#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>

using namespace std;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    cv::Mat dst_127, image;

    // cv::Canny(cv_bridge::toCvShare(msg, "mono8")->image , dst_127, 100, 127, 3, false);

    // cout << "running image Callback" << endl;
    // cv::imshow("sub", dst_127);


    // print original image
   cv::imshow("sub", cv_bridge::toCvShare(msg, "bgr8")->image);
   cout << "running main sub" << endl;


    cv::waitKey(30);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

int main(int argc, char **argv)
{
  cout << "running sub main" << endl;
  ros::init(argc, argv, "ros_opencv_sub");
  ros::NodeHandle nh;
  cv::namedWindow("sub");

  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("camera/color/image_raw", 1, imageCallback);
  ros::spin();
  cv::destroyWindow("sub");
}


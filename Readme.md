## Depth camera on car

>* Depth camera를 차에 붙이고 publish하는 image를 rviz에 띄우기
>* 촬영한 image를 다른 노드에서 subscribe하기


### * Depth camera를 차에 붙이고 publish하는 image를 rviz에 띄우기

1. Car model 만들기 (https://github.com/SungjoonCho/ROS-study/blob/main/gazebo/Creating%20Model.md)

2. model에 카메라 붙이기 

  * 우선 kinect sensor 카메라 다운로드 (참고 : <http://gazebosim.org/tutorials/?tut=ros_depth_camera>)
  
    a. http://github.com/osrf/gazebo_tutorials/raw/master/ros_depth_camera/files/kinect.zip 에서 zip 파일 다운로드

    b. kinect 폴더를 kinect_ros로 이름 바꾸고  ~/.gazebo/models에 넣어놓기

    c. config 파일과 model.sdf 파일에 폴더 이름 바꾼대로 적용

    d. sensor 태그 안에, </camera> 태그 끝나자마자 아래 코드 삽입

 
```html
<plugin name="camera_plugin" filename="libgazebo_ros_openni_kinect.so">
          <baseline>0.2</baseline>
          <alwaysOn>true</alwaysOn>
          <!-- Keep this zero, update_rate in the parent <sensor> tag
            will control the frame rate. -->
          <updateRate>0.0</updateRate>
          <cameraName>camera_ir</cameraName>
          <imageTopicName>/camera/color/image_raw</imageTopicName>
          <cameraInfoTopicName>/camera/color/camera_info</cameraInfoTopicName>
          <depthImageTopicName>/camera/depth/image_raw</depthImageTopicName>
          <depthImageCameraInfoTopicName>/camera/depth/camera_info</depthImageCameraInfoTopicName>
          <pointCloudTopicName>/camera/depth/points</pointCloudTopicName>
          <frameName>camera_link</frameName>
          <pointCloudCutoff>0.5</pointCloudCutoff>
          <pointCloudCutoffMax>3.0</pointCloudCutoffMax>
          <distortionK1>0</distortionK1>
          <distortionK2>0</distortionK2>
          <distortionK3>0</distortionK3>
          <distortionT1>0</distortionT1>
          <distortionT2>0</distortionT2>
          <CxPrime>0</CxPrime>
          <Cx>0</Cx>
          <Cy>0</Cy>
          <focalLength>0</focalLength>
          <hackBaseline>0</hackBaseline>
        </plugin>

```

3. gazebo 열어서 (roslaunch gazebo_ros empty_world.launch) car model edit

4. 모델에다가 카메라 붙이기 (joint 하고 joint type은 fixed) 

    이때 카메라에 plugin 코드를 삽입해놓았으므로 모델에는 추가로 plugin 코드 삽입 필요 없다.

5. 모델 저장하고 나오기

6. gazebo 다시 켜고 [Insert] 탭에서 Add path - 내 모델 경로

   이때 내 모델의 패키지 경로까지만 지정해주면 알아서 모델 파일 뜬다.

7. model 카메라 앞에 촬영할 도형 및 구조물 하나 두고 gazebo 하단의 재생 버튼 눌려있는지 확인

<p align="center">
  <img width="600" height="300" src="https://user-images.githubusercontent.com/80872528/113850875-df976000-97d5-11eb-9750-3fd0150a9954.png">
</p>

8. 새 터미널 창 - $rosrun rviz rviz

9. Fixed Frame은 camera_link로 바꿔주고 Add - Image, PointCloud2

10. ImageTopic 드롭박스 클릭시 /camera/color/image_raw 선택

<p align="center">
  <img width="400" src="https://user-images.githubusercontent.com/80872528/113852174-3baeb400-97d7-11eb-82d5-13cc082cc1ff.png">
</p>

<pre>
  rviz가 topic을 subscribe하여 화면에 영상 출력
  
  만약 영상 안 뜬다면 plugin에서 잘못 되었을 확률 큼
  
  rostopic list로 현재 오가는 topic 확인 가능
</pre>

<p align="center">
  <img width="700" src="https://user-images.githubusercontent.com/80872528/113852450-8a5c4e00-97d7-11eb-9bd6-0c522b25567b.png">
</p>


### * 촬영한 image를 다른 노드에서 subscribe하기

1.패키지 ros_opencv_sub에 대해서 catkin_create (https://github.com/SungjoonCho/ROS-study)

2.ros_opencv_sub.cpp 소스코드에서 topic명은 받고 싶은 topic으로 써준다. 코드에서는 image를 받으므로 “camera/image”

3.빌드 후 subscribe한 화면에 영상 출력

  $cd ros_opencv_sub
  
  $catkin_make



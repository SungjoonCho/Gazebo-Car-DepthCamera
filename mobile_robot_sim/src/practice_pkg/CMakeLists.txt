cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(practice_pkg REQUIRED)

include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_executable(practice_pkg listener.cc)
target_link_libraries(practice_pkg ${GAZEBO_LIBRARIES} pthread)

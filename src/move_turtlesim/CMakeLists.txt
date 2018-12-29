cmake_minimum_required(VERSION 2.8.3)
project(move_turtlesim)

find_package(catkin REQUIRED roscpp turtlesim geometry_msgs)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(test1 src/test1.cpp)
target_link_libraries(test1
  ${catkin_LIBRARIES}
)
add_executable(miniTest2 src/miniTest2.cpp)
target_link_libraries(miniTest2
  ${catkin_LIBRARIES}
)

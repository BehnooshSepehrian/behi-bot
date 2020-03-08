cmake_minimum_required(VERSION 2.8.3)
project(line_following)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  duckietown_msgs
)
catkin_package(     
  LIBRARIES line_following
  CATKIN_DEPENDS std_msgs roscpp duckietown_msgs
)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(line_following_node src/line_following_node.cpp)
add_dependencies(line_following_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(line_following_node ${catkin_LIBRARIES})


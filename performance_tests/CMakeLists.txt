cmake_minimum_required(VERSION 2.8.3)
project(performance_tests)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
        roscpp
        rospy
        std_msgs
        message_generation
)


## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   SuperAwesome.msg
 )

## Generate services in the 'srv' folder
 add_service_files(
   FILES
   LoopRate.srv
)

## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs
 )


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES performance_tests
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(pub_cpp src/pubcpp.cpp)
target_link_libraries(pub_cpp ${catkin_LIBRARIES})
add_dependencies(pub_cpp performance_tests_generate_messages_cpp)

add_executable(sub_cpp src/subcpp.cpp)
target_link_libraries(sub_cpp ${catkin_LIBRARIES})
add_dependencies(sub_cpp performance_tests_generate_messages_cpp)

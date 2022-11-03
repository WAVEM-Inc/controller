cmake_minimum_required(VERSION 2.8.3)
project(wm_motor_subscriber)

find_package(catkin REQUIRED COMPONENTS message_generation std_msgs roscpp)

generate_messages(DEPENDENCIES std_msgs )
catkin_package(
	INCLUDE_DIRS include
	LIBRARIES wm_motor_subscriber
  CATKIN_DEPENDS std_msgs roscpp
)

include_directories(
	include
	include/wm_motor_subscriber
	${catkin_INCLUDE_DIRS})

ADD_LIBRARY(dart_mx8m_gpio STATIC lib/gpio_ctrl.c)
add_executable(cdrmotor_subscriber src/cdrmotor_subscriber.cpp lib/gpio_ctrl.cpp
				src/cl_motor_manager.cpp src/cl_motor_recv_data.cpp)
add_dependencies(cdrmotor_subscriber ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(cdrmotor_subscriber ${catkin_LIBRARIES})


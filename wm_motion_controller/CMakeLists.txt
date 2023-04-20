cmake_minimum_required(VERSION 3.5)
project(wm_motion_controller)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

include_directories(
  include
  include/${PROJECT_NAME}
  #${EXTERNAL_INCLUDE_DIRS}
)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(actionlib_msgs REQUIRED)
find_package(can_msgs REQUIRED)

add_executable(wm_motion_controller_node src/wm_motion_controller.cpp src/main.cpp
  src/can/lib.cpp src/can/can_adaptor.cpp src/can/can_send.cpp src/can/data_relayer.cpp src/can/can_dump.cpp src/can/can_manager.cpp
)

ament_target_dependencies(wm_motion_controller_node rclcpp std_msgs geometry_msgs can_msgs)

install(TARGETS
  wm_motion_controller_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

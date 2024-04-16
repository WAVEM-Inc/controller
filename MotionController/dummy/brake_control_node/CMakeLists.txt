cmake_minimum_required(VERSION 3.8)
project(brake_control_node)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(can_msgs REQUIRED)

# add executable
add_executable(brake_control_node src/brake_control_node.cpp)
ament_target_dependencies(brake_control_node rclcpp can_msgs)

install(TARGETS
  brake_control_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()

cmake_minimum_required(VERSION 3.8)
project(ad_steering_publisher)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(can_msgs REQUIRED)

# add executable
add_executable(ad_steering_publisher src/steering_control_node.cpp)
ament_target_dependencies(ad_steering_publisher rclcpp can_msgs)

install(TARGETS
  ad_steering_publisher
  DESTINATION lib/${PROJECT_NAME})

ament_package()


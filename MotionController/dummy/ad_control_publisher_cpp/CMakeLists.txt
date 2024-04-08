cmake_minimum_required(VERSION 3.5)
project(ad_control_publisher_cpp)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(can_msgs REQUIRED)

# Add the executable
add_executable(ad_control_publisher src/main.cpp)

# Include directories
target_include_directories(ad_control_publisher PRIVATE include)

# Link against the libraries
ament_target_dependencies(ad_control_publisher rclcpp can_msgs)

# Install the executable
install(TARGETS
  ad_control_publisher
  DESTINATION lib/${PROJECT_NAME})

ament_package()

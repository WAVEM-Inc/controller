cmake_minimum_required(VERSION 3.5)
project(can_led_keyboard)

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
find_package(can_msgs REQUIRED)

add_executable(can_led_keyboard_node src/can_led_keyboard.cpp
)

ament_target_dependencies(can_led_keyboard_node rclcpp can_msgs)

install(TARGETS
  can_led_keyboard_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

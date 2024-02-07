cmake_minimum_required(VERSION 3.5)
project(odom_listener)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav_msgs REQUIRED)

set(source_set 
	src/main.cpp
	)
set(dependencies
	rclcpp
	nav_msgs
	)
set(node_name
	${PROJECT_NAME}_node
	)
add_executable(${node_name}
  ${source_set}
)

ament_target_dependencies(${node_name}
  ${dependencies}
)
install(TARGETS
  ${node_name}
  DESTINATION lib/${PROJECT_NAME}
)


ament_package()

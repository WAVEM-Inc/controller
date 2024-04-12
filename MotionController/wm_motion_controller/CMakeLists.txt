cmake_minimum_required(VERSION 3.5)
project(wm_motion_controller)

# Default to C++14
if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
endif ()

include_directories(
        include
        include/${PROJECT_NAME}
        #${EXTERNAL_INCLUDE_DIRS}
)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
#find_package(actionlib_msgs REQUIRED)
find_package(can_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(route_msgs REQUIRED)

add_executable(wm_motion_controller_node
        src/main.cpp
        src/wm_motion_controller/wm_motion_controller.cpp src/wm_motion_controller/wm_motion_controller_constants.cpp
        src/converter/ugv_converter.cpp src/entity/ugv.cpp
        src/quaternion/quaternion.cpp
    src/converter/ugv_converter.cpp src/entity/ugv.cpp
        src/quaternion/quaternion.cpp
        include/common/test.h
)
ament_target_dependencies(wm_motion_controller_node
        rclcpp
        std_msgs
        geometry_msgs
        can_msgs
        sensor_msgs
        nav_msgs
        tf2_ros
        route_msgs

)
install(TARGETS
        wm_motion_controller_node
        DESTINATION lib/${PROJECT_NAME}
)
install(DIRECTORY
        launch
        DESTINATION share/${PROJECT_NAME}
)
ament_package()

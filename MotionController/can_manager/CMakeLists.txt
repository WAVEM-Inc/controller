cmake_minimum_required(VERSION 3.8)
project(can_manager)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(can_msgs REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(
        include
        include/${PROJECT_NAME}
        #${EXTERNAL_INCLUDE_DIRS}
)
set(dependencies
        rclcpp
        can_msgs
        #route_msgs
        std_msgs
)

set(source_list
        src/main.cpp
        include/can/can2ad_dbc.h
        include/can/can2vcu_dbc.h
        include/can/can_adaptor.hpp
        include/can/can_define.hpp
        include/can/can_dump.hpp
        include/can/can_manager.hpp
        include/can/can_send.hpp
        include/can/cancallbackfunc.hpp
        include/can/data_relayer.hpp
        include/can/i_can_connect.hpp
        include/can/lib.hpp
        include/can/lib.hpp
        src/can/can_adaptor.cpp
        src/can/can_dump.cpp
        src/can/can_manager.cpp
        src/can/can_send.cpp
        src/can/data_relayer.cpp
        src/can/lib.cpp
        include/can_manager/constants.hpp
)
set(node_name
        can_manager_node
)
add_executable(${node_name}
        ${source_list}
)
ament_target_dependencies(${node_name}
        ${dependencies}
)
install(TARGETS
        ${node_name}
        DESTINATION lib/${PROJECT_NAME}
)
ament_package()


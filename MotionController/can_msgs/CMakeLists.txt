cmake_minimum_required(VERSION 3.5)
project(can_msgs)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(nav_msgs REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
        "msg/AdControlAccelerate.msg"
        "msg/AdControlBody.msg"
        "msg/AdControlBrake.msg"
        "msg/AdControlSteering.msg"
        "msg/Bms.msg"
        "msg/DbsStatusTwo.msg"
        "msg/TorqueFeedback.msg"
        "msg/VcuMcuRequest.msg"
        "msg/Mode.msg"
        "msg/Emergency.msg"
	"msg/Init.msg"
	"msg/VcuVehicleOdometerStatus.msg"
        DEPENDENCIES builtin_interfaces std_msgs nav_msgs
)

ament_export_dependencies(rosidl_default_runtime)

ament_package()

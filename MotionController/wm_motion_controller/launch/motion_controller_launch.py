from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
def generate_launch_description():
    motion_node_arg = DeclareLaunchArgument('correction', default_value='3.14')
    motion_node = Node(
        package='wm_motion_controller',
        executable='wm_motion_controller_node',
        parameters=[{'correction': 90.0}],
        output='screen'
    )

    return LaunchDescription([motion_node])

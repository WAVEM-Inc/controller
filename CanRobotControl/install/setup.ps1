# generated from colcon_powershell/shell/template/prefix_chain.ps1.em

# This script extends the environment with the environment of other prefix
# paths which were sourced when this file was generated as well as all packages
# contained in this prefix path.

# function to source another script with conditional trace output
# first argument: the path of the script
function _colcon_prefix_chain_powershell_source_script {
  param (
    $_colcon_prefix_chain_powershell_source_script_param
  )
  # source script with conditional trace output
  if (Test-Path $_colcon_prefix_chain_powershell_source_script_param) {
    if ($env:COLCON_TRACE) {
      echo ". '$_colcon_prefix_chain_powershell_source_script_param'"
    }
    . "$_colcon_prefix_chain_powershell_source_script_param"
  } else {
    Write-Error "not found: '$_colcon_prefix_chain_powershell_source_script_param'"
  }
}

# source chained prefixes
_colcon_prefix_chain_powershell_source_script "/opt/ros/foxy\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/rms/rcs_mqtt_bridge/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/amr-navigation/gps_to_slam_transformer/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/gps/ublox-foxy-RTCM-correction-/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/controller/FakeController/fake_controller/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/controller/odom_listener/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/ros2_library/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/ros2_library/teb_local/teb_local_planner/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/ros2_library/teb_local/costmap_converter/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/gps/geographic_info-ros2/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/gps/mavros-ros2/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/gps/nmea/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/gps/ntrip_client-ros2/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/amr-navigation/navigation2/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/amr-navigation/robot_pose_publisher/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/amr-navigation/robot_state_listener/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/amr-navigation/robot_state_publisher/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/imu/imu_listener/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/imu/imu_tools/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/imu/phidgets_drivers-foxy/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/lidar/velodyne/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/lidar/velodyne_listener/install\local_setup.ps1"
_colcon_prefix_chain_powershell_source_script "/ws/ugv_total_launcher/install\local_setup.ps1"

# source this prefix
$env:COLCON_CURRENT_PREFIX=(Split-Path $PSCommandPath -Parent)
_colcon_prefix_chain_powershell_source_script "$env:COLCON_CURRENT_PREFIX\local_setup.ps1"

#ifndef WM_MOTION_CONTROLLER_HPP_
#define WM_MOTION_CONTROLLER_HPP_

#define STEER_MAX_ANGLE 0.7
#define CLEAR_FLOAT_ZERO 0.0
#define TP_CMDVEL "/cmd_vel"
#define TP_CONTROL_HARD_WARE "/can/control_hardware"
#define TP_QUEUE_SIZE 1
#define TP_ODOM "/drive/odom/origin"
#define TP_RTT_ODOM "/drive/odom/eular"
#define ODOM_FRAME_ID "odom"
#define CHILD_FRAME_ID "base_footprint"
#define TP_IMU "/sensor/imu/data"
#define TP_EMERGENCY "/emergency"
#define TP_CONTROL_MODE "/control/mode"
#define TP_NAME_BREAK "/drive/break"
#define TP_NAME_RPM "/drive/can/vcu/torque_feedback"

#define TP_NAME_CONTROL_BODY "/drive/can/ad_control_body"
#define TP_NAME_CONTROL_ACCELERATE "/drive/can/ad_control_accelerate"
#define TP_NAME_CONTROL_BRAKE "/drive/can/ad_control_brake"
#define TP_NAME_CONTROL_STEERING "/drive/can/ad_control_steering"
#define RPM_CENTER 10000.0
#define ZERO_APPROXIMATION 0.008
#define RPM_BREAK 10

#define SLAM_MODE_FAST_SPEED 0.5
#define SLAM_MODE_ANG_COR 100

#define LOG_CONSTRUCTOR "==[WmMotionContoller__CONSTRUCTOR]== "
#define LOG_FUNC_CHW_CALLBACK "==[WmMotionController__can_chw_callback]== "
#define LOG_FUNC_IMU_CALLBACK "==[WmMotionController__imu_callback]== "
#define LOG_FUNC_CMD_CALLBACK "==[WmMotionController__cmdvel_callback]== "
#define LOG_MEDIATOR_RECV_RPM_DISTANCE "==[WmMotionController__recv_rpm__distance]== "
#define LOG_MEDIATOR_RECV_RPM_CHECK "==[WmMotionController__recv_rpm__check]== "

#endif
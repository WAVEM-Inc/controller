#ifndef WM_MOTION_CONTROLLER_HPP_
#define WM_MOTION_CONTROLLER_HPP_

#define STEER_MAX_ANGLE 0.7
#define CLEAR_FLOAT_ZERO 0.0
#define TP_CMDVEL "/cmd_vel"
#define TP_CONTROL_HARD_WARE "/can/control_hardware"
#define TP_QUEUE_SIZE 10
#define TP_ODOM "/odom"
#define ODOM_FRAME_ID "/odom"
#define CHILD_FRAME_ID "base_footprint"
#define TP_IMU "/imu/data"
#define RPM_CENTER 100000.0
#define ZERO_APPROXIMATION 0.008
#define RPM_BREAK 10

#define LOG_CONSTRUCTOR "==[WmMotionContoller__CONSTRUCTOR]== "
#define LOG_FUNC_CHW_CALLBACK "==[WmMotionController__can_chw_callback]== "
#define LOG_FUNC_IMU_CALLBACK "==[WmMotionController__imu_callback]== "
#define LOG_FUNC_CMD_CALLBACK "==[WmMotionController__cmdvel_callback]== "
#define LOG_MEDIATOR_RECV_RPM_DISTANCE "==[WmMotionController__recv_rpm__distance]== "
#define LOG_MEDIATOR_RECV_RPM_CHECK "==[WmMotionController__recv_rpm__check]== "

#endif
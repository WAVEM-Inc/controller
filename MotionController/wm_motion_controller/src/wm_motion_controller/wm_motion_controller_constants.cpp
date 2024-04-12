#include"wm_motion_controller/wm_motion_controller_constants.hpp"

WmMotionControllerConstants::WmMotionControllerConstants():
        m_steer_max_ang(STEER_MAX_ANGLE),
        m_tp_cmdvel(TP_CMDVEL),
        m_tp_queue_size(TP_QUEUE_SIZE),
        m_tp_can_chw(TP_CONTROL_HARD_WARE),
        tp_imu_(TP_IMU),
        tp_odom_(TP_ODOM),
        odom_frame_id_(ODOM_FRAME_ID),
        child_frame_id_(CHILD_FRAME_ID),
        clear_zero_(CLEAR_FLOAT_ZERO),
        rpm_center_(RPM_CENTER),
        rpm_break(RPM_BREAK),
        zero_approximation_(ZERO_APPROXIMATION),
        log_constructor(LOG_CONSTRUCTOR),
        log_chw_callback(LOG_FUNC_CHW_CALLBACK),
        log_imu_callback(LOG_FUNC_IMU_CALLBACK),
        log_cmd_callback(LOG_FUNC_CMD_CALLBACK),
        log_mediator_recv_rpm_distance(LOG_MEDIATOR_RECV_RPM_DISTANCE),
        log_mediator_recv_rpm_check(LOG_MEDIATOR_RECV_RPM_CHECK),
        tp_rtt_odom_(TP_RTT_ODOM),
        tp_control_mode_(TP_CONTROL_MODE),
        tp_emergency_(TP_EMERGENCY),
        slam_mode_fast_speed_(SLAM_MODE_FAST_SPEED),
        slam_mode_ang_cor_(SLAM_MODE_ANG_COR),
        tp_control_body_(TP_NAME_CONTROL_BODY),
        tp_control_accelerate_(TP_NAME_CONTROL_ACCELERATE),
        tp_control_brake_(TP_NAME_CONTROL_BRAKE),
        tp_control_steering_(TP_NAME_CONTROL_STEERING)
{

}
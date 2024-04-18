#ifndef WM_MOTION_CONTOLLER__CONSTANTS_HPP_
#define WM_MOTION_CONTOLLER__CONSTANTS_HPP_
#include<iostream>
#include"wm_motion_controller/df_motion_controller.hpp"
class WmMotionControllerConstants{

public :
    const int m_steer_max_ang;
    const int m_tp_queue_size;
    const std::string m_tp_cmdvel;
    const std::string m_tp_can_chw;
    const std::string tp_imu_;
    const std::string tp_odom_;
    const std::string odom_frame_id_;
    const std::string child_frame_id_;
    const std::string tp_control_body_;
    const std::string tp_control_accelerate_;
    const std::string tp_control_brake_;
    const std::string tp_control_steering_;
    const std::string tp_break_;
    const std::string tp_name_rpm_;

    const float clear_zero_;
    const float rpm_center_;
    const float zero_approximation_;
    const float rpm_break;
    const float slam_mode_fast_speed_;
    const float slam_mode_ang_cor_;

    const std::string log_constructor;
    const std::string log_chw_callback;
    const std::string log_imu_callback;
    const std::string log_cmd_callback;
    const std::string log_mediator_recv_rpm_distance;
    const std::string log_mediator_recv_rpm_check;
    const std::string tp_rtt_odom_;
    const std::string tp_control_mode_;
    const std::string tp_emergency_;
    WmMotionControllerConstants();
};

#endif
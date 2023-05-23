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
        const float clear_zero_;
        const std::string log_constructor;
        WmMotionControllerConstants();
};

#endif
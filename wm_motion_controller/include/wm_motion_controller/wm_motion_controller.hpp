#ifndef MOTION_CONTROLLER
#define MOTION_CONTROLLER

// cpp header file
#include <iostream>
#include <math.h> //std::fabs
#include <unistd.h>
#include <signal.h>
#include <functional>

// ros2 header file
#include"rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "can_msgs/msg/control_hardware.hpp"

// define header file
#include "wm_motion_controller/df_motion_controller.hpp"

// can header file
#include "can/can_manager.hpp"

#include "colleague/motion_colleague.hpp"
#include "mediator/i_motion_mediator.hpp"

using std::placeholders::_1;

/**
 * @brief Class controlled by robot motion can communication
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.05
 */
class WmMotionController : public rclcpp::Node,public MotionColleague{
    private :
        const int m_steer_max_ang;
        const int m_tp_queue_size;
        const std::string m_tp_cmdvel;
        const std::string m_tp_can_chw;
        rclcpp::TimerBase::SharedPtr m_timer;
        rclcpp::CallbackGroup::SharedPtr m_cb_group_cmd_vel;
        rclcpp::CallbackGroup::SharedPtr m_cb_group_can_chw;
        rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr m_sub_cmdvel;
        rclcpp::Subscription<can_msgs::msg::ControlHardware>::SharedPtr m_sub_can_chw;
        void fn_can_chw_callback(const can_msgs::msg::ControlHardware::SharedPtr can_chw);
        void fn_cmdvel_callback(const geometry_msgs::msg::Twist::SharedPtr cmd_vel);
        CanMGR* m_can_manager;
        //override
        //void fn_wm_motion_controller_function(int value);
        float fn_mps2kmph(float mps);
        float fn_kmph2mps(float kmph);
    public :
        WmMotionController(IMotionMediator* motion_colleague);
        virtual ~WmMotionController();
};

#endif
#ifndef MOTION_CONTROLLER
#define MOTION_CONTROLLER

// cpp header file
#include <iostream>
#include <math.h> //std::fabs
#include <unistd.h>
#include <signal.h>
#include <functional>
#include <memory>
// ros2 header file
#include"rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "can_msgs/msg/control_hardware.hpp"


// define header file
#include "wm_motion_controller/df_motion_controller.hpp"

// can header file
#include "can/can_manager.hpp"

// mediator header file
#include "colleague/i_motion_colleague.hpp"
#include "mediator/i_motion_mediator.hpp"
#include "mediator/concrete_motion_mediator.hpp"

#include "entity/ugv.hpp"

using std::placeholders::_1;
class IMotionMediator;
/**
 * @brief Class controlled by robot motion can communication
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.05
 */
class WmMotionController : public rclcpp::Node,public IMotionColleague,public std::enable_shared_from_this<WmMotionController> {
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
        std::shared_ptr<CanMGR> m_can_manager;

        std::shared_ptr<ENTITY::UGV> prev_ugv_;
        std::shared_ptr<ENTITY::UGV> cur_ugv_;

        //override
        //void fn_wm_motion_controller_function(int value);
        float fn_mps2kmph(float mps);
        float fn_kmph2mps(float kmph);
        //

    public :
        WmMotionController(std::shared_ptr<IMotionMediator> motion_colleague,std::shared_ptr<CanMGR> can_mgr);
        virtual ~WmMotionController();
        void fn_send_value(const int& value) override;
        void fn_recv_value(const int& value) override;
        void fn_send_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time) override;
        void fn_recv_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time) override;
};

#endif
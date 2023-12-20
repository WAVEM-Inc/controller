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
#include "can_msgs/msg/mode.hpp"
#include "can_msgs/msg/emergency.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
// define header file
#include "wm_motion_controller/wm_motion_controller_constants.hpp"

// can header file
#include "can/can_manager.hpp"

// mediator header file
#include "colleague/i_motion_colleague.hpp"
#include "mediator/i_motion_mediator.hpp"
#include "mediator/concrete_motion_mediator.hpp"

#include "entity/ugv.hpp"
#include "quaternion/quaternion.hpp"

using std::placeholders::_1;
class IMotionMediator;
/**
 * @brief Class controlled by robot motion can communication
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.05
 */
class WmMotionController : public rclcpp::Node,public IMotionColleague,public std::enable_shared_from_this<WmMotionController> {
    private :
        std::shared_ptr<WmMotionControllerConstants> constants_;
        float test;
        std::shared_ptr<CanMGR> m_can_manager;
        // timer 
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::TimerBase::SharedPtr tf_timer_;
        // callback group list 
        rclcpp::CallbackGroup::SharedPtr m_cb_group_cmd_vel;
        rclcpp::CallbackGroup::SharedPtr m_cb_group_can_chw;
        rclcpp::CallbackGroup::SharedPtr cb_group_imu_;
        rclcpp::CallbackGroup::SharedPtr cb_group_odom_;
        rclcpp::CallbackGroup::SharedPtr cb_group_rtt_odom_;
        rclcpp::CallbackGroup::SharedPtr cb_group_mode_;
        rclcpp::CallbackGroup::SharedPtr cb_group_emergency_;

        // subscription list
        rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr m_sub_cmdvel;
        rclcpp::Subscription<can_msgs::msg::ControlHardware>::SharedPtr m_sub_can_chw;
        rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr sub_imu_;
        rclcpp::Subscription<can_msgs::msg::Mode>::SharedPtr sub_mode_;
        rclcpp::Subscription<can_msgs::msg::Emergency>::SharedPtr sub_emergency_;

        rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr pub_odom_;
        rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pub_rtt_;

        // callback fucntion list
        void fn_can_chw_callback(const can_msgs::msg::ControlHardware::SharedPtr can_chw);
        void fn_cmdvel_callback(const geometry_msgs::msg::Twist::SharedPtr cmd_vel);
        void imu_callback(const sensor_msgs::msg::Imu::SharedPtr imu);
        void slam_mode_callback(const can_msgs::msg::Mode::SharedPtr mode);
        void emergency_callback(const can_msgs::msg::Emergency::SharedPtr stop);

        // ugv calculate 
        std::shared_ptr<ENTITY::UGV> prev_ugv_;
        std::shared_ptr<ENTITY::UGV> cur_ugv_;

        float fn_mps2kmph(float mps);
        float fn_kmph2mps(float kmph);
        // refactoring target list
        Quaternion qua_;
        tf2::Quaternion q;
        float pose_yaw_;
        float prev_pose_yaw_;
        rclcpp::Time imu_time_;
        rclcpp::Time odom_time_;
        double lo_x_;
        double lo_y_;
        double lo_th_;
        double dxy_;
        double vel_x_;
        double vel_th_;
        double odom_dist_;
        double origin_corr_;
        double origin_x_;
        double origin_y_;
        double imu_th_;
        double prev_imu_th_;
        float correction_;
        bool control_mode_;
        bool emergency_check_;
        geometry_msgs::msg::Quaternion odom_quat_;
        //rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Time current_time_;  //!< 현재 시각
		rclcpp::Time last_time_;	 //!< 가장 최근 오도메트리 공표 시각: 델타 계산에 필요
        // Robot Control function list
        void pub_odometry();
        void update_transform();
        void calculate_next_position();
        void calculate_next_orientation();
        void cmd_vel_break(float vel_linear, float cur_rpm);
        void cmd_vel_run(float vel_linear, float vel_angular);
        //
        float cmd_angel_convert(const float& ori_angel,const float& ori_linaer);
    public :
        WmMotionController(std::shared_ptr<IMotionMediator> motion_colleague,std::shared_ptr<CanMGR> can_mgr);
        virtual ~WmMotionController();

        // mediator function list
        void fn_send_value(const int& value) override;
        void fn_recv_value(const int& value) override;
        void fn_send_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time) override;
        void fn_recv_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time) override;
};

#endif
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
#include "can_msgs/msg/ad_control_accelerate.hpp"
#include "can_msgs/msg/ad_control_body.hpp"
#include "can_msgs/msg/ad_control_brake.hpp"
#include "can_msgs/msg/ad_control_steering.hpp"
#include "can_msgs/msg/torque_feedback.hpp"

#include "can_msgs/msg/mode.hpp"
#include "route_msgs/msg/drive_break.hpp"
#include "route_msgs/msg/offset.hpp"

#include "sensor_msgs/msg/imu.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
// define header file
#include "wm_motion_controller/wm_motion_controller_constants.hpp"


#include "entity/ugv.hpp"
#include "quaternion/quaternion.hpp"

using std::placeholders::_1;
/**
 * @brief Class controlled by robot motion can communication
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.05
 */
class WmMotionController : public rclcpp::Node {
private :
    std::shared_ptr<WmMotionControllerConstants> constants_;
    float total_odom_;
    float imu_offset_;
    //std::shared_ptr<Manager> manager_;

    // timer
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::TimerBase::SharedPtr tf_timer_;
    // callback group list
    rclcpp::CallbackGroup::SharedPtr m_cb_group_cmd_vel;

    rclcpp::CallbackGroup::SharedPtr cb_group_imu_;
    rclcpp::CallbackGroup::SharedPtr cb_group_odom_;
    rclcpp::CallbackGroup::SharedPtr cb_group_rtt_odom_;
    rclcpp::CallbackGroup::SharedPtr cb_group_mode_;
    rclcpp::CallbackGroup::SharedPtr cb_group_break_;
    rclcpp::CallbackGroup::SharedPtr cbg_body_;
    rclcpp::CallbackGroup::SharedPtr cbg_accelerate_;
    rclcpp::CallbackGroup::SharedPtr cbg_brake_;
    rclcpp::CallbackGroup::SharedPtr cbg_steering_;
    rclcpp::CallbackGroup::SharedPtr cbg_rpm_;
    rclcpp::CallbackGroup::SharedPtr cbg_imu_offset_;
    // publish list
    rclcpp::Publisher<can_msgs::msg::AdControlBody>::SharedPtr pub_body_;
    rclcpp::Publisher<can_msgs::msg::AdControlAccelerate>::SharedPtr pub_accelerate_;
    rclcpp::Publisher<can_msgs::msg::AdControlBrake>::SharedPtr pub_brake_;
    rclcpp::Publisher<can_msgs::msg::AdControlSteering>::SharedPtr pub_steering_;
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr pub_odom_;
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pub_rtt_;

    // subscription list
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr m_sub_cmdvel;

    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr sub_imu_;
    rclcpp::Subscription<can_msgs::msg::Mode>::SharedPtr sub_mode_;
    rclcpp::Subscription<route_msgs::msg::DriveBreak>::SharedPtr sub_break_;
    rclcpp::Subscription<can_msgs::msg::TorqueFeedback>::SharedPtr sub_rpm_;
    rclcpp::Subscription<route_msgs::msg::Offset>::SharedPtr sub_imu_offset_;
    std::unique_ptr<tf2_ros::TransformBroadcaster> broadcaster;

    // callback fucntion list

    void fn_cmdvel_callback(const geometry_msgs::msg::Twist::SharedPtr cmd_vel);
    void imu_callback(const sensor_msgs::msg::Imu::SharedPtr imu);
    void slam_mode_callback(const can_msgs::msg::Mode::SharedPtr mode);
    void break_callback(const route_msgs::msg::DriveBreak::SharedPtr pressure);
    void rpm_callback(const can_msgs::msg::TorqueFeedback::SharedPtr rpm);
    void imu_offset_callback(const route_msgs::msg::Offset::SharedPtr data);

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
    float odometry_offset_;
    bool control_mode_;
    double pressure_;
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
    WmMotionController();
    virtual ~WmMotionController();

    // mediator function list
    void fn_send_value(const int& value) ;
    void fn_recv_value(const int& value) ;
    void fn_send_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time) ;
    void fn_recv_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time) ;

    int test_num ;
    void run() {
        // 여기에 스레드로 실행할 작업을 추가합니다.
        // 이 예시에서는 간단히 "WmMotionController is running"을 출력합니다.
        while (rclcpp::ok()) {
            std::cout << "WmMotionController is running" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1)); // 1초 대기
        }
    }

};

#endif
#ifndef CAN_MANAGER
#define CAN_MANAGER

// can header file
#include "can/data_relayer.hpp"

// linux header file 
#include <unistd.h> //sleep
#include <iomanip>
#include <chrono> // time
#include <memory>
//extern int optind, opterr, optopt;
//static char *progname;
#include "can/df_ugv.hpp"
#include "can_manager/constants.hpp"
// can include
#include "rclcpp/rclcpp.hpp"
#include "can_msgs/msg/ad_control_body.hpp"
#include "can_msgs/msg/ad_control_accelerate.hpp"
#include "can_msgs/msg/ad_control_brake.hpp"
#include "can_msgs/msg/ad_control_steering.hpp"
#include "can_msgs/msg/bms.hpp"
#include "can_msgs/msg/dbs_status_two.hpp"
#include "can_msgs/msg/torque_feedback.hpp"
#include "can_msgs/msg/vcu_mcu_request.hpp"
#include "robot_status_msgs/msg/velocity_status.hpp"
#include "can_msgs/msg/emergency.hpp"
#include "sensor_msgs/msg/battery_state.hpp"
#include "can_msgs/msg/init.hpp"
#include "std_msgs/msg/string.hpp"

static volatile int state = 1;

/**
 * @brief 
 * @param signo 
 */
static void sigterm(int signo) {
    fprintf(stdout, "SIGNAL %d  in main\n", signo);
    state = 0;
}

/**
 * @brief Class to control CAN communication
 * @author changunAn(changun516@wavem.net)
 * @see enable_shared_from_this
 * @see ICanConnect
 * @see IMotionColleague
 * @warning Be careful of problems caused by Mutex
 */
class CanMGR : public rclcpp::Node {
//class CanMGR{
private :
    DataRelayer obj_; // Member variables for calling Can-related functions
    float cur_speed_;
    float cur_speed_acc_;
    bool check_emergency_;
    std::chrono::_V2::system_clock::time_point callback_time_; // current callback time
    std::chrono::_V2::system_clock::time_point old_time_; // Previous callback time
    std::unique_ptr<Constants> constants_;
    rclcpp::Subscription<can_msgs::msg::AdControlBody>::SharedPtr sub_body_;
    rclcpp::Subscription<can_msgs::msg::AdControlAccelerate>::SharedPtr sub_accelerate_;
    rclcpp::Subscription<can_msgs::msg::AdControlBrake>::SharedPtr sub_brake_;
    rclcpp::Subscription<can_msgs::msg::AdControlSteering>::SharedPtr sub_steering_;
    rclcpp::Subscription<can_msgs::msg::Emergency>::SharedPtr sub_emergency_;
    rclcpp::Subscription<can_msgs::msg::Init>::SharedPtr sub_can_init_;

    rclcpp::CallbackGroup::SharedPtr cbg_body;
    rclcpp::CallbackGroup::SharedPtr cbg_accelerate;
    rclcpp::CallbackGroup::SharedPtr cbg_brake;
    rclcpp::CallbackGroup::SharedPtr cbg_steering;
    rclcpp::CallbackGroup::SharedPtr cbg_emergency;
    rclcpp::CallbackGroup::SharedPtr cbg_init_;
    rclcpp::CallbackGroup::SharedPtr cbg_rpm;
    rclcpp::CallbackGroup::SharedPtr cbg_bms;
    rclcpp::CallbackGroup::SharedPtr cbg_velocity;
    rclcpp::CallbackGroup::SharedPtr cbg_error_;

    rclcpp::Publisher<can_msgs::msg::TorqueFeedback>::SharedPtr pub_rpm_;
    rclcpp::Publisher<sensor_msgs::msg::BatteryState>::SharedPtr pub_bms_;
    rclcpp::Publisher<robot_status_msgs::msg::VelocityStatus>::SharedPtr pub_velocity_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_error_;

    int fn_can_init(); // can callback function register
    void faultCallback(int can_falut, unsigned long long dbs_fault);

    void rpmCallback(int mcu_shift, int mcu_speed, int mcu_torque);

    void bmsCallback(int bms_charge_stscc ,int soc, int sys_sts, int voltage);
    void vehicleErrorCallback(int error_code, int low_voltage);
    void vehicleStatus2Callback(int brake_press, float speed);
    void remoteIOCallback(int remote_a);
    void vehicleOdometerStatusCallback(float odom);
    void log(std::string call_name);

    void tp_control_body_callback(can_msgs::msg::AdControlBody::SharedPtr control_body);

    void tp_control_accelerate(can_msgs::msg::AdControlAccelerate::SharedPtr control_accelerate);

    void tp_control_brake(can_msgs::msg::AdControlBrake::SharedPtr control_brake);

    void tp_control_steering(can_msgs::msg::AdControlSteering::SharedPtr control_steering);
    void tp_emergency(can_msgs::msg::Emergency::SharedPtr stop);
    void tp_init_callback(can_msgs::msg::Init::SharedPtr init);

public :

    void fn_can_run();

    void fn_send_rpm(const float &rpm, const std::chrono::system_clock::time_point &cur_time);


    CanMGR();

    virtual ~CanMGR();

};

#endif
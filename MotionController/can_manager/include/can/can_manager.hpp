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
    std::chrono::_V2::system_clock::time_point callback_time_; // current callback time
    std::chrono::_V2::system_clock::time_point old_time_; // Previous callback time
    std::unique_ptr<Constants> constants_;
    rclcpp::Subscription<can_msgs::msg::AdControlBody>::SharedPtr sub_body_;
    rclcpp::Subscription<can_msgs::msg::AdControlAccelerate>::SharedPtr sub_accelerate_;
    rclcpp::Subscription<can_msgs::msg::AdControlBrake>::SharedPtr sub_brake_;
    rclcpp::Subscription<can_msgs::msg::AdControlSteering>::SharedPtr sub_steering_;
    rclcpp::CallbackGroup::SharedPtr cbg_body;
    int fn_can_init(); // can callback function register
    void faultCallback(int can_falut, int dbs_fault);

    void rpmCallback(int mcu_shift, int mcu_speed, int mcu_torque);

    void bmsCallback(int sys_sts,int soc);
    void vehicleErrorCallback(int error_code, int low_voltage);
    void vehicleStatus2Callback(int brake_press, float speed);
    void log(std::string call_name);

    void tp_control_body_callback(can_msgs::msg::AdControlBody::SharedPtr control_body);

    void tp_control_accelerate(can_msgs::msg::AdControlAccelerate::SharedPtr control_accelerate);

    void tp_control_brake(can_msgs::msg::AdControlBrake::SharedPtr control_brake);

    void tp_control_steering(can_msgs::msg::AdControlSteering::SharedPtr control_steering);


public :

    void fn_can_run();

    void fn_send_rpm(const float &rpm, const std::chrono::system_clock::time_point &cur_time);


    CanMGR();

    virtual ~CanMGR();

};

#endif
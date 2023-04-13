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
#include "can/data_relayer.hpp"
#include "can/i_can_connect.hpp"

using std::placeholders::_1;

//extern int optind, opterr, optopt;
//static char *progname;
static volatile int state = 1;
/**
 * @brief 
 * @param signo 
 */
static void sigterm(int signo)
{
  fprintf(stdout, "SIGNAL %d  in main\n", signo);
	state = 0;
}

/**
 * @brief Class controlled by robot motion can communication
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.05
 */
class WmMotionController : public rclcpp::Node, public ICanConnect{
    private :
        const int m_steer_max_ang;
        const int m_tp_queue_size;
        const std::string m_tp_cmdvel;
        const std::string m_tp_can_chw;
      
        DataRelayer obj;
        rclcpp::TimerBase::SharedPtr m_timer;
        rclcpp::CallbackGroup::SharedPtr m_cb_group_cmd_vel;
        rclcpp::CallbackGroup::SharedPtr m_cb_group_can_chw;
        rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr m_sub_cmdvel;
        rclcpp::Subscription<can_msgs::msg::ControlHardware>::SharedPtr m_sub_can_chw;

        int fn_can_init(); // Register callback function for can communication response
        void fn_cmdvel_callback(const geometry_msgs::msg::Twist::SharedPtr cmd_vel);
        void fn_can_chw_callback(const can_msgs::msg::ControlHardware::SharedPtr can_chw);
        void faultCallback(int can_falut,int dbs_fault);
        void rpmCallback(int remote_f_horn,int remote_d_headlight,int remote_b_motor_holding_brake);
        void fn_can_run();
        float fn_mps2kmph(float mps);
        float fn_kmph2mps(float kmph);
    public :
        WmMotionController();
        virtual ~WmMotionController();
};

#endif
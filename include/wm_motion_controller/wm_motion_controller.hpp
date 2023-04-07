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

// define header file
#include "wm_motion_controller/df_motion_controller.hpp"

#include "can/data_relayer.hpp"

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
class WmMotionController : public rclcpp::Node{
    private :
        const int m_steer_max_ang;
        const int m_steer_max_ang_cal;
        int fn_can_init(); // Register callback function for can communication response

        void fn_cmdvel_callback(const geometry_msgs::msg::Twist::SharedPtr cmd_vel);

        

        rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr m_sub_cmdvel;
    public :
        WmMotionController();
        virtual ~WmMotionController();
        void faultCallback(int can_falut,int dbs_fault);
};

#endif
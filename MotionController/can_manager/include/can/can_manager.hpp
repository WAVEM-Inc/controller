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
#include "rclcpp/rclcpp.hpp"
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
 * @brief Class to control CAN communication
 * @author changunAn(changun516@wavem.net)
 * @see enable_shared_from_this
 * @see ICanConnect
 * @see IMotionColleague
 * @warning Be careful of problems caused by Mutex
 */
#include "rclcpp/rclcpp.hpp"
class CanMGR :public rclcpp::Node{
//class CanMGR{
    private :

  
        DataRelayer obj_; // Member variables for calling Can-related functions
        std::chrono::_V2::system_clock::time_point callback_time_; // current callback time
        std::chrono::_V2::system_clock::time_point old_time_; // Previous callback time
        int fn_can_init(); // can callback function register 
        void faultCallback(int can_falut,int dbs_fault);
        void rpmCallback(int mcu_shift,int mcu_speed,int mcu_torque);
        void log(std::string call_name);

        //
        int test_num;
    public :
        void static_break(bool flag);
        void static_break(UGV::BREAK break_status);
        void fn_can_run();
        void fn_send_control_hardware(bool horn,bool head_light,bool right_light,bool left_light);
        void fn_send_control_steering(float angular);
        void fn_send_control_vel(float linear);
        void fn_send_value(const int& value);
        void fn_recv_value(const int& value);
        void fn_send_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time);
        void fn_recv_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time);
        

        CanMGR();

        virtual ~CanMGR();

};
#endif
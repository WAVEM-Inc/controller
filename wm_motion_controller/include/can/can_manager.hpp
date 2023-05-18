#ifndef CAN_MANAGER
#define CAN_MANAGER

//can

// can header file
#include "can/data_relayer.hpp"
#include "can/i_can_connect.hpp"

// linux header file 
#include <unistd.h> //sleep

#include "mediator/i_motion_mediator.hpp"
#include "colleague/i_motion_colleague.hpp"
#include <iomanip>
#include <chrono> // time
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
 * @brief Class to control CAN communication
 * @author changunAn(changun516@wavem.net)
 * @see enable_shared_from_this
 * @see ICanConnect
 * @see IMotionColleague
 * @warning Be careful of problems caused by Mutex
 */
class CanMGR:public ICanConnect, public IMotionColleague, public std::enable_shared_from_this<CanMGR>{
    private :
        DataRelayer obj_; // Member variables for calling Can-related functions
        std::chrono::_V2::system_clock::time_point callback_time_; // current callback time
        std::chrono::_V2::system_clock::time_point old_time_; // Previous callback time
        int fn_can_init(); // can callback function register 
        void faultCallback(int can_falut,int dbs_fault);
        void rpmCallback(int mcu_shift,int mcu_speed,int mcu_torque);

        void log(std::string call_name);
    public :
        void fn_can_run();
        void fn_send_control_hardware(bool horn,bool head_light,bool right_light,bool left_light);
        void fn_send_control_steering(float angular);
        void fn_send_control_vel(float linear);
        void fn_send_value(const int& value) override;
        void fn_recv_value(const int& value) override;
        void fn_send_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time) override;
        void fn_recv_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time) override;
        
        CanMGR(std::shared_ptr<IMotionMediator> motion_colleague);

        virtual ~CanMGR();

};
#endif
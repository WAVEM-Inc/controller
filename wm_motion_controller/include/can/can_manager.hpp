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

class CanMGR:public ICanConnect, public IMotionColleague{
    private :
        DataRelayer obj;
        //WmMotionController* m_wmc;
        int fn_can_init();
        void faultCallback(int can_falut,int dbs_fault);
        void rpmCallback(int remote_f_horn,int remote_d_headlight,int remote_b_motor_holding_brake);
    public :
        void fn_can_run();
        void fn_send_control_hardware(bool horn,bool head_light,bool right_light,bool left_light);
        void fn_send_control_steering(float angular);
        void fn_send_control_vel(float linear);
        //void fn_set_m_wmc(WmMotionController& wmc);
        void fn_send_value(const int& value) override;
        void fn_recv_value(const int& value) override;
        CanMGR(IMotionMediator* motion_colleague);
        virtual ~CanMGR();

};

#endif
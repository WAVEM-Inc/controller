#ifndef CAN_MANAGER
#define CAN_MANAGER

// can header file
#include "can/data_relayer.hpp"
#include "can/i_can_connect.hpp"

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

class CanMGR:public ICanConnect{
    private :
        DataRelayer obj;
        int fn_can_init();
        void faultCallback(int can_falut,int dbs_fault);
        void rpmCallback(int remote_f_horn,int remote_d_headlight,int remote_b_motor_holding_brake);
    public :
        void fn_run();
        CanMGR();
        virtual ~CanMGR();

};

#endif
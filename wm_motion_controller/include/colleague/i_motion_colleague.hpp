#ifndef MOTION_COLLEAGUE
#define MOTION_COLLEAGUE
#include "mediator/i_motion_mediator.hpp"
class IMotionMediator;
class IMotionColleague{
    public : 
        IMotionColleague(IMotionMediator* motion_mediator);
        virtual void fn_send_value(const int& value)=0;
        virtual void fn_recv_value(const int& value)=0;

    protected :
       IMotionMediator* m_i_motion_mediator; 

};
#endif
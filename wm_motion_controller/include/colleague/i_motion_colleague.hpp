#ifndef MOTION_COLLEAGUE
#define MOTION_COLLEAGUE
#include "mediator/i_motion_mediator.hpp"
#include <memory>
class IMotionMediator;
class IMotionColleague{
    public : 
        IMotionColleague(std::shared_ptr<IMotionMediator> motion_mediator):m_i_motion_mediator(motion_mediator){};
        virtual void fn_recv_value(const int& value)=0;
        virtual void fn_send_value(const int& value)=0;
    protected :
       std::shared_ptr<IMotionMediator> m_i_motion_mediator; 

};
#endif
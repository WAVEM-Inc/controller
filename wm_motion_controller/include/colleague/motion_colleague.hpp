#ifndef MOTION_COLLEAGUE
#define MOTION_COLLEAGUE
#include "mediator/i_motion_mediator.hpp"
class MotionColleague{
    public : 
        MotionColleague(IMotionMediator* motion_mediator);
    protected :
       IMotionMediator* m_i_motion_mediator; 

};
#endif
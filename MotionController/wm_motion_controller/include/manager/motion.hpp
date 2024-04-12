#ifndef MANAGER__MOTION__HPP__
#define MANAGER__MOTION__HPP__

#include "entity/df_ugv.hpp"
class IMotion{
    public :

        virtual void fn_can_send_steering(float angular)=0;
        virtual void fn_can_send_vel(float linear)=0;
        virtual void fn_can_send_break(UGV::BREAK break_status)=0;
};

#endif
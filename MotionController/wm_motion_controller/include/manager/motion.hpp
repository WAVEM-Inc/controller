#ifndef MANAGER__MOTION__HPP__
#define MANAGER__MOTION__HPP__

#include "can_msgs/msg/control_hardware.hpp"
#include "entity/df_ugv.hpp"
class IMotion{
    public :
   
        virtual void fn_can_send_led_and_horn(const can_msgs::msg::ControlHardware::SharedPtr can_chw)=0;
        virtual void fn_can_send_steering(float angular)=0;
        virtual void fn_can_send_vel(float linear)=0;
        virtual void fn_can_send_break(UGV::BREAK break_status)=0;
};

#endif
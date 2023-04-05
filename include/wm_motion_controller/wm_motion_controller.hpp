#ifndef MOTION_CONTROLLER
#define MOTION_CONTROLLER
// cpp header file
#include <iostream>

// ros2 header file
#include"rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
/**
 * @brief 
 * 
 */
class WmMotionController : public rclcpp::Node{
    private :
        int acmotor_pulse;
        int acmotor_pulse_flag;
        float ac_angular_bak;
        int fn_light_init();
        int fn_light_set_val(int light_val);
        int fn_can_motor_init();
        int fn_dcmotor_disable();
        int fn_dcmotor_set_speed(int motor,float speed);
        void* fn_do_acmotor(void* arg);
        int fn_init_ac();
        int fn_write_ac_pulse(int num);
        void fn_cmdvel_callback(const geometry_msgs::msg::Twist::SharedPtr twist_aux);
       
    public :
        WmMotionController();
        virtual ~WmMotionController();
};

#endif
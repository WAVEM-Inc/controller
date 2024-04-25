//
// Created by nuc-bt on 24. 4. 8.
//

#ifndef CAN_MANAGER_CONSTANTS_HPP
#define CAN_MANAGER_CONSTANTS_HPP
#define TP_NAME_CONTROL_BODY "/drive/can/ad_control_body"
#define TP_NAME_CONTROL_ACCELERATE "/drive/can/ad_control_accelerate"
#define TP_NAME_CONTROL_BRAKE "/drive/can/ad_control_brake"
#define TP_NAME_CONTROL_STEERING "/drive/can/ad_control_steering"

//
#define TP_NAME_TORQUE_FEEDBACK "/drive/can/vcu/torque_feedback"
#define TP_NAME_BMS "/sensor/battery/state"
#define TP_NAME_VELOCITY "/drive/velocity/state"
#define TP_NAME_EMERGENCY "/drive/can/emergency"
#define TP_NAME_INIT "/drive/can/init"

#include<iostream>
class Constants {
public:
    explicit Constants():
            tp_name_control_body_(TP_NAME_CONTROL_BODY),
            tp_name_control_accelerate_(TP_NAME_CONTROL_ACCELERATE),
            tp_name_control_brake_(TP_NAME_CONTROL_BRAKE),
            tp_name_control_steering_(TP_NAME_CONTROL_STEERING),
            tp_name_state_rpm_(TP_NAME_TORQUE_FEEDBACK),
            tp_name_state_bms_(TP_NAME_BMS),
            tp_name_state_velocity_(TP_NAME_VELOCITY),
            tp_name_emergency_(TP_NAME_EMERGENCY),
            tp_name_init_(TP_NAME_INIT)
    {}
    const std::string tp_name_control_body_;
    const std::string tp_name_control_accelerate_;
    const std::string tp_name_control_brake_;
    const std::string tp_name_control_steering_;
    const std::string tp_name_state_rpm_;
    const std::string tp_name_state_bms_;
    const std::string tp_name_state_velocity_;
    const std::string tp_name_emergency_;
    const std::string tp_name_init_;
};


#endif //CAN_MANAGER_CONSTANTS_HPP

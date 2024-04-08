//
// Created by nuc-bt on 24. 4. 8.
//

#ifndef CAN_MANAGER_CONSTANTS_HPP
#define CAN_MANAGER_CONSTANTS_HPP
#define TP_NAME_CONTROL_BODY "/drive/can/ad_control_body"
#define TP_NAME_CONTROL_ACCELERATE "/drive/can/ad_control_accelerate"
#define TP_NAME_CONTROL_BRAKE "/drive/can/ad_control_brake"
#define TP_NAME_CONTROL_STEERING "/drive/can/ad_control_steering"

#include<iostream>
class Constants {
public:
    explicit Constants():
            tp_name_control_body_(TP_NAME_CONTROL_BODY),
            tp_name_control_accelerate_(TP_NAME_CONTROL_ACCELERATE),
            tp_name_control_brake_(TP_NAME_CONTROL_BRAKE),
            tp_name_control_steering_(TP_NAME_CONTROL_STEERING)
    {}
    const std::string tp_name_control_body_;
    const std::string tp_name_control_accelerate_;
    const std::string tp_name_control_brake_;
    const std::string tp_name_control_steering_;
};


#endif //CAN_MANAGER_CONSTANTS_HPP

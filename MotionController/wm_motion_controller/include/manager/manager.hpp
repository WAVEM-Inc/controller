#ifndef MOTION_CONTROLLER__MANAGER__HPP__
#define MOTION_CONTROLLER__MANAGER__HPP__
//can header
#include "can/can_manager.hpp"
// motion_controller header
#include "wm_motion_controller/wm_motion_controller.hpp"
//
#include "common/common.hpp"
#include "manager/motion.hpp"
#include "manager/i_can.hpp"
//defualt header
#include <memory>
#include <map>
class WmMotionController;
class CanMGR;
class IMotion;
class ICAN;
class Manager : public IMotion,ICAN{
    public :
        Manager();
        virtual ~Manager();
        void fn_run();
        void fn_map_up(std::string key, MANAGER::SETUP value);
        //
     

        // motion
        void fn_can_send_led_and_horn(const can_msgs::msg::ControlHardware::SharedPtr can_chw) override;
        void fn_can_send_steering(float angular) override;
        void fn_can_send_vel(float linear) override;
        void fn_can_send_break(UGV::BREAK break_status) override;
       

        // can
        void can_send_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time) override;
       

    private : 
        std::map<std::string,MANAGER::SETUP> map_setup_;
        std::shared_ptr<CanMGR> can_manager_;
        std::shared_ptr<WmMotionController> wm_motion_controller_;
};

#endif
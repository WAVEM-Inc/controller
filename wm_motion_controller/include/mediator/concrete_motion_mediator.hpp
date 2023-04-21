#ifndef MOTION_MEDIATOR
#define MOTION_MEDIATOR
#include"mediator/i_motion_mediator.hpp"
#include"can/can_manager.hpp"
#include"wm_motion_controller/wm_motion_controller.hpp"

class WmMotionController;
class ConcreteMotionMediator : public IMotionMediator{
    public :
        void fn_set_can_mgr(CanMGR* can_mgr);
        void fn_set_wm_motion_controller(WmMotionController* wm_motion_controller);
        void fn_send_value(const int& value, IMotionColleague* sender) override;
    private : 
        CanMGR* m_can_mgr;
        WmMotionController* m_wm_motion_controller;
};

#endif
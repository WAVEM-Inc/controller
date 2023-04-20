#ifndef MOTION_MEDIATOR
#define MOTION_MEDIATOR
#include"mediator/i_motion_mediator.hpp"
#include"can/can_manager.hpp"
#include "wm_motion_controller/wm_motion_controller.hpp"
class ConcreteMotionMediator : public IMotionMediator{
    public :
        ConcreteMotionMediator(CanMGR* can_mgr,WmMotionController* wm_motion_controller);

        void fn_send_value_to_wm_motion_controller(int value) override;
    private : 
        CanMGR* m_can_mgr;
        WmMotionController* m_wm_motion_controller;
};

#endif
#ifndef MOTION_MEDIATOR
#define MOTION_MEDIATOR
#include"mediator/i_motion_mediator.hpp"
#include"can/can_manager.hpp"
#include"wm_motion_controller/wm_motion_controller.hpp"
#include <mutex>

class WmMotionController;
class ConcreteMotionMediator : public IMotionMediator{
    public :
        void fn_set_can_mgr(std::shared_ptr<CanMGR> can_mgr);
        void fn_set_wm_motion_controller(std::shared_ptr<WmMotionController> wm_motion_controller);
        void fn_send_value(const int& value, std::shared_ptr<IMotionColleague> sender) override;
    private : 
        std::shared_ptr<CanMGR> m_can_mgr;
        std::shared_ptr<WmMotionController> m_wm_motion_controller;
        std::mutex m_mutex; 
};

#endif
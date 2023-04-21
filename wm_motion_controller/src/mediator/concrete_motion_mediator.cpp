#include"mediator/concrete_motion_mediator.hpp"

void ConcreteMotionMediator::fn_set_wm_motion_controller(WmMotionController* wm_motion_controller){
    m_wm_motion_controller=wm_motion_controller;
}
void ConcreteMotionMediator::fn_set_can_mgr(CanMGR* can_mgr){
    m_can_mgr = can_mgr;
}

void ConcreteMotionMediator::fn_send_value(const int& value,IMotionColleague* sender){
    std::cout<<"test1"<<std::endl;
   if(sender == m_can_mgr){
        std::cout<<"test2"<<std::endl;
        m_wm_motion_controller->fn_recv_value(value);
   }
   else if(sender == m_wm_motion_controller){
        std::cout<<"test3"<<std::endl;
        m_can_mgr->fn_recv_value(value);
   }
}
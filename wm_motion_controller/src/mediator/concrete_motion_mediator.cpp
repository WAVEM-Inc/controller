#include"mediator/concrete_motion_mediator.hpp"

void ConcreteMotionMediator::fn_set_wm_motion_controller(std::shared_ptr<WmMotionController> wm_motion_controller){
    m_wm_motion_controller=wm_motion_controller;
}
void ConcreteMotionMediator::fn_set_can_mgr(std::shared_ptr<CanMGR> can_mgr){
    m_can_mgr = can_mgr;
}

void ConcreteMotionMediator::fn_send_value(const int& value,std::shared_ptr<IMotionColleague> sender){
    std::cout<<"test1"<<std::endl;
   if(sender == m_can_mgr){
        std::cout<<"test2"<<std::endl;
        std::lock_guard<std::mutex> lock(m_mutex); // 뮤텍스 락
        m_wm_motion_controller->fn_recv_value(value);
   }
   else if(sender == m_wm_motion_controller){
        std::cout<<"test3"<<std::endl;
        std::lock_guard<std::mutex> lock(m_mutex); // 뮤텍스 락
        m_can_mgr->fn_recv_value(value);
   }
}
#include"mediator/concrete_motion_mediator.hpp"
/**
 * @brief WmMotionController Handed Over to Arbitrator
 * @author changunAn(changun516@wavem.net)
 * @param wm_motion_controller 
 */
void ConcreteMotionMediator::fn_set_wm_motion_controller(std::shared_ptr<WmMotionController> wm_motion_controller){
    m_wm_motion_controller=wm_motion_controller;
}

/**
 * @brief CanMGR Handed Over to Arbitrator
 * @author changunAn(changun516@wavem.net)
 * @param can_mgr 
 */
void ConcreteMotionMediator::fn_set_can_mgr(std::shared_ptr<CanMGR> can_mgr){
    m_can_mgr = can_mgr;
}
/**
 * @brief Data exchange through arbitrator, lock to prevent other data from entering
 * @author changunAn(changun516@wavem.net)
 * @param value 
 * @param sender 
 */
void ConcreteMotionMediator::fn_send_value(const int& value,std::shared_ptr<IMotionColleague> sender){

}

/**
 * @brief 
 * 
 * @param rpm 
 * @param cur_time 
 * @param sender 
 */
void ConcreteMotionMediator::fn_send_rpm(const float& rpm, const std::chrono::system_clock::time_point cur_time, std::shared_ptr<IMotionColleague> sender){


}

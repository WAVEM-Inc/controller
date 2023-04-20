#include"mediator/concrete_motion_mediator.hpp"

ConcreteMotionMediator::ConcreteMotionMediator(CanMGR* can_mgr,WmMotionController* wm_motion_controller)
:m_can_mgr(can_mgr),
m_wm_motion_controller(wm_motion_controller){

}
void ConcreteMotionMediator::fn_send_value_to_wm_motion_controller(int value){
   //m_wm_motion_controller->fn_wm_motion_controller_function(value);
}
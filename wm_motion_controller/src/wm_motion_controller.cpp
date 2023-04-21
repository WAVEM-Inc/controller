#include "wm_motion_controller/wm_motion_controller.hpp"
/**
 * @brief Construct a new Wm Motion Controller:: Wm Motion Controller object
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.06
 */
WmMotionController::WmMotionController(IMotionMediator* motion_mediator,CanMGR* can_mgr)
:Node("WmMotionControllerNode"),
IMotionColleague(motion_mediator),
m_can_manager(can_mgr),
m_steer_max_ang(STEER_MAX_ANGLE),
m_tp_cmdvel(TP_CMDVEL),
m_tp_queue_size(TP_QUEUE_SIZE),
m_tp_can_chw(TP_CONTROL_HARD_WARE){
	std::cout<<"WmMotionContoller Start"<<std::endl;
	
	//m_can_manager = new CanMGR(motion_mediator);

	m_cb_group_cmd_vel = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
	m_cb_group_can_chw = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
	rclcpp::SubscriptionOptions sub_cmdvel_options;
	rclcpp::SubscriptionOptions sub_can_chw_options;
	sub_cmdvel_options.callback_group = m_cb_group_cmd_vel;
	sub_can_chw_options.callback_group = m_cb_group_can_chw;
	m_sub_cmdvel = this->create_subscription<geometry_msgs::msg::Twist>(m_tp_cmdvel,m_tp_queue_size,std::bind(&WmMotionController::fn_cmdvel_callback,this,_1),sub_cmdvel_options);
	m_sub_can_chw = this->create_subscription<can_msgs::msg::ControlHardware>(m_tp_can_chw,m_tp_queue_size,std::bind(&WmMotionController::fn_can_chw_callback,this,_1),sub_can_chw_options);
	
	std::thread thread_run(&CanMGR::fn_can_run,m_can_manager);
    thread_run.detach();
}
WmMotionController::~WmMotionController(){

}


void WmMotionController::fn_can_chw_callback(const can_msgs::msg::ControlHardware::SharedPtr can_chw){
	std::cout<< "chw_callback : "<< can_chw->horn << " : " << can_chw->head_light <<" : "<<can_chw->right_light<<" : "<<can_chw->left_light<<std::endl; 
	m_can_manager->fn_send_control_hardware(can_chw->horn,can_chw->head_light,can_chw->right_light,can_chw->left_light);
}

/**
 * @brief cmd_vel receive function for robot control
 * @param twist_aux Received cmd_vel data
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.06
 */
void WmMotionController::fn_cmdvel_callback(const geometry_msgs::msg::Twist::SharedPtr cmd_vel){
	float vel_linear = 0,vel_angular = 0;
	vel_linear = cmd_vel->linear.x;
	vel_angular = cmd_vel->angular.z;
    RCLCPP_INFO(this->get_logger(),"linear = %.02f,angular = %.02f\n", vel_linear, vel_angular);
	m_can_manager->fn_send_control_steering(vel_angular);
	m_can_manager->fn_send_control_vel(vel_linear);
}

/**
 * @brief m/s to km/h
 * @param mps 
 * @return float 
 */
float WmMotionController::fn_mps2kmph(float mps){
	return mps * 3600 / 1000;  // mps를 kmph로 변환
}

float WmMotionController::fn_kmph2mps(float kmph){
	return kmph * 1000 / 3600;  // kmph를 mps로 변환
}


void WmMotionController::fn_send_value(const int& value){
    std::cout<< "override WmMotionController"<<std::endl;
    m_i_motion_mediator->fn_send_value(value,this);
}

void WmMotionController::fn_recv_value(const int& value){
    std::cout<< "override WmMotionController "<<value<<std::endl;

}

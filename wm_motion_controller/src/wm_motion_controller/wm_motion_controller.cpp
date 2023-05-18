#include "wm_motion_controller/wm_motion_controller.hpp"
#include "converter/ugv_converter.hpp"

/**
 * @brief Construct a new Wm Motion Controller:: Wm Motion Controller object
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.06
 */
WmMotionController::WmMotionController(std::shared_ptr<IMotionMediator> motion_mediator,std::shared_ptr<CanMGR> can_mgr)
:Node("WmMotionControllerNode"),
IMotionColleague(motion_mediator),
m_can_manager(can_mgr),
m_steer_max_ang(STEER_MAX_ANGLE),
m_tp_cmdvel(TP_CMDVEL),
m_tp_queue_size(TP_QUEUE_SIZE),
m_tp_can_chw(TP_CONTROL_HARD_WARE){
	std::cout<<"WmMotionContoller Start"<<std::endl;
	
	//m_can_manager = new CanMGR(motion_mediator);
	//
	prev_ugv_ = std::make_shared<ENTITY::UGV>();
	(*prev_ugv_).set_cur_rpm(0);
	(*prev_ugv_).set_cur_time(std::chrono::system_clock::now());
	cur_ugv_ = std::make_shared<ENTITY::UGV>();
	//

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

/**
 * @brief Callback function for controlling horn, light, when can_msgs:msgControlHardWare message is received
 * @author changunAn(changun516@wavem.net)
 * @param can_chw 
 */
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
    RCLCPP_INFO(this->get_logger(),"!!!!!!@@@@@@linear = %.02f,angular = %.02f\n", vel_linear, vel_angular);
	m_can_manager->fn_send_control_steering(vel_angular);
	m_can_manager->fn_send_control_vel(vel_linear);
}

/**
 * @brief m/s to km/h
 * @param mps 
 * @author changunAn(changun516@wavem.net)
 * @return float 
 */
float WmMotionController::fn_mps2kmph(float mps){
	return mps * 3600 / 1000;  // mps를 kmph로 변환
}
/**
 * @brief km/h to m/s
 * @param kmph 
 * @author changunAn(changun516@wavem.net)
 * @return float 
 */
float WmMotionController::fn_kmph2mps(float kmph){
	return kmph * 1000 / 3600;  // kmph를 mps로 변환
}


/**
 * @brief Function for sending data to CanMGR via arbitrator
 * @author changunAn(changun516@wavem.net)
 * @param value 
 */
void WmMotionController::fn_send_value(const int& value){
    std::cout<< "override WmMotionController"<<std::endl;
    m_i_motion_mediator->fn_send_value(value,enable_shared_from_this<WmMotionController>::shared_from_this());
}
/**
 * @brief Function for receiving data from CanMGR through arbitrator
 * @author changunAn(changun516@wavem.net)
 * @param value 
 */
void WmMotionController::fn_recv_value(const int& value){
    std::cout<< "override WmMotionController "<<value<<std::endl;

}

void WmMotionController::fn_send_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time){
	
}
/**
 * @brief RPM data coming over CAN communication
 * 
 * @param rpm 
 * @param cur_time 
 */
void WmMotionController::fn_recv_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time){
	//
    std::unique_ptr<CONVERTER::UGVConverter> converter = std::make_unique<CONVERTER::UGVConverter>();
	(*converter).rpm_to_distance(*prev_ugv_,*cur_ugv_);
	//
}
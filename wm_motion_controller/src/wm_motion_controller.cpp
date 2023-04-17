#include "wm_motion_controller/wm_motion_controller.hpp"
/**
 * @brief Construct a new Wm Motion Controller:: Wm Motion Controller object
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.06
 */
WmMotionController::WmMotionController()
:Node("WmMotionControllerNode"),m_steer_max_ang(STEER_MAX_ANGLE),m_tp_cmdvel(TP_CMDVEL),m_tp_queue_size(TP_QUEUE_SIZE),m_tp_can_chw(TP_CONTROL_HARD_WARE){
	std::cout<<"WmMotionContoller Start"<<std::endl;
	fn_can_init();
	m_cb_group_cmd_vel = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
	m_cb_group_can_chw = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
	rclcpp::SubscriptionOptions sub_cmdvel_options;
	rclcpp::SubscriptionOptions sub_can_chw_options;
	sub_cmdvel_options.callback_group = m_cb_group_cmd_vel;
	sub_can_chw_options.callback_group = m_cb_group_can_chw;
	m_sub_cmdvel = this->create_subscription<geometry_msgs::msg::Twist>(m_tp_cmdvel,m_tp_queue_size,std::bind(&WmMotionController::fn_cmdvel_callback,this,_1),sub_cmdvel_options);
	m_sub_can_chw = this->create_subscription<can_msgs::msg::ControlHardware>(m_tp_can_chw,m_tp_queue_size,std::bind(&WmMotionController::fn_can_chw_callback,this,_1),sub_can_chw_options);
	
	std::thread thread_run(&WmMotionController::fn_can_run,this);
    thread_run.detach();
}
WmMotionController::~WmMotionController(){

}
/**
 * @brief Register callback function for can communication response
 * @return int Verify function normal termination
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.06
 */
int WmMotionController::fn_can_init(){
	obj.RegistFaultCallback<WmMotionController>(this, &WmMotionController::faultCallback);
	obj.RegistRpmCallback<WmMotionController>(this, &WmMotionController::rpmCallback);
    return 0;
}

/**
 * @brief can run function
 * @date 23.04.10
 * @author changunAn(changun516@wavem.net)
 */
void WmMotionController::fn_can_run(){
	std::cout << "***can run start!!!***" << std::endl;
	obj.Run();
	while(state){
		sleep(5);
	}
	std::cout << "***can end!!!***" << std::endl;
}
void WmMotionController::fn_can_chw_callback(const can_msgs::msg::ControlHardware::SharedPtr can_chw){
	std::cout<< "chw_callback : "<< can_chw->horn << " : " << can_chw->head_light <<" : "<<can_chw->right_light<<" : "<<can_chw->left_light<<std::endl; 
	obj.ControlHardware(can_chw->horn,can_chw->head_light,can_chw->right_light,can_chw->left_light);
}

/**
 * @brief 
 * @param can_falut 0x0: no fault
 * 0X1: invalid connection
 * @param dbs_fault 0x0: no fault
 * 0X1: oil pressure sensor failure
 * 0X2: Insufficient system power supply
 * 0X4: Controller temperature is too high
 * 0X8: Motor failure
 * 0X10: The controller itself is faulty
 * 0X20: Oil pressure command message lost
 * 0X40: CAN BUS OFF
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.07
 */
void WmMotionController::faultCallback(int can_falut,int dbs_fault){
	  std::cout << "[main] callback DBS_Status : " << (int)can_falut<< "," << (int)dbs_fault<< std::endl; 
}

/**
 * @brief 
 * 
 * @param remote_f_horn 
 * @param remote_d_headlight 
 * @param remote_b_motor_holding_brake 
 */
void WmMotionController::rpmCallback(int remote_f_horn
                    ,int remote_d_headlight
                    ,int remote_b_motor_holding_brake
                    ){

  cout << "[main] callback RPM Status : " << (int)remote_f_horn
  << "," << (int)remote_d_headlight
  << "," << (int)remote_b_motor_holding_brake
  << endl;
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
	obj.ControlSteering(vel_angular);
	obj.ControlVel(vel_linear);
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


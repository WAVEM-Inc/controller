#include "wm_motion_controller/wm_motion_controller.hpp"
/**
 * @brief Construct a new Wm Motion Controller:: Wm Motion Controller object
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.06
 */
WmMotionController::WmMotionController()
:Node("WmMotionControllerNode"),m_steer_max_ang(STEER_MAX_ANGLE),m_steer_max_ang_cal(STEER_MAX_ANGLE_CAL){
	std::cout<<"WmMotionContoller Start"<<std::endl;
	fn_can_init();
	m_cb_group_cmd_vel = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
	rclcpp::SubscriptionOptions sub_cmdvel_options;
	m_sub_cmdvel = this->create_subscription<geometry_msgs::msg::Twist>("/cmd_vel",10,std::bind(&WmMotionController::fn_cmdvel_callback,this,_1));
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
	//float ac_state = 0;
	float steer_angle = 0, steer_val = 0;
	vel_linear = cmd_vel->linear.x;
	vel_angular = cmd_vel->angular.z;
    RCLCPP_INFO(this->get_logger(),"linear = %.02f,angular = %.02f\n", vel_linear, vel_angular);
    steer_angle= (vel_angular)/(0.0001+vel_linear*2);
    if(steer_angle > m_steer_max_ang){
		steer_angle = m_steer_max_ang;
	}
	else if(steer_angle < -m_steer_max_ang){
		steer_angle = -m_steer_max_ang;
	}
	steer_val = steer_angle/m_steer_max_ang; // 차후 수정
	if((std::fabs(steer_val) <= m_steer_max_ang_cal ) ){
		//acmotor_pulse = acmotor_pulse+steer_val-ac_angular_bak;
		//ac_angular_bak = steer_val;
	}    
}


/**
 * @brief The main function of the WmMotionController node.
 * @param argc int paramter , Number of factors delivered at the start of the program
 * @param argv char**, The factors you gave me at the start of the program
 * @return int Program normal operation
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.06
 */
int main(int argc, char** argv){
    rclcpp::init(argc, argv);
	std::cout<<"main start"<<std::endl;
    auto node = std::make_shared<WmMotionController>();
    rclcpp::spin(node);	
	rclcpp::shutdown();
	return 0;
}
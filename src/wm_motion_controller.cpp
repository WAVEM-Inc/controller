#include "wm_motion_controller/wm_motion_controller.hpp"
/**
 * @brief Construct a new Wm Motion Controller:: Wm Motion Controller object
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.06
 */
WmMotionController::WmMotionController()
:Node("WmMotionControllerNode"),m_steer_max_ang(STEER_MAX_ANGLE),m_steer_max_ang_cal(STEER_MAX_ANGLE_CAL){

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
	DataRelayer obj;
	//std::function<void(WmMotionController&, int,int)> func = &WmMotionController::faultCallback;
	//void(WmMotionController::*pfunc)(int,int);
	//obj.RegistFaultCallback(this,pfunc);
	int a= 1,b=2;
	obj.RegistFaultCallback<WmMotionController>(this, &WmMotionController::faultCallback);

    return 0;
}

void WmMotionController::faultCallback(int can_falut,int dbs_fault){
	  std::cout << "[main] callback DBS_Status : " << (int)can_falut<< "," << (int)dbs_fault<< std::endl;
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
    auto node = std::make_shared<WmMotionController>();
    rclcpp::spin(node);	
	rclcpp::shutdown();
	return 0;
}
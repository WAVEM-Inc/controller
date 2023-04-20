#include"can/can_manager.hpp"
CanMGR::CanMGR(IMotionMediator* motion_mediator):MotionColleague(motion_mediator){
    fn_can_init();
}
void CanMGR::fn_can_run(){
	std::cout << "***can run start!!!***" << std::endl;
	while(state){
		sleep(5);
	}
	std::cout << "***can end!!!***" << std::endl;
}

/**
 * @brief Register callback function for can communication response
 * @return int Verify function normal termination
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.06
 */
int CanMGR::fn_can_init(){
	obj.RegistFaultCallback<CanMGR>(this, &CanMGR::faultCallback);
	obj.RegistRpmCallback<CanMGR>(this, &CanMGR::rpmCallback);
    obj.Run();
    return 0;
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
void CanMGR::faultCallback(int can_falut,int dbs_fault){
	  std::cout << "[main] callback DBS_Status : " << (int)can_falut<< "," << (int)dbs_fault<< std::endl; 
}


/**
 * @brief 
 * @param remote_f_horn 
 * @param remote_d_headlight 
 * @param remote_b_motor_holding_brake 
 */
void CanMGR::rpmCallback(int remote_f_horn
                    ,int remote_d_headlight
                    ,int remote_b_motor_holding_brake
                    ){

  std::cout << "[can_manager] callback RPM Status : " << (int)remote_f_horn
  << "," << (int)remote_d_headlight
  << "," << (int)remote_b_motor_holding_brake
  << std::endl;
}

void CanMGR::fn_send_control_hardware(bool horn,bool head_light,bool right_light,bool left_light){
    obj.ControlHardware(horn,head_light,right_light,left_light);
}
void CanMGR::fn_send_control_steering(float angular){
    obj.ControlSteering(angular);
}

void CanMGR::fn_send_control_vel(float linear){
    obj.ControlVel(linear);
}

CanMGR::~CanMGR(){
    
}
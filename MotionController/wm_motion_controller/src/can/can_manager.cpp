#include"can/can_manager.hpp"
#include <unistd.h>

#include "manager/manager.hpp"
/**
 * @brief Construct a new Can M G R:: Can M G R object
 * @author changunAn(changun516@wavem.net)
 * @param motion_mediator 
 */
CanMGR::CanMGR(std::shared_ptr<Manager> manager):manager_(manager){    
    fn_can_init();
    manager_->fn_map_up("CanMGR",MANAGER::SETUP::START);
}

/**
 * @brief can operation function
 * @author changunAn(changun516@wavem.net)
 */
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
	//obj_.RegistFaultCallback<CanMGR>(this, &CanMGR::faultCallback);
	obj_.RegistRpmCallback<CanMGR>(this, &CanMGR::rpmCallback);
    //obj_.RegistRequestCallback<CanMGR>(this,&CanMGR::requestCallback);
    obj_.Run();
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
 * @brief  Function to respond to rpm reception through can communication
 * @details DataRelayer::Handler_MCU_Torque_Feedback
 * @author changunAn(changun516@wavem.net)
 * @param mcu_shift : msg.mcu_shift 
 * @param mcu_speed : msg.mcu_speed -- rpm
 * @param mcu_torque : msg.mcu_torque //
 * @see DataRelayer
 */
void CanMGR::rpmCallback(int mcu_shift
                    ,int mcu_speed
                    ,int mcu_torque
                    ){
    fn_send_rpm(mcu_speed,std::chrono::system_clock::now());
    std::cout<<"[can] spped callback"<<std::endl;
}

/**
 * 
*/
void CanMGR::requestCallback(short temp){

}


/**
 * @brief Function for controlling horn, head_light, right, left_light from robot to VCU via Can communication
 * @param horn 
 * @param head_light 
 * @param right_light 
 * @param left_light 
 * @author changunAn(changun516@wavem.net) 
 */
void CanMGR::fn_send_control_hardware(bool horn,bool head_light,bool right_light,bool left_light){
    obj_.ControlHardware(horn,head_light,right_light,left_light);
    fn_send_value(1);
}

/**
 * @brief Function for sending steering control values from robot to VCU via Can communication
 * @author changunAn(changun516@wavem.net) 
 * @param angular 
 */
void CanMGR::fn_send_control_steering(float angular){
    obj_.ControlSteering(angular);
}
/**
 * @brief Function for sending motor control values from robot to VCU via Can communication
 * @author changunAn(changun516@wavem.net) 
 * @param linear 
 */
void CanMGR::fn_send_control_vel(float linear){
    obj_.ControlVel(linear);
}

CanMGR::~CanMGR(){
    
}
/**
 * @brief Ability to send data from VCU to robot via Can communication to wm_motion_controller
 * @author changunAn(changun516@wavem.net) 
 * @param value 
 */
void CanMGR::fn_send_value(const int& value){
   // std::cout<< "override can_mannager"<<std::endl;
   //m_i_motion_mediator->fn_send_value(value,shared_from_this());
}
/**
 * @brief 
 * @author changunAn(changun516@wavem.net) 
 * @param value 
 */
void CanMGR::fn_recv_value(const int& value){
   // std::cout<< "override can_mannager "<<value<<std::endl;

}
void CanMGR::log(std::string call_name){
    std::chrono::system_clock::time_point callback_time = std::chrono::system_clock::now();
    std::time_t callback_time_t = std::chrono::system_clock::to_time_t(callback_time);
    std::tm* callback_time_tm = std::localtime(&callback_time_t);
    auto duration = callback_time.time_since_epoch();
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration) % std::chrono::seconds(1);
}

/**
 * @brief Function that passes rpm and time entered over Can communication to wm_motion_controller
 * 
 * @param rpm 
 * @param cur_time 
 */
void CanMGR::fn_send_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time){
    //m_i_motion_mediator->fn_send_rpm(rpm,cur_time,shared_from_this());
    manager_->can_send_rpm(rpm,cur_time);
}

void CanMGR::fn_recv_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time){
    
}


void CanMGR::static_break(UGV::BREAK break_status){
    obj_.static_break(break_status);
}




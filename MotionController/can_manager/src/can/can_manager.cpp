#include"can/can_manager.hpp"
#include <unistd.h>
#include<signal.h>

/**
 * @brief Construct a new Can M G R:: Can M G R object
 * @author changunAn(changun516@wavem.net)
 * @param motion_mediator 
 */
CanMGR::CanMGR() : Node("CanMotionController"){
//CanMGR::CanMGR(){
    //

    constants_ = std::make_unique<Constants>();
    cbg_body = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    rclcpp::CallbackGroup::SharedPtr cbg_accelerate=create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    rclcpp::CallbackGroup::SharedPtr cbg_brake=create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    rclcpp::CallbackGroup::SharedPtr cbg_steering=create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    rclcpp::SubscriptionOptions options_body;
    rclcpp::SubscriptionOptions options_accelerate;
    rclcpp::SubscriptionOptions options_brake;
    rclcpp::SubscriptionOptions options_steering;
    options_body.callback_group = cbg_body;
    options_accelerate.callback_group=cbg_accelerate;
    options_brake.callback_group=cbg_brake;
    options_steering.callback_group=cbg_steering;

    sub_body_ = this->create_subscription<can_msgs::msg::AdControlBody>(constants_->tp_name_control_body_,
                                                                        1,
                                                                        std::bind(&CanMGR::tp_control_body_callback,this,std::placeholders::_1),
                                                                        options_body);

    sub_accelerate_ = this->create_subscription<can_msgs::msg::AdControlAccelerate>(constants_->tp_name_control_accelerate_,
                                                                                    rclcpp::QoS(rclcpp::SystemDefaultsQoS()),
                                                                std::bind(&CanMGR::tp_control_accelerate, this,
                                                                          std::placeholders::_1), options_accelerate);
    sub_brake_= this->create_subscription<can_msgs::msg::AdControlBrake>(constants_->tp_name_control_brake_,
                                                                              rclcpp::QoS(rclcpp::SystemDefaultsQoS()),
                                                                              std::bind(&CanMGR::tp_control_brake, this,
                                                                                        std::placeholders::_1), options_brake);
    sub_steering_ = this->create_subscription<can_msgs::msg::AdControlSteering>(constants_->tp_name_control_steering_,
                                                                        rclcpp::QoS(rclcpp::SystemDefaultsQoS()),
                                                                        std::bind(&CanMGR::tp_control_steering, this,
                                                                                  std::placeholders::_1), options_steering);
    cur_speed_=0;
    cur_speed_acc_=0;
    fn_can_init();
 }

/**
 * @brief can operation function
 * @author changunAn(changun516@wavem.net)
 */
void CanMGR::fn_can_run(){
	std::cout << "***can run start!!!***" << std::endl;
	while(state){
        signal(SIGINT, SIG_DFL);
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
    // dbs fault status
	//obj_.RegistFaultCallback<CanMGR>(this, &CanMGR::faultCallback);
    //obj_.RegistRpmCallback<CanMGR>(this, &CanMGR::rpmCallback);
    //obj_.RegistBmsCallback<CanMGR>(this,&CanMGR::bmsCallback);
    obj_.RegistVehicleErrorCallback<CanMGR>(this,&CanMGR::vehicleCallback);
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
    //fn_send_rpm(mcu_speed,std::chrono::system_clock::now());
    std::cout<<"[can] speed callback"<<std::endl;
}
void CanMGR::bmsCallback(int sys_sts, int soc) {
    RCLCPP_INFO(this->get_logger(),"[bmsCallback] sys_sts %d, soc %d \n",
                sys_sts,
                soc);
}
void CanMGR::vehicleCallback(int error_code, int low_voltage) {
    RCLCPP_INFO(this->get_logger(),"[vehicleCallback] error_code %d, low_voltage %d \n",
                error_code,
                low_voltage);
}


CanMGR::~CanMGR(){
    
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

    //manager_->can_send_rpm(rpm,cur_time);
    std::cout<<rpm<<std::endl;
}


void CanMGR::tp_control_body_callback( can_msgs::msg::AdControlBody::SharedPtr control_body) {
    std::cout<<std::endl;
    RCLCPP_INFO(this->get_logger(),"fog_light %d , low_beam %d, reversing_light %d, double_flash_light %d, brake_light %d, horn_control %d, high_beam %d, right_turn_light %d , left_turn_light %d \n",
                control_body->fog_light,
                control_body->low_beam,
                control_body->reversing_light,
                control_body->double_flash_light,
                control_body->brake_light,
                control_body->horn_control,
                control_body->high_beam,
                control_body->right_turn_light,
                control_body->left_turn_light);
    obj_.ControlVel(cur_speed_acc_,cur_speed_);
    obj_.ControlHardware(control_body->fog_light,
                         control_body->low_beam,
                         control_body->reversing_light,
                         control_body->double_flash_light,
                         control_body->brake_light,
                         control_body->horn_control,
                         control_body->high_beam,
                         control_body->right_turn_light,
                         control_body->left_turn_light);

}

void CanMGR::tp_control_accelerate( can_msgs::msg::AdControlAccelerate::SharedPtr control_accelerate) {
    cur_speed_ = static_cast<float>(control_accelerate->speed_control);
    cur_speed_acc_= static_cast<float>(control_accelerate->acc);
    obj_.ControlVel(cur_speed_acc_,cur_speed_);
}

void CanMGR::tp_control_brake( can_msgs::msg::AdControlBrake::SharedPtr control_brake) {
    obj_.ControlVel(cur_speed_acc_,cur_speed_);
    if(control_brake->brakepressure_cmd==0){
        obj_.static_break(UGV::BREAK::GO);
    }
    else if(control_brake->brakepressure_cmd == 1){
        obj_.static_break(UGV::BREAK::STOP);
    }
    else{
        obj_.static_break(UGV::BREAK::LED);
    }
}

void CanMGR::tp_control_steering( can_msgs::msg::AdControlSteering::SharedPtr control_steering) {
    obj_.ControlVel(cur_speed_acc_,cur_speed_);
    obj_.ControlSteering(control_steering->steering_speed_cmd,control_steering->steering_angle_cmd);
}




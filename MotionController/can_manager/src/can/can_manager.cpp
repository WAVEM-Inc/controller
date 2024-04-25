#include"can/can_manager.hpp"
#include <unistd.h>
#include<signal.h>
#include "can_manager/debug.hpp"

/**
 * @brief Construct a new Can M G R:: Can M G R object
 * @author changunAn(changun516@wavem.net)
 * @param motion_mediator 
 */
CanMGR::CanMGR() : Node("CanMotionController") {
//CanMGR::CanMGR(){
    //
    check_emergency_ = false;
    constants_ = std::make_unique<Constants>();
    cbg_body = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    cbg_accelerate = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    cbg_brake = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    cbg_steering = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    cbg_emergency = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    rclcpp::SubscriptionOptions options_body;
    rclcpp::SubscriptionOptions options_accelerate;
    rclcpp::SubscriptionOptions options_brake;
    rclcpp::SubscriptionOptions options_steering;
    rclcpp::SubscriptionOptions options_emergency;
    options_body.callback_group = cbg_body;
    options_accelerate.callback_group = cbg_accelerate;
    options_brake.callback_group = cbg_brake;
    options_steering.callback_group = cbg_steering;
    options_emergency.callback_group = cbg_emergency;

    cbg_rpm = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    cbg_bms = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    cbg_velocity = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    rclcpp::PublisherOptions options_rpm;
    rclcpp::PublisherOptions options_bms;
    rclcpp::PublisherOptions options_velocity;
    options_rpm.callback_group = cbg_rpm;
    options_bms.callback_group = cbg_bms;
    options_velocity.callback_group = cbg_velocity;

    sub_body_ = this->create_subscription<can_msgs::msg::AdControlBody>(constants_->tp_name_control_body_,
                                                                        1,
                                                                        std::bind(&CanMGR::tp_control_body_callback,
                                                                                  this, std::placeholders::_1),
                                                                        options_body);

    sub_accelerate_ = this->create_subscription<can_msgs::msg::AdControlAccelerate>(
            constants_->tp_name_control_accelerate_,
            rclcpp::QoS(rclcpp::SystemDefaultsQoS()),
            std::bind(&CanMGR::tp_control_accelerate, this,
                      std::placeholders::_1), options_accelerate);
    sub_brake_ = this->create_subscription<can_msgs::msg::AdControlBrake>(constants_->tp_name_control_brake_,
                                                                          rclcpp::QoS(rclcpp::SystemDefaultsQoS()),
                                                                          std::bind(&CanMGR::tp_control_brake, this,
                                                                                    std::placeholders::_1),
                                                                          options_brake);
    sub_steering_ = this->create_subscription<can_msgs::msg::AdControlSteering>(constants_->tp_name_control_steering_,
                                                                                rclcpp::QoS(
                                                                                        rclcpp::SystemDefaultsQoS()),
                                                                                std::bind(&CanMGR::tp_control_steering,
                                                                                          this,
                                                                                          std::placeholders::_1),
                                                                                options_steering);
    sub_emergency_ = this->create_subscription<can_msgs::msg::Emergency>(constants_->tp_name_emergency_,
                                                                         rclcpp::QoS(rclcpp::SystemDefaultsQoS()),
                                                                         std::bind(&CanMGR::tp_emergency, this,
                                                                                   std::placeholders::_1),
                                                                         options_emergency);
    pub_rpm_ = this->create_publisher<can_msgs::msg::TorqueFeedback>(constants_->tp_name_state_rpm_,
                                                                     rclcpp::QoS(rclcpp::SystemDefaultsQoS()),
                                                                     options_rpm);
    pub_bms_ = this->create_publisher<sensor_msgs::msg::BatteryState>(constants_->tp_name_state_bms_,
                                                          rclcpp::QoS(rclcpp::SystemDefaultsQoS()),
                                                          options_bms);
    pub_velocity_ = this->create_publisher<robot_status_msgs::msg::VelocityStatus>(constants_->tp_name_state_velocity_,
                                                                                   rclcpp::QoS(
                                                                                           rclcpp::SystemDefaultsQoS()),
                                                                                   options_velocity);

    cur_speed_ = 0;
    cur_speed_acc_ = 0;
    fn_can_init();
}

/**
 * @brief can operation function
 * @author changunAn(changun516@wavem.net)
 */
void CanMGR::fn_can_run() {
    std::cout << "***can run start!!!***" << std::endl;
    while (state) {
        signal(SIGINT, SIG_DFL);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        obj_.ControlVel(cur_speed_acc_, cur_speed_);
        obj_.run_flag();
        if (check_emergency_) {
            obj_.static_break(UGV::BREAK::STOP);
        }

    }
    std::cout << "***can end!!!***" << std::endl;
}

/**
 * @brief Register callback function for can communication response
 * @return int Verify function normal termination
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.06
 */
int CanMGR::fn_can_init() {
    // dbs fault status
    obj_.RegistFaultCallback<CanMGR>(this, &CanMGR::faultCallback);
    obj_.RegistRpmCallback<CanMGR>(this, &CanMGR::rpmCallback);
    obj_.RegistBmsCallback<CanMGR>(this, &CanMGR::bmsCallback);
    obj_.RegistVehicleStatus2Callback(this, &CanMGR::vehicleStatus2Callback);
    obj_.RegistVehicleErrorCallback<CanMGR>(this, &CanMGR::vehicleErrorCallback);
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
void CanMGR::faultCallback(int can_falut, int dbs_fault) {
#if DEBUG_MODE == 1
    RCLCPP_INFO(this->get_logger(), "[faultCallback] can_falut %d, dbs_fault %d \n",
                can_falut,
                dbs_fault);
#endif
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
void CanMGR::rpmCallback(int mcu_shift, int mcu_speed, int mcu_torque
) {
#if DEBUG_MODE == 1
    RCLCPP_INFO(this->get_logger(), "[rpmCallback] mcu_speed %d \n",
                mcu_speed);
#endif
    can_msgs::msg::TorqueFeedback temp_rpm;
    temp_rpm.mcu_shift = mcu_shift;
    temp_rpm.mcu_speed = mcu_speed;
    temp_rpm.mcu_torque = mcu_torque;
    pub_rpm_->publish(temp_rpm);
}

void CanMGR::bmsCallback(int sys_sts, int soc) {
#if DEBUG_MODE == 1
    RCLCPP_INFO(this->get_logger(), "[bmsCallback] sys_sts %d, soc %d \n",
                sys_sts,
                soc);
#endif
    sensor_msgs::msg::BatteryState temp_battery;
    temp_battery.voltage = soc;
    temp_battery.present = sys_sts;

    pub_bms_->publish(temp_battery);
}

void CanMGR::vehicleErrorCallback(int error_code, int low_voltage) {
#if DEBUG_MODE == 1
    RCLCPP_INFO(this->get_logger(), "[vehicleErrorCallback] error_code %d, low_voltage %d \n",
                error_code,
                low_voltage);
#endif
}

void CanMGR::vehicleStatus2Callback(int brake_press, float speed) {
#if DEBUG_MODE == 1
    RCLCPP_INFO(this->get_logger(), "[vehicleStatus2Callback] brake_press %d, speed %f \n",
                brake_press,
                speed);
#endif
    robot_status_msgs::msg::VelocityStatus temp_velocity;
    temp_velocity.current_velocity = speed;
    pub_velocity_->publish(temp_velocity);
}


CanMGR::~CanMGR() {

}

void CanMGR::log(std::string call_name) {
    std::chrono::system_clock::time_point callback_time = std::chrono::system_clock::now();
    std::time_t callback_time_t = std::chrono::system_clock::to_time_t(callback_time);
    std::tm *callback_time_tm = std::localtime(&callback_time_t);
    auto duration = callback_time.time_since_epoch();
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration) % std::chrono::seconds(1);
}

/**
 * @brief Function that passes rpm and time entered over Can communication to wm_motion_controller
 * 
 * @param rpm 
 * @param cur_time 
 */
void CanMGR::fn_send_rpm(const float &rpm, const std::chrono::system_clock::time_point &cur_time) {
    //m_i_motion_mediator->fn_send_rpm(rpm,cur_time,shared_from_this());

    //manager_->can_send_rpm(rpm,cur_time);
    std::cout << rpm << std::endl;
}


void CanMGR::tp_control_body_callback(can_msgs::msg::AdControlBody::SharedPtr control_body) {
#if DEBUG_MODE == 1
    RCLCPP_INFO(this->get_logger(),
                "fog_light %d , low_beam %d, reversing_light %d, double_flash_light %d, brake_light %d, horn_control %d, high_beam %d, right_turn_light %d , left_turn_light %d \n",
                control_body->fog_light,
                control_body->low_beam,
                control_body->reversing_light,
                control_body->double_flash_light,
                control_body->brake_light,
                control_body->horn_control,
                control_body->high_beam,
                control_body->right_turn_light,
                control_body->left_turn_light);
#endif
    //obj_.ControlVel(cur_speed_acc_,cur_speed_);
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

void CanMGR::tp_control_accelerate(can_msgs::msg::AdControlAccelerate::SharedPtr control_accelerate) {
    double safe_speed = 0.6;
    if(control_accelerate->speed_control>safe_speed){
        cur_speed_=safe_speed;
    } // 추후 제거 필요 Test 시 사고 방지
    else {
        cur_speed_ = static_cast<float>(control_accelerate->speed_control);
    }
    cur_speed_acc_ = static_cast<float>(control_accelerate->acc);
    //obj_.ControlVel(cur_speed_acc_,cur_speed_);
}

void CanMGR::tp_control_brake(can_msgs::msg::AdControlBrake::SharedPtr control_brake) {
    RCLCPP_INFO(this->get_logger(), "[brake] pressure %d\n",
                control_brake->brakepressure_cmd);
    //obj_.ControlVel(cur_speed_acc_,cur_speed_);
    if (control_brake->brakepressure_cmd == 0) {
        obj_.static_break(UGV::BREAK::GO);
    } else if (control_brake->brakepressure_cmd == 1) {
        obj_.static_break(UGV::BREAK::STOP);
    } else {
        obj_.static_break(UGV::BREAK::LED);
    }
}

void CanMGR::tp_control_steering(can_msgs::msg::AdControlSteering::SharedPtr control_steering) {
    //obj_.ControlVel(cur_speed_acc_,cur_speed_);
    obj_.ControlSteering(control_steering->steering_speed_cmd, control_steering->steering_angle_cmd);
}

void CanMGR::tp_emergency(can_msgs::msg::Emergency::SharedPtr stop) {
    if (stop->stop) {
        check_emergency_ = true;
    } else {
        check_emergency_ = false;
    }
}





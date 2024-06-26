#include <vector>
#include <unistd.h>
#include <cmath>
#include "can/can_adaptor.hpp"
#include "can/data_relayer.hpp"

#include "rclcpp/rclcpp.hpp"
#include "rcutils/logging_macros.h"

DataRelayer::DataRelayer() :   prev_gear_(ACC_GEAR::NEUTRAL),gear_trans_check_(0){
    system_endian_ = is_big_endian();
}

DataRelayer::~DataRelayer() {
    if (canlib_ != NULL) {
        canlib_->Release();
    }
}

/**
* @brief Send control commands.(ControlSteering)
* @details
* @param steering_angle_cmd Steering angle
* @return void
* @exception
*/
void DataRelayer::ControlSteering(float speed, float angle) {
    SendMessageControlSteering(speed, angle);
}

/**
* @brief Send control commands.(ControlVel)
* @details
* @param vel  Accelerate speeed
* @return void
* @exception
*/
void DataRelayer::ControlVel(float acc, float vel) {//iECU_Control_Accelerate, iECU_Control_Brake둘다 사용)
    SendMessageControlAccelerate(acc, vel);
}

/**
* @brief Send control commands.(ControlHardware)
* @details
* @param Horn true : on, false : 0ff
* @param HeadLight true : on, false : 0ff
* @param Right_Turn_Light true : on, false : 0ff
* @param Left_Turn_Light true : on, false : 0ff
* @return void
* @exception
*/
void DataRelayer::ControlHardware(
        bool fog_light,
        bool low_beam,
        bool reversing_light,
        bool double_flash_light,
        bool brake_light,
        bool horn_control,
        bool high_beam,
        bool right_turn_light,
        bool left_turn_light) {
    rclcpp::Logger logger = rclcpp::get_logger("DataRelayer");
    RCUTILS_LOG_INFO_NAMED(logger.get_name(),
                           "Data fog_light %d , low_beam %d, reversing_light %d, double_flash_light %d, brake_light %d, horn_control %d, high_beam %d, right_turn_light %d , left_turn_light %d \\n",
                           fog_light,
                           low_beam,
                           reversing_light,
                           double_flash_light,
                           brake_light,
                           horn_control,
                           high_beam,
                           right_turn_light,
                           left_turn_light);

    SendMessageControlHardware(fog_light, low_beam, reversing_light, double_flash_light,
                               brake_light, horn_control, high_beam, right_turn_light, left_turn_light);
}


/**
* @brief service <-> message id / channel mapping
* @details Mapping so that can channel and can id can be changed according to environment variables later
* @param
* @return void
* @exception
*/
void DataRelayer::SetmsgMap(int svcid, int msgid, string device) {
    magMap_.insert(make_pair(svcid, msgid));
    channelMap_.insert(make_pair(svcid, device));
}

/**
* @brief send API(ControlSteering)
* @details
* @param steering_angle_cmd steering angle
* @return void
* @exception
*/
void DataRelayer::SendMessageControlSteering(float speed, float steering_angle_cmd) {

    if (steering_angle_cmd > MAX_STEERING || steering_angle_cmd < MIN_STEERING) {
        return;
    }
    AD::AD_Control_Steering dat_1;
    memset(&dat_1, 0x00, CAN_MAX_DLEN);
    dat_1.AD_Steering_Valid= 1;
    dat_1.AD_Steering_Speed_Cmd = static_cast<unsigned char>(speed)-static_cast<unsigned char>(2.68);
    dat_1.AD_Steering_Angle_Cmd = (steering_angle_cmd + OFFSET_STEERING) * RESOLUTION_STEERING_CTRL;
    canlib_->PostCanMessage<AD::AD_Control_Steering>(dat_1, AD_CONTROL_STEERING, device_type[CAN0]);
};

/**
* @brief send API(ControlAccelerate)
* @details
* @param vel  Accelerate speeed
* @return void
* @exception
*/
void DataRelayer::SendMessageControlAccelerate(float acc, float vel) {

    unsigned char gear;
    if (vel > 0) {
        gear = FORWARD;
    } else if (vel < 0) {
        gear = REVERSE;
    } else {
        gear = NEUTRAL;
        //gear = NEUTRAL;
    }
    //HeartBeat();
    AD::AD_Control_Accelerate dat_1;
    memset(&dat_1, 0x00, CAN_MAX_DLEN);
    dat_1.AD_Accelerate_Valid = 1;
    dat_1.AD_Acc = static_cast<unsigned short>(acc)+ static_cast<unsigned short>(500);
    dat_1.AD_Accelerate_Work_Mode = 1;
    dat_1.AD_Accelerate_Gear = gear;
    dat_1.AD_Speed_Control = [](float v) { return v * CNV_SPEED_FACTOR * RESOLUTION_SPEED_CTRL; }(std::fabs(vel));
    dat_1.AD_Torque_Control = 0;
    canlib_->PostCanMessage<AD::AD_Control_Accelerate>(dat_1, AD_CONTROL_ACCELERATE, device_type[CAN0]);
};

void DataRelayer::SendMessageControlAccelerate(float acc, float vel, unsigned char gear) {
    //HeartBeat();
    AD::AD_Control_Accelerate dat_1;
    memset(&dat_1, 0x00, CAN_MAX_DLEN);
    dat_1.AD_Accelerate_Valid = 1;
    dat_1.AD_Acc = static_cast<unsigned short>(acc)+ static_cast<unsigned short>(500);
    dat_1.AD_Accelerate_Work_Mode = 1;
    dat_1.AD_Accelerate_Gear = gear;
    dat_1.AD_Speed_Control = [](float v) { return v * CNV_SPEED_FACTOR * RESOLUTION_SPEED_CTRL; }(std::fabs(vel));
    dat_1.AD_Torque_Control = 0;
    canlib_->PostCanMessage<AD::AD_Control_Accelerate>(dat_1, AD_CONTROL_ACCELERATE, device_type[CAN0]);
};
/**
* @brief send API(ControlHardware)
* @details
* @param Horn true : on, false : 0ff
* @param HeadLight true : on, false : 0ff
* @param Right_Turn_Light true : on, false : 0ff
* @param Left_Turn_Light true : on, false : 0ff
* @return void
* @exception
*/
void DataRelayer::SendMessageControlHardware(bool fog_light,
                                             bool low_beam,
                                             bool reversing_light,
                                             bool double_flash_light,
                                             bool brake_light,
                                             bool horn_control,
                                             bool high_beam,
                                             bool right_turn_light,
                                             bool left_turn_light) {
    AD::AD_Control_Body dat_1;
    memset(&dat_1, 0x00, CAN_MAX_DLEN);
    dat_1.AD_Fof_Light = fog_light ? 1 : 0;
    dat_1.AD_Low_Beam = low_beam ? 1 : 0;
    dat_1.AD_Reversing_Lights = reversing_light ? 1 : 0;
    dat_1.AD_Double_Flash_Light = double_flash_light ? 1 : 0;
    dat_1.AD_Brake_Light = brake_light ? 1 : 0;
    dat_1.AD_Horn_Control = horn_control ? 1 : 0;
    dat_1.AD_High_Beam = high_beam ? 1 : 0;
    dat_1.AD_Right_Turn_Light = right_turn_light ? 1 : 0;
    dat_1.AD_Left_Turn_Light = left_turn_light ? 1 : 0;
    dat_1.AD_Body_Valid = 1;
    canlib_->PostCanMessage<AD::AD_Control_Body>(dat_1, AD_CONTROL_BODY, device_type[CAN0]);
};
// 필요에 따라 추가 한다.외부 인터페이스 API 정의 필요

/**
* @brief Callback function to register with CanAdaptor::
* @details Register a callback function using CanAdaptor::SetHandler.
* @param msg receive data
* @return void
* @exception
*/
/*
void DataRelayer::Handler_VCU_EPS_Control_Request (VCU_EPS_Control_Request msg){
   std::cout<<"Handler_VCU_EPS_Control_Request"<<std::endl;
  short vcu_eps_strangle = htons(msg.vcu_eps_strangle);

  double strangle_value = (vcu_eps_strangle / RESOLUTION_STEERING_CTRL ) - OFFSET_STRANGLE ;

 // cout << "[recv] VCU_EPS_Control_Request : " << vcu_eps_strangle <<"("<<strangle_value<<"),"<< (int)msg.vcu_eps_ctrlenable <<","<< (int)msg.vcu_eps_ctrlmode << endl;

}
*/

/**
* @brief Callback function to register with CanAdaptor::
* @details Register a callback function using CanAdaptor::SetHandler.
* @param msg receive data
* @return void
* @exception
*/
/*
void DataRelayer::Handler_DBS_Status (DBS_Status msg){
  cout << "[recv] DBS_Status : " << (int)msg.dbs_fault_code <<","<<(int)msg.dbs_hp_pressure <<","<<(int)msg.dbs_system_status << endl;
  faultCallback(CAN_NO_FAULT,msg.dbs_fault_code);
}



/**
* @brief Callback function to register with CanAdaptor::
* @details Register a callback function using CanAdaptor::SetHandler.
* @param msg receive data
* @return void
* @exception
*/
void DataRelayer::Handler_MCU_Torque_Feedback(VCU::MCU_Torque_Feedback msg) {
    rpmCallback((int) msg.MCU_Shift, (int) msg.MCU_SPEED, (int) msg.MCU_TORQUE);
}
void DataRelayer::Handler_BMS_Status(VCU::BMS_A0h msg) {
    bmsCallback(static_cast<int>(msg.BMS_Charge_StsCc),
                static_cast<int>(msg.BMS_HVBatSOC)*RESOLUTION_BMS_SOC,
                static_cast<int>(msg.BMS_Sys_Sts),
                static_cast<int>(msg.BMS_HVBatVol));
}
void DataRelayer::Handler_VEHICLE_ERROR_Status(VCU::VCU_Vehicle_ErrorCode msg) {
    vehicleErrorCallback(static_cast<int>(msg.Error_Code), static_cast<int>(msg.Low_voltage));
}


/**
* @brief run test
* @details
* @param
* @return void
* @exception
*/
void DataRelayer::Run() {

    canlib_ = CanAdaptor::getInstance();
    canlib_->Initialize(system_endian_);
#if DEBUG_MODE == 2
    std::cout<<"[DataRelayer]-[Run] : "<<__LINE__<<std::endl;
#endif
    // 수신 핸들러 등록
    canlib_->SetHandler<DataRelayer>(this, &DataRelayer::Handler_DBS_Status2, DBS_STATUS2,device_type[CAN0]); // changun
    canlib_->SetHandler<DataRelayer>(this, &DataRelayer::Handler_MCU_Torque_Feedback, TORQUE_FEEDBACK,device_type[CAN0]);
    canlib_->SetHandler<DataRelayer>(this,&DataRelayer::Handler_VEHICLE_ERROR_Status,VCU_VEHICLE_ERRORCODE,device_type[CAN0]);
    canlib_->SetHandler<DataRelayer>(this,&DataRelayer::Handler_BMS_Status,BMS_A0H, device_type[CAN0]);
    canlib_->SetHandler<DataRelayer>(this,&DataRelayer::Handler_VCU_Vehicle_Status_2,VCU_VEHICLE_STATUS_2, device_type[CAN0]);
    canlib_->SetHandler<DataRelayer>(this,&DataRelayer::Handler_Remote_Control_IO,REMOTE_CONTROL_IO,device_type[CAN0]);
    canlib_->SetHandler<DataRelayer>(this,&DataRelayer::Handler_VCU_Vehicle_Odometer_Status,VEHICLE_ODOMETER_STATUS,device_type[CAN0]);
#if DEBUG_MODE == 2
    std::cout<<"[DataRelayer]-[Run] : "<<__LINE__<<std::endl;
#endif

    // 수신 리스너 오픈
    vector<string> device;
    device.push_back(device_type[CAN0]);

    int ret = 0;
    while (canlib_->Open(device) != 0) {
        cout << "open fail" << endl;
        sleep(CAN_ALIVE_CHECKTIME);
    }
    while(canlib_->RunControlFlag(0,device_type[CAN0]) != 0 ){
        cout << "run config flag fail" << endl;
        sleep(CAN_ALIVE_CHECKTIME);
    }

#if DEBUG_MODE == 2
    std::cout<<"[DataRelayer]-[Run] : "<<__LINE__<<std::endl;
#endif
    //포트 오픈 체크 스레드
    cout << "Start checking for can channel fault" << endl;
    canlib_->CheckSocketStatus(device, vehicleErrorCallback);
#if DEBUG_MODE == 2
    std::cout<<"[DataRelayer]-[Run] : "<<__LINE__<<std::endl;
#endif
}

void DataRelayer::StopPostMessage(unsigned int id) {
    canlib_->StopPostMessage(id);
}

/**
* @brief data send test
* @details
* @param
* @return void
* @exception
*/
void DataRelayer::SendTest() {
    // 전송 테스트
    AD::AD_Control_Body dat_1;
    memset(&dat_1, 0x00, CAN_MAX_DLEN);
    dat_1.AD_High_Beam = 1;
    dat_1.AD_Horn_Control = 0;
    dat_1.AD_Left_Turn_Light = 1;
    dat_1.AD_Right_Turn_Light = 1;
    //
    canlib_->PostCanMessage<AD::AD_Control_Body>(dat_1, AD_CONTROL_BODY, device_type[CAN0]);
}

/*void DataRelayer::static_break(UGV::BREAK break_status) {
    std::cout<<"[test]" <<std::endl;
    AD::AD_Control_Brake dat_2;
    memset(&dat_2, 0x00, CAN_MAX_DLEN);
    dat_2.AD_DBS_Valid = 1;
    if (UGV::BREAK::LED == break_status) {
        dat_2.AD_BrakePressure_Cmd = 10;
    } else if (UGV::BREAK::GO == break_status) {
        dat_2.AD_DBS_Valid = 0;
        dat_2.AD_BrakePressure_Cmd = 0;
    } else if (UGV::BREAK::STOP == break_status) {
        dat_2.AD_BrakePressure_Cmd = 100; //origin 100
    }
    //dat_2.iecu_dbs_valid = 1;
    canlib_->PostCanMessage<AD::AD_Control_Brake>(dat_2, AD_CONTROL_BRAKE, device_type[CAN0]);
}*/
void DataRelayer::static_break(int brake_pressure_cmd) {
    rclcpp::Logger logger = rclcpp::get_logger("DataRelayer");
    RCUTILS_LOG_INFO_NAMED(logger.get_name(),"[static_break]-brake_pressure_cmd %d",brake_pressure_cmd);
    AD::AD_Control_Brake dat_2;
    memset(&dat_2, 0x00, CAN_MAX_DLEN);
    dat_2.AD_DBS_Valid = 1;
    dat_2.AD_BrakePressure_Cmd =brake_pressure_cmd;
    //dat_2.iecu_dbs_valid = 1;
    canlib_->PostCanMessage<AD::AD_Control_Brake>(dat_2, AD_CONTROL_BRAKE, device_type[CAN0]);
}


void DataRelayer::Handler_DBS_Status2(VCU::DBS_Status2 msg) {
    faultCallback(msg.DBS_WarringCode, msg.DBS_Fault_Code);
}

void DataRelayer::run_flag() {
     canlib_->RunControlFlag(0, device_type[CAN0]);
}
void DataRelayer::run_off_flag() {
    canlib_->RunControlFlag(1, device_type[CAN0]);
}


void DataRelayer::Handler_VCU_Vehicle_Status_2(VCU::VCU_Vehicle_Status_2 msg) {
    vehicleStatus2Callback(static_cast<float>(msg.Vehicle_Brake_Pressure)*RESOLUTION_VEHICLE_BRAKE_PRESSURE, (static_cast<float>(msg.Vehicle_Speed)*RESOLUTION_VEHICLE_SPEED)-OFFSET_VEHICLE_STATUS_SPEED);
}



void DataRelayer::Handler_Remote_Control_IO(VCU::Remote_Control_IO msg) {
    remoteIOCallback(static_cast<int>(msg.Remote_A));
}

void DataRelayer::Handler_VCU_Vehicle_Odometer_Status(VCU::Vehicle_Odometer_Status msg) {
    vehicleOdometerStatusCallback(static_cast<float>(msg.Vehicle_ODO));
}
#include <vector>
#include <unistd.h>

#include "can/can_adaptor.hpp"
#include "can/data_relayer.hpp"

#include "can/can_define.hpp"
#include "wm_motion_controller/wm_motion_controller.hpp"

DataRelayer::DataRelayer() {
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
void DataRelayer::ControlSteering(float angle) {
    SendMessageControlSteering(angle);
}

/**
* @brief Send control commands.(ControlVel)
* @details
* @param vel  Accelerate speeed
* @return void
* @exception
*/
void DataRelayer::ControlVel(float vel) {//iECU_Control_Accelerate, iECU_Control_Brake둘다 사용)
    SendMessageControlAccelerate(vel);
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
void DataRelayer::ControlHardware(bool horn, bool head_light, bool right_light, bool left_light) {
    SendMessageControlHardware(horn, head_light, right_light, left_light);
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
void DataRelayer::SendMessageControlSteering(float steering_angle_cmd) {

    if (steering_angle_cmd > MAX_STEERING || steering_angle_cmd < MIN_STEERING) {
        return;
    }
    AD::AD_Control_Steering dat_1;
    memset(&dat_1, 0x00, CAN_MAX_DLEN);
    dat_1.AD_Steering_Angle_Cmd = (steering_angle_cmd + OFFSET_STEERING) * RESOLUTION_STEERING_CTRL;
    dat_1.AD_Steering_Valid = 1;
    //changun CAN 1->0 230427
    canlib_->PostCanMessage<AD::AD_Control_Steering>(dat_1, AD_CONTROL_STEERING, device_type[CAN0]);
};

/**
* @brief send API(ControlAccelerate)
* @details
* @param vel  Accelerate speeed
* @return void
* @exception
*/
void DataRelayer::SendMessageControlAccelerate(float vel) {

    unsigned char gear;
    if (vel > 0) {
        gear = FORWARD;
    } else if (vel < 0) {
        gear = REVERSE;
    } else {
        gear = PARKING;
        //gear = NEUTRAL;
    }
    //HeartBeat();
    AD::AD_Control_Accelerate dat_1;
    memset(&dat_1, 0x00, CAN_MAX_DLEN);
    dat_1.AD_Accelerate_Gear = gear;
    dat_1.AD_Accelerate_Valid = 1;
    dat_1.AD_Accelerate_Work_Mode = 1;
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
void DataRelayer::SendMessageControlHardware(bool Horn, bool HeadLight, bool Right_Turn_Light, bool Left_Turn_Light) {
    AD::AD_Control_Body dat_1;
    memset(&dat_1, 0x00, CAN_MAX_DLEN);
    dat_1.AD_High_Beam = HeadLight ? 1 : 0;
    dat_1.AD_Horn_Control = Horn ? 1 : 0;
    dat_1.AD_Left_Turn_Light = Left_Turn_Light ? 1 : 0;
    dat_1.AD_Right_Turn_Light = Right_Turn_Light ? 1 : 0;
    canlib_->PostCanMessage<AD::AD_Control_Body>(dat_1, AD_CONTROL_HARDWARE, device_type[CAN0]);
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
*/


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
#if DEBUG_MODE==1
    std::cout<<"[DataRelayer]-[Run] : "<<__LINE__<<std::endl;
#endif
    // 수신 핸들러 등록
    canlib_->SetHandler<DataRelayer>(this, &DataRelayer::Handler_DBS_Status2, DBS_STATUS2,
                                     device_type[CAN0]); // changun
    canlib_->SetHandler<DataRelayer>(this, &DataRelayer::Handler_MCU_Torque_Feedback, TORQUE_FEEDBACK,
                                     device_type[CAN0]);
#if DEBUG_MODE==1
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
#if DEBUG_MODE==1
    std::cout<<"[DataRelayer]-[Run] : "<<__LINE__<<std::endl;
#endif
    //포트 오픈 체크 스레드
    cout << "Start checking for can channel fault" << endl;
    canlib_->CheckSocketStatus(device, faultCallback);
#if DEBUG_MODE==1
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
    canlib_->PostCanMessage<AD::AD_Control_Body>(dat_1, AD_CONTROL_HARDWARE, device_type[CAN0]);
}

void DataRelayer::static_break(UGV::BREAK break_status) {
    AD::AD_Control_Brake dat_2;
    memset(&dat_2, 0x00, CAN_MAX_DLEN);
    dat_2.AD_DBS_Valid = 1;
    if (UGV::BREAK::LED == break_status) {
        dat_2.AD_BrakePressure_Cmd = 15;
    } else if (UGV::BREAK::GO == break_status) {
        dat_2.AD_DBS_Valid = 0;
        dat_2.AD_BrakePressure_Cmd = 0;
    } else if (UGV::BREAK::STOP == break_status) {
        dat_2.AD_BrakePressure_Cmd = 100; //origin 100
    }
    //dat_2.iecu_dbs_valid = 1;
    canlib_->PostCanMessage<AD::AD_Control_Brake>(dat_2, AD_CONTROL_BRAKE, device_type[CAN0]);
}

void DataRelayer::Handler_DBS_Status2(VCU::DBS_Status2 msg) {
    cout << "[recv] DBS_Status2 : " << (int) msg.DBS_Fault_Code << "," << (int) msg.DBS_RollingCounter2 << ","
         << (int) msg.DBS_WarringCode << endl;
    faultCallback(CAN_NO_FAULT, msg.DBS_Fault_Code);
}



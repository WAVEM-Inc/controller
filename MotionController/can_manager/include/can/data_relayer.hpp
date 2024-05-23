#ifndef DATA_RELAYER_H
#define DATA_RELAYER_H

#include <iostream>
#include <functional>
#include <map>
#include <memory.h>
#include <arpa/inet.h>

#include "can/can2ad_dbc.h"
#include "can/can2vcu_dbc.h"
#include "can/df_ugv.hpp"

#include "can/can_define.hpp"
using namespace std;

class CanAdaptor;
/**
    @class   DataRelayer
    @date    2023-02-14
    @author  ys.kwon(ys.kwon@wavem.net)
    @brief   Wrapping classes for CAN data conversion and relaying
    @version 0.0.1
    @warning
*/
class DataRelayer {

  private:
    //void(*fpoint)(int,int,int);
    typedef std::function<void(int,unsigned long long)> func_fault_callback; // Callback function pointer variable definition
    typedef std::function<void(int,int,int)> func_rpm_callback; // Callback function pointer variable definition
    typedef std::function<void(int,int,int,int)> func_bms_callback;
    typedef std::function<void(int,int)> func_vehicle_error_callback;
    typedef std::function<void(int,float)> func_vehicle_status2;
    typedef std::function<void(int)> func_remote_io_callback;

    //typedef std::function<void(int,int,int)> func_other_callback; // Callback function pointer variable definition

    func_fault_callback faultCallback;// Callback function pointer variable definition
    func_rpm_callback rpmCallback; // Callback function pointer variable definition
    func_bms_callback bmsCallback;
    func_vehicle_error_callback  vehicleErrorCallback;
    func_vehicle_status2 vehicleStatus2Callback;
    func_remote_io_callback remoteIOCallback;
    //func_other_callback otherCallback; // Callback function pointer variable definition

    bool system_endian_ = 0;
    CanAdaptor* canlib_ = NULL;

    map<int,int> magMap_; // code , MSG_ID
    map<int,string> channelMap_; // code , channel

    //
    ACC_GEAR prev_gear_;
    int gear_trans_check_;
    //
  public:
    DataRelayer(); 
    virtual ~DataRelayer();

    void ControlSteering(float speed,float angle);
    void ControlVel(float acc, float vel);
    void ControlVel();
    void ControlHardware(
            bool fog_light,
            bool low_beam,
            bool reversing_light,
            bool double_flash_light,
            bool brake_light,
            bool horn_control,
            bool high_beam,
            bool right_turn_light,
            bool left_turn_light);
    void StopPostMessage(unsigned int id);

    //void static_break(bool flag);
    //void static_break(UGV::BREAK break_status);
    void static_break(int brake_pressure_cmd);

    /**
    * @brief Register a RPM callback function
    * @details Registering class member function callbacks (std:funcion)
    * @param pfunc function point
    * @return void
    * @exception
    */
    template<typename T>
    void RegistRpmCallback(T *pClassType,void(T::*pfunc)(int,int,int)){
      rpmCallback = move(bind(pfunc, pClassType
        , placeholders::_1
        , placeholders::_2
        , placeholders::_3
        ));
    }

    /**
    * @brief Register a FAULT callback function
    * @details Registering class member function callbacks (std:funcion)
    * @param pfunc function point
    * @return void
    * @exception
    */
    template<typename T>
    void RegistFaultCallback(T *pClassType,void(T::*pfunc)(int,unsigned long long)){
      faultCallback = move(bind(pfunc, pClassType
        , placeholders::_1
        , placeholders::_2
        ));
    }

    template<typename T>
    void RegistBmsCallback(T *pClassType,void(T::*pfunc)(int,int,int,int)){
        bmsCallback = move(bind(pfunc,
                                pClassType,
                                placeholders::_1,
                                placeholders::_2,
                                placeholders::_3,
                                placeholders::_4
                ));
    }
    template<typename T>
    void RegistVehicleErrorCallback(T *pClassType,void(T::*pfunc)(int,int)){
        vehicleErrorCallback = move(bind(pfunc,
                                pClassType,
                                placeholders::_1,
                                placeholders::_2
        ));
    }
    template<typename T>
    void RegistVehicleStatus2Callback(T *pClassType,void(T::*pfunc)(int,float)){
        vehicleStatus2Callback = move(bind(pfunc,
                                         pClassType,
                                         placeholders::_1,
                                         placeholders::_2
        ));
    }
    template<typename T>
    void RegisterRemoteIOCallback(T *pClassType,void(T::*pfunc)(int)){
        remoteIOCallback = move(bind(pfunc,
                                         pClassType,
                                         placeholders::_1));
    }

    void Run();
    void SendTest();
    void run_flag();
    void run_off_flag();
  private:
    void SetmsgMap(int svcid,int msgid,string device);

    void SendMessageControlSteering(float speed,float steering_angle_cmd);
    void SendMessageControlAccelerate(float acc, float vel);
    void SendMessageControlAccelerate(float acc, float vel,unsigned char gear);
    void SendMessageControlHardware(bool fog_light,
                                    bool low_beam,
                                    bool reversing_light,
                                    bool double_flash_light,
                                    bool brake_light,
                                    bool horn_control,
                                    bool high_beam,
                                    bool right_turn_light,
                                    bool left_turn_light);

    //void Handler_VCU_EPS_Control_Request (VCU_EPS_Control_Request msg);
    void Handler_DBS_Status2 (VCU::DBS_Status2 msg);
    void Handler_MCU_Torque_Feedback (VCU::MCU_Torque_Feedback msg);
    void Handler_BMS_Status(VCU::BMS_A0h msg);
    void Handler_VEHICLE_ERROR_Status(VCU::VCU_Vehicle_ErrorCode msg);
    void Handler_VCU_Vehicle_Status_2(VCU::VCU_Vehicle_Status_2 msg);
    void Handler_Remote_Control_IO(VCU::Remote_Control_IO msg);
    bool is_big_endian(){
      char buf[2] = {0,1};
      unsigned short *val = reinterpret_cast<unsigned short*>(buf);
      return *val == 1;
    }

 };

#endif //FUNCTIONCALLBACK_PARENT_H

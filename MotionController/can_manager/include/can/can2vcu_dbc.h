//
// Created by msi-341 on 24. 3. 25.
//

#ifndef WM_MOTION_CONTROLLER_CAN2VCU_DBC_H
#define WM_MOTION_CONTROLLER_CAN2VCU_DBC_H
#pragma pack(push, 1)
namespace VCU {
    struct BMS_A0h{
        // 0byte
        unsigned short BMS_HVBatCrnt; // 16 bit
        // 2byte
        unsigned short BMS_HVBatVol; // 16 bit
        // 4byte
        unsigned char BMS_HVBatSOC; // 8bit
        // 5byte - 3개
        unsigned char BMS_Sys_Sts:3; // 3bit
        unsigned char BMS_Charge_StsCc2:1; // 1bit
        unsigned char BMS_Charge_StsCc:1; // 1bit
        unsigned char reserved:3; // 3bit
        // 6byte
        unsigned char BMS_Sys_Flt; // 8bit
        // 7byte
        unsigned char BMS_HVDisplaySOH; // 8bit
    };

    struct VCU_MCU_Request{
        // 0byte
        unsigned char MCU_VCU_Motor_Request_Valid:1; //1bit
        unsigned char MCU_DriveMode:2; //2bit - > 3bit
        unsigned char MCU_Clamping_Brake_Req:1; //1bit --> 4bit
        unsigned char reserved:4; //
        // 1byte
        unsigned short MCU_Torque_Req;
        // 3byte
        unsigned short MCU_Speed_Req; // 16 bit
        // 5byte
        unsigned char reserved2[3];
    };

    struct MCU_Torque_Feedback{
        unsigned long long MCU_Shift:2; // 2
        unsigned long long MCU_SPEED:18; // 20
        unsigned long long MCU_TORQUE:16; // 36
        unsigned long long MCU_CURRENT:12; // 48
        unsigned long long MCU_MOTORTEMP:8; // 56
        unsigned long long MCU_ERRORCODE:8; //64
    };
    struct VCU_Vehicle_ErrorCode{
        unsigned short Error_Code:10; //10
        unsigned short reserved:4; //14
        unsigned short Veh_Bat_St:2; // 16
        unsigned char Low_voltage; // 24
        unsigned char Residual_Pressure:1; //25 -1
        unsigned char Charge_Abnormal:1; //26 -2
        unsigned char reserved2:6; // 32
        unsigned char reserved3[4];
    };
    struct DBS_Status2{
        unsigned long long DBS_Fault_Code:24; //24
        unsigned long long DBS_WarringCode:16; //40
        unsigned long long reserved:8; //48
        unsigned long long DBS_RollingCounter2:4; //52
        unsigned long long reserved2:4; // 56
        unsigned long long DBS_CheckSum2:8; // 64
    };
    // select

    struct Vehicle_Mileage1{
        unsigned long long Vehicle_ODO1:24; // 24
        unsigned long long Vchicle_AD_Mileage1:24; //48
        unsigned long long Vehicle_Mileage1_MsgCntr:4; // 52
        unsigned long long reserved:12; //64
    };

    struct DBS_Status{
        unsigned char DBS_System_Status:2; //2
        unsigned char reserved:4; // 6
        unsigned char DBS_Park_Warning:2; // 8
        unsigned char DBS_Work_Mode; // 16
        unsigned char BrakePressureReqACK; // 24
        unsigned char DBS_HP_pressure; // 32
        unsigned char DBS_PeadalOpening; // 40
        unsigned char DBS_Ref_Iq; // 48
        unsigned char DBS_RollingCounter:4; //52
        unsigned char reserved2:2; //54
        unsigned char DBS_EstopFlag:1; // 55
        unsigned char DBS_PedaiFlag:1; // 56
        unsigned char DBS_CheckSum; //64.
    };
    struct VCU_DBS_Request{
        unsigned char VCU_DBS_Request_Flag; //8
        unsigned char VCU_DBS_Work_Mode; //16
        unsigned char VCU_DBS_Pressure_Request; //24
        unsigned char VCU_ABS_Active; // 32
        unsigned char reserved[4];
    };
    struct Vehicle_Odometer_Status{
        unsigned long long Vehicle_ODO:18; // 18
        unsigned long long Vehicle_TRIP:12; // 30
        unsigned long long Vehicle_Remote_Mileage:12; //42
        unsigned long long Vehicle_AD_Mileage:18; // 60
        unsigned long long Vehicle_Odometer_MsgCntr:4; //64
    };
    struct VCU_Vehicle_Status_2{
        unsigned short Vehicle_Speed; // 16
        unsigned short Vehicle_Brake_Pressure; // 16
        unsigned short Vehicle_Steering_Angle; //16
        unsigned short reserved:12; //12
        unsigned short Vehicle_Status_2_MsgCntr:4;
    };

    struct Remote_Control_IO{
        unsigned char Remote_E; //0 8
        unsigned char Remote_F; //1 16
        unsigned char Remote_A; //2 24
        unsigned char Remote_B; //3 32
        unsigned char Remote_C; //4 40
        unsigned char Remote_D; //5 48
        unsigned short reserved;
    };

}
#pragma pack(pop)
#endif //WM_MOTION_CONTROLLER_CAN2VCU_DBC_H

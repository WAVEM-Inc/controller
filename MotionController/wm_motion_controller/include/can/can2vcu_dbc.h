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

}
#pragma pack(pop)
#endif //WM_MOTION_CONTROLLER_CAN2VCU_DBC_H

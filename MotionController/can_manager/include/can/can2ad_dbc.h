//
// Created by msi-341 on 24. 3. 25.
//

#ifndef WM_MOTION_CONTROLLER_CAN2AD_DBC_H
#define WM_MOTION_CONTROLLER_CAN2AD_DBC_H
#pragma pack(push, 1)
namespace AD{
    struct AD_Setup_Control{
        unsigned char AD_Release_Emergency_Button:1; //1
        unsigned char AD_Release_F_Bumper:1;//2
        unsigned char AD_Release_B_Bumper:1;//3
        unsigned char AD_Release_L_Bumper:1;//4
        unsigned char AD_Release_R_Bumper:1;//5
        unsigned char reserved:3;//8
        unsigned char AD_Clear_TRIP:1;//9
        unsigned char AD_Disable_F_Bumper:1;//10
        unsigned char AD_Disable_B_Bumper:1;//11
        unsigned char AD_Disable_L_Bumper:1;//12
        unsigned char AD_Disable_R_Bumper:1;//13
        unsigned char reserved2:3; //16
        unsigned char CAN_Sign_tran_State:1; //17
        unsigned char reserved3:7; //24
        unsigned char reserved4[5];
    };
    struct System_Power_Control {
        unsigned char AD_Sys_Power_Control: 2; // 1 byte 2bit
        unsigned char Reserved_Sys_Power_Control: 2; // 1 byte 2bit
        unsigned char Network_Sys_Power_Control: 2; //1 byte 2bit
        unsigned char Radar_Sys_Power_Control: 2; //1 byte 2bit  - 1byte
        //1 byte
        unsigned char Business_Sys_Power_Control: 2; // 1byte 2bit - 1byte 2bit
        unsigned char reserved: 6; // 1byte 6bit - 2byte
        //2 byte
        unsigned short reserved2; // 2byte - 4byte
        //4 byte
        unsigned char Vehicle_Work_Mode_Control: 2; // 1byte 2bit - 4byte 2bit
        unsigned char reserved3: 6; //1byte 6bit - 5 byte
        //5byte
        unsigned char reserved4[3]; //3byte - 8byte
    };
    struct Power_on_CAN {
        unsigned char Vehicle_Power_Req; //1byte
        unsigned char reserved[7];
    };
    struct AD_Control_Body {
        //0byte
        unsigned char AD_Body_Valid: 4; // 4bit
        unsigned char reserved: 4; // 8bit
        //1byte
        unsigned char AD_Brake_Light: 1; // 1bit - 8
        unsigned char AD_Double_Flash_Light: 1; // 2bit - 9
        unsigned char AD_Reversing_Lights: 1; // 3bit - 10
        unsigned char AD_Low_Beam: 1; //4bit - 11
        unsigned char AD_Left_Turn_Light: 1; //5bit - 12
        unsigned char AD_Right_Turn_Light: 1; //6bit - 13
        unsigned char AD_Horn_Control: 1; // 7bit - 14
        unsigned char AD_High_Beam: 1; // 8bit - 15
        //2byte
        unsigned char AD_Fof_Light: 1; //1bit - 16
        unsigned char reserved2: 7; //7bit - 17
        //3byte
        unsigned char reserved3[5];
    };

    struct AD_Control_Accelerate{
        //0byte
        unsigned short AD_Accelerate_Valid:4; // 4bit
        unsigned short AD_Acc:12; // 12 bit
        //2byte - 16
        unsigned char AD_Accelerate_Work_Mode; //8bit
        //3byte - 24
        unsigned char AD_Accelerate_Gear; //8bit
        //4byte - 32
        unsigned char reserved2; // 8bit
        //5byte - 40
        unsigned char AD_Torque_Control; // 8bit
        //6byte - 48
        unsigned short AD_Speed_Control; // 16bit
    };
    struct AD_Control_Brake{
        // 0byte
        unsigned char AD_DBS_Valid:4; //4bit
        unsigned char reserved:4; //4bit
        // 1byte
        unsigned char AD_BrakePressure_Cmd; //8bit
        // 2byte
        unsigned char reserved2[6];
    };
    /**

AD_Steering_Angle_Cmd

     */
    struct AD_Control_Steering{
        //0byte
        unsigned char AD_Steering_Valid:4; // 4bit
        unsigned char reserved:4; // 4bit
        //1byte
        unsigned char AD_Steering_Speed_Cmd; // 8bit
        //2byte
        unsigned short reserved2; // 16bit
        //4byte
        unsigned short AD_Steering_Angle_Cmd; // 16bit
        //6byte
        unsigned short reserved3; // 16bit
    };
}
#pragma pack(pop)
#endif //WM_MOTION_CONTROLLER_CAN2AD_DBC_H

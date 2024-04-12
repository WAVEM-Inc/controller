
#ifndef CAN_DEFINE_H
#define CAN_DEFINE_H

#define  CNV_SPEED_FACTOR 3.6
#define  RESOLUTION_SPEED_CTRL 10
#define  RESOLUTION_STEERING_CTRL 10.0
#define  RESOLUTION_BMS_SOC 0.4
#define RESOLUTION_VEHICLE_SPEED 0.1
#define RESOLUTION_VEHICLE_BRAKE_PRESSURE 0.01
#define OFFSET_VEHICLE_STATUS_SPEED 80
#define OFFSET_DBS_WARRINGCODE 65535.0
#define  OFFSET_STEERING 30
#define OFFSET_TORQUE 10000
#define  OFFSET_STRANGLE 3000
#define  MAX_STEERING 31
#define  MIN_STEERING -31

enum MSG_ID {
  DBS_STATUS = 0x142,
  DBS_STATUS2 = 0x143,
  AD_CONTROL_BODY	=	0x506, // AD_CONTROL_BODY
  AD_CONTROL_ACCELERATE	=	0x504,
  AD_CONTROL_BRAKE	=	0x503,
  AD_CONTROL_STEERING	=	0x502,
  AD_SETUP_CONTROL = 0x507,
  TORQUE_FEEDBACK = 0x10,
  BMS_A0H = 0xa0,
  VCU_VEHICLE_ERRORCODE = 0x30E,
  VCU_VEHICLE_STATUS_2 = 0x304
};

enum SVC_ID {
  CONTROL_STEERING,
  CONTROL_ACCELERATE,
  CONTROL_HARDWARE,
  RPM_FEEDBACK
};

enum ACC_GEAR {
   PARKING,
   FORWARD,
   NEUTRAL,
   REVERSE
};

enum CHANNEL_TYPE { CAN0 } ;

/**
 * @brief Test device type
 * 
static const char *device_type[] =
        { "can0", "can1"};
*/
/**
 * @brief Test device type
 * 
 */
static const char *device_type[] =
        { "can0"};
#define CAN_ALIVE_CHECKTIME 2 // second
#define CAN_RECV_RETRY_TIME 2 // second

#endif

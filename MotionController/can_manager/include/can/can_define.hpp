
#ifndef CAN_DEFINE_H
#define CAN_DEFINE_H

#define  CNV_SPEED_FACTOR 3.6
#define  RESOLUTION_SPEED_CTRL 10
#define  RESOLUTION_STEERING_CTRL 10.0

#define  OFFSET_STEERING 30
#define  OFFSET_STRANGLE 3000
#define  MAX_STEERING 30
#define  MIN_STEERING -30

enum MSG_ID {
  DBS_STATUS = 0x142,
  DBS_STATUS2 = 0x143,
  AD_CONTROL_HARDWARE	=	0x506,
  AD_CONTROL_ACCELERATE	=	0x504,
  AD_CONTROL_BRAKE	=	0x503,
  AD_CONTROL_STEERING	=	0x502,
  TORQUE_FEEDBACK = 0x10 // [v]
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

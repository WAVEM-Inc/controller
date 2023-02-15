#define CDR_MOTOR_TTY "/dev/ttyUSB0"
#define  ESS_KEY     9527
#define  KEY_NUM     9527
#define  MEM_SIZE    1024
//
#define RECV_SIZE 1024
#define SEND_SIZE 1024
#define RECV_LEFT_START 2
#define RECV_LEFT_END 5
#define RECV_RIGHT_START 7
#define RECV_RIGHT_END 10
#define  ESS_SIZE    sizeof(struct epoll_sensor_info)

#define TP_CMD_VEL "cmd_vel"

struct left_encor_info{
	int encor_left;
};

struct right_encor_info{
	int encor_right;
};

struct epoll_sensor_info {
	struct left_encor_info left_encor_data;
	struct right_encor_info right_encor_data;
};


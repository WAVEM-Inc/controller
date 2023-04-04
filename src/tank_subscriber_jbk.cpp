#include "ros/ros.h"                          // ROS Default Header File
#include "ros_tutorials_topic/MsgTutorial.h"  // MsgTutorial Message File Header. The header file is automatically created when building the package.
#include <geometry_msgs/Twist.h>
#include "../include/gpio_ctrl.h"

#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

// 2020-10-14 JBK
#include <linux/input.h>
#include <semaphore.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// 2020-10-14 JBK
#define ESS_KEY 9527	// Shared Memory Key
#define MEM_SIZE 1024 	// Shared Memory Size

#define RIGHT_MOTOR 1
#define LEFT_MOTOR 2
#define RIGHT_MOTOR_DIR 12
#define LEFT_MOTOR_DIR 6

#define LIGHT_RED 118
#define LIGHT_GREEN 117

#define INIT_PERIOD 10000

// 2020-10-14 JBK
struct left_encor_info {
	int encor_left;
};

struct right_encor_info {
	int encor_right;
};

struct epoll_sensor_info {
	struct left_encor_info left_encor_data;
	struct right_encor_info right_encor_data;
};

/////////////////////////////////////minseok//////////////////////////////
int light_init(void)
{
	gpio_export(LIGHT_GREEN);
	gpio_export(LIGHT_RED);
	gpio_set_output(LIGHT_GREEN);
	gpio_set_output(LIGHT_RED);
	gpio_set_val(LIGHT_GREEN,0);
	gpio_set_val(LIGHT_RED,0);
}

int light_set_val(int light_val)
{
	if((light_val != 0) && (light_val !=1) && (light_val !=2))
	{
		printf("light_val value 0 or 1\n");
		return -1;
	}
	if(light_val == 1)
	{
		gpio_set_val(LIGHT_GREEN,1);
		gpio_set_val(LIGHT_RED,0);
	}
	else if(light_val ==2)
	{
		gpio_set_val(LIGHT_GREEN,0);
		gpio_set_val(LIGHT_RED,1);
	}
	else
	{
		gpio_set_val(LIGHT_GREEN,0);
		gpio_set_val(LIGHT_RED,0);
	}
	return 0;
}

int dcmotor_init(void)
{
	//set pwm
	pwm_export(RIGHT_MOTOR);
	pwm_export(LEFT_MOTOR);
	pwm_set_period(RIGHT_MOTOR,INIT_PERIOD);
	pwm_set_period(LEFT_MOTOR,INIT_PERIOD);
	pwm_set_enable(RIGHT_MOTOR);
	pwm_set_enable(LEFT_MOTOR);
	//set gpio
	gpio_export(LEFT_MOTOR_DIR);
	gpio_export(RIGHT_MOTOR_DIR);
	gpio_set_output(LEFT_MOTOR_DIR);
	gpio_set_output(RIGHT_MOTOR_DIR);
	gpio_set_val(LEFT_MOTOR_DIR,0);
	gpio_set_val(RIGHT_MOTOR_DIR,0);
	return 0;
}
int dcmotor_disable(void)
{
	pwm_set_disable(RIGHT_MOTOR);
	pwm_set_disable(LEFT_MOTOR);
	return 0;
}

int dcmotor_set_speed(int motor,int speed)
{
	int motor_speed, motor_dir;
	motor_speed = abs(speed);

	if(speed < 0)
	{
		motor_dir = 0;
	}
	else
	{
		motor_dir = 1;
	}

	if((motor_speed > 250) || (motor_speed < -250))
	{
		printf("Speed range -100 ~ 100.\n");
		return -1;
	}
	else if(motor_speed == 0)
	{
		pwm_set_dutycycle(motor, 0);
		return 1;
	}

	if(motor == 1)
	{
		gpio_set_val(LEFT_MOTOR_DIR, motor_dir);
	}
	else if(motor == 2)
	{
		gpio_set_val(RIGHT_MOTOR_DIR, motor_dir);
	}
	else
	{
		printf("Motor value : RIGHT - 2, LEFT - 1\n");
	}
	pwm_set_dutycycle(motor, 2200 + motor_speed * 31);
}

// 2020-10-14 JBK Shared Memory & Semaphore Code

static int getEncoderValue()
{
	int epoll_shm_id;

	struct epoll_sensor_info *epoll_shm;

	struct left_encor_info *left_encor_data;
	struct right_encor_info *right_encor_data;

	if ((epoll_shm_id = shmget((key_t)ESS_KEY, MEM_SIZE, IPC_CREAT | 0666)) == -1)
	{
		perror("shmid failed");
		return -1;
	}

	printf("shmid : %d\n", epoll_shm_id);

	if ((void *)-1 == (epoll_shm = static_cast<epoll_sensor_info*>(shmat(epoll_shm_id, 0x0, 0))))
	{
		perror("shmat failed");
		return -1;
	}

	left_encor_data = &epoll_shm->left_encor_data;
	right_encor_data = &epoll_shm->right_encor_data;

	while (1)
	{
		printf("Left : %d\n", *left_encor_data);
		printf("Right : %d\n", *right_encor_data);

		sleep(1);
	}

	return EXIT_SUCCESS;
}

// Message callback function. This is a function is called when a topic
// message named 'ros_tutorial_msg' is received. As an input message,
// the 'MsgTutorial' message of the 'ros_tutorials_topic' package is received.
void msgCallback(const geometry_msgs::Twist& cmd_vel_msg)
{
	float vel_linear,vel_angular;
	vel_linear = cmd_vel_msg.linear.x;
	vel_angular = cmd_vel_msg.angular.z;

	printf("linear = %.02f,angular = %.02f\n", vel_linear, vel_angular);
		dcmotor_set_speed(1,150*vel_linear - 150*vel_angular);
		dcmotor_set_speed(2,-(150*vel_linear + 150*vel_angular));
}

int main(int argc, char **argv)                         // Node Main Function
{
	dcmotor_init();
	light_init();	
	ros::init(argc, argv, "topic_subscriber");            // Initializes Node Name
	ros::NodeHandle nh;                                   // Node handle declaration for communication with ROS system
	//ros::Subscriber ros_tutorial_sub = nh.subscribe("cmd_vel", 100, msgCallback);
	getEncoderValue();

	ros::spin();

	return 0;
}

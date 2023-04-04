#include "ros/ros.h"                          // ROS Default Header File
#include "ros_tutorials_topic/MsgTutorial.h"  // MsgTutorial Message File Header. The header file is automatically created when building the package.
#include <geometry_msgs/Twist.h>
#include "../include/gpio_ctrl.h"

#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#define RIGHT_MOTOR 1
#define LEFT_MOTOR 2
#define RIGHT_MOTOR_DIR 12
#define LEFT_MOTOR_DIR 6

#define AC_PULS2 15
#define AC_SIGN2  97

#define LIGHT_RED 118
#define LIGHT_GREEN 117

#define INIT_PERIOD 10000

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
		printf("Speed range -90 ~ 90.\n");
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
	pwm_set_dutycycle(motor, 7000 + motor_speed * 12);
}

// Message callback function. This is a function is called when a topic
// message named 'ros_tutorial_msg' is received. As an input message,
// the 'MsgTutorial' message of the 'ros_tutorials_topic' package is received.
float ac_angular_bak = 0;
void msgCallback(const geometry_msgs::Twist& cmd_vel_msg)
{
	float vel_linear,vel_angular;
	float ac_state;
	vel_linear = cmd_vel_msg.linear.x;
	vel_angular = cmd_vel_msg.angular.z;
	printf("linear = %.02f,angular = %.02f\n", vel_linear, vel_angular);
	ac_state = abs(ac_angular_bak - vel_angular);
	if((vel_linear == 0) && (vel_angular == 0))
	{
		light_set_val(1);
		system("amixer sset 'Headphone' 0");
	}
	else
	{
		light_set_val(2);
		system("amixer sset 'Headphone' 45");
	}
	if(ac_state > 0.00001)
	{
		printf("state=%f,bak=%f,vel=%f\n",ac_state,ac_angular_bak,vel_angular);
		writeAcPulse((vel_angular-ac_angular_bak)*1500);
		ac_angular_bak = vel_angular;
	}
	dcmotor_set_speed(1,vel_linear*60);
	dcmotor_set_speed(2,vel_linear*60);
}

int main(int argc, char **argv)                         // Node Main Function
{
	dcmotor_init();
	light_init();
	initAc();	
	ros::init(argc, argv, "control_subscriber");            // Initializes Node Name
	ros::NodeHandle nh;                                   // Node handle declaration for communication with ROS system
	ros::Subscriber ros_tutorial_sub = nh.subscribe("cmd_vel", 100, msgCallback);

	ros::spin();

	return 0;
}

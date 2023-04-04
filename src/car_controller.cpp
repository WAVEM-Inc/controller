#include "ros/ros.h"                          // ROS Default Header File
#include "ros_tutorials_topic/MsgTutorial.h"  // MsgTutorial Message File Header. The header file is automatically created when building the package.
#include <geometry_msgs/Twist.h>
#include "../include/gpio_ctrl.h"

#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define RIGHT_MOTOR 1
#define LEFT_MOTOR 2
#define RIGHT_MOTOR_DIR 12
#define LEFT_MOTOR_DIR 6

#define AC_PULS2 15
#define AC_SIGN2  97

#define INIT_PERIOD 10000

/////////////////////////////////////minseok//////////////////////////////


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
		motor_dir = 1;
	}
	else
	{
		motor_dir = 0;
	}

	if((motor_speed > 60) || (motor_speed < -60))
	{
		printf("Speed range -60 ~ 60.\n");
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

int initAc(void)
{
	gpio_export(AC_PULS2);
	gpio_export(AC_SIGN2);
	gpio_set_output(AC_PULS2);
	gpio_set_output(AC_SIGN2);
	gpio_set_val(AC_PULS2,1);
	gpio_set_val(AC_SIGN2,1);
}
int writeAcPulse(int num)
{
	int lp;
	int pulse_num;
	int ac_pulse;
	pulse_num=abs(num);
	if(num < 0)
	{
		ac_pulse = AC_SIGN2;
	}
	else if (num > 0)
	{
		ac_pulse = AC_PULS2;
	}
	for(lp=0;lp<pulse_num;lp++)
	{
		gpio_set_val(ac_pulse,0);
		usleep(1);
		gpio_set_val(ac_pulse,1);
		usleep(1);
	}
}

////////////////////////////////////////////////////////

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

	/*
	   if(ac_state > 0.00001)
	   {
	   printf("state=%f,bak=%f,vel=%f\n",ac_state,ac_angular_bak,vel_angular);
	   writeAcPulse((vel_angular-ac_angular_bak)*1500);
	   ac_angular_bak = vel_angular;
	   }
	   */
	/*
	   dcmotor_set_speed(1,vel_linear*1100);
	   dcmotor_set_speed(2,vel_linear*1100);
	   */
	//	ac_state = abs(ac_angular_bak - vel_angular);
	if((vel_angular > 0) && (vel_linear == 0))
	{
		//		if(ac_state > 0.00001)
		//		{
		printf("state=%f,bak=%f,vel=%f\n",ac_state,ac_angular_bak,vel_angular);
		vel_angular = 2.1;
		writeAcPulse((vel_angular-ac_angular_bak)*1500);
		ac_angular_bak = vel_angular;
		//		}
		dcmotor_set_speed(1,30);
		dcmotor_set_speed(2,50);	
	}
	else if((vel_angular < 0) && (vel_linear == 0))
	{
		//		if(ac_state > 0.00001)
		//		{
		printf("state=%f,bak=%f,vel=%f\n",ac_state,ac_angular_bak,vel_angular);
		vel_angular = -2.1;
		writeAcPulse((vel_angular-ac_angular_bak)*1500);
		ac_angular_bak = vel_angular;
		//		}
		dcmotor_set_speed(1,50);
		dcmotor_set_speed(2,30);	
	}
	else if(vel_linear !=0)
	{
		//		if(ac_state > 0.00001)
		//		{
		printf("state=%f,bak=%f,vel=%f\n",ac_state,ac_angular_bak,vel_angular);
		vel_angular = vel_angular * 2.1;
		writeAcPulse((vel_angular-ac_angular_bak)*1500);
		ac_angular_bak = vel_angular;
		//		}
		dcmotor_set_speed(1,40*vel_linear);
		dcmotor_set_speed(2,40*vel_linear);
	}
	else
	{
		vel_angular = 0;
		writeAcPulse((vel_angular-ac_angular_bak)*1500);
		ac_angular_bak = vel_angular;
		dcmotor_set_speed(1,0);
		dcmotor_set_speed(2,0);
	}
}

int main(int argc, char **argv)                         // Node Main Function
{
	dcmotor_init();
	initAc();	
	ros::init(argc, argv, "topic_subscriber");            // Initializes Node Name
	ros::NodeHandle nh;                                   // Node handle declaration for communication with ROS system
	ros::Subscriber ros_tutorial_sub = nh.subscribe("cmd_vel", 100, msgCallback);

	ros::spin();

	return 0;
}

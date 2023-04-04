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

static pthread_t acmotor_thread;
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

int dcmotor_set_speed(int motor,float speed)
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
	if(speed == 0)
	{
		pwm_set_dutycycle(motor, 0);
	}
	else
	{
		pwm_set_dutycycle(motor, 7300 + motor_speed * 12);
		printf("motor_pwm=%d\n",7300+motor_speed*12);
	}
}
int acmotor_pulse=0;
int acmotor_pulse_flag=0;
void *do_acmotor(void *arg)
{
	int lp;
	int pulse_num;
	int ac_pulse=0;
	while(1)
	{
//		if(acmotor_pulse_flag==0)
		while(!(acmotor_pulse==0))
		{
//			pulse_num=abs(acmotor_pulse);
			if(acmotor_pulse < 0)
			{
				ac_pulse = AC_SIGN2;
				acmotor_pulse++;
			}
			else if (acmotor_pulse > 0)
			{
				ac_pulse = AC_PULS2;
				acmotor_pulse--;
			}
//			for(lp=0;lp<pulse_num;lp++)
//			if(abs(acmotor_pulse) < 1000)
			{
				gpio_set_val(ac_pulse,0);
////				usleep(1);
				gpio_set_val(ac_pulse,1);
				usleep(1);
			}
			/*
			else
			{
				gpio_set_val(ac_pulse,0);
				usleep(1);
				gpio_set_val(ac_pulse,1);
				usleep(1);
			}
			*/
//			acmotor_pulse_flag = 1;
		}
		usleep(10000);
	}
}
int initAc(void)
{
	gpio_export(AC_PULS2);
	gpio_export(AC_SIGN2);
	gpio_set_output(AC_PULS2);
	gpio_set_output(AC_SIGN2);
	gpio_set_val(AC_PULS2,1);
	gpio_set_val(AC_SIGN2,1);

	pthread_create(&acmotor_thread, 0, do_acmotor, 0);
	pthread_detach(acmotor_thread);
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

float ac_angular_bak = 0;
void msgCallback(const geometry_msgs::Twist& cmd_vel_msg)
{
	float vel_linear,vel_angular;
	float ac_state;
	float steer_angle, steer_val;
	vel_linear = cmd_vel_msg.linear.x;
	vel_angular = cmd_vel_msg.angular.z;
	printf("linear = %.02f,angular = %.02f\n", vel_linear, vel_angular);
	steer_angle= (vel_angular)/(0.0001+vel_linear*2);
	if(steer_angle > 0.7)
	{
		steer_angle = 0.7;
	}
	else if(steer_angle < -0.7)
	{
		steer_angle = -0.7;
	}
	steer_val = steer_angle/0.7*2000;
	//	ac_state = fabs(ac_angular_bak - vel_angular);
//	ac_state = fabs(ac_angular_bak - steer_val);
//	if(ac_state > 0.00001)
	{
		if((fabs(steer_val) <= 2000) )
		{
			acmotor_pulse = acmotor_pulse+steer_val-ac_angular_bak;
			ac_angular_bak = steer_val;
		}
	}
	if(vel_linear > 0.09)
	{
		dcmotor_set_speed(1,(vel_linear+0.05)*80);
		dcmotor_set_speed(2,(vel_linear+0.05)*80+15);
	}
	else if(vel_linear <-0.09)
	{
		dcmotor_set_speed(1,(vel_linear-0.05)*80);
		dcmotor_set_speed(2,(vel_linear-0.05)*80);
	}
	else if(vel_linear > 0.001)
	{
		dcmotor_set_speed(1,(vel_linear+fabs(vel_angular)*0.2+0.05)*80);
		dcmotor_set_speed(2,(vel_linear+fabs(vel_angular)*0.2+0.05)*80+15);
	}
	else if(vel_linear <-0.001)
	{
		dcmotor_set_speed(1,(vel_linear-fabs(vel_angular)*0.2-0.05)*80);
		dcmotor_set_speed(2,(vel_linear-fabs(vel_angular)*0.2-0.05)*80);
	}
	else if(vel_angular > 0)
	{
		dcmotor_set_speed(1,(fabs(vel_angular)*0.5+0.2)*80);
		dcmotor_set_speed(2,(fabs(vel_angular)*0.5+0.2)*80+15);
	}
	else if(vel_angular < 0)
	{
		dcmotor_set_speed(1,(fabs(vel_angular)*0.5+0.2)*80);
		dcmotor_set_speed(2,(fabs(vel_angular)*0.5+0.2)*80);
	}
	else
	{
		//require break add
		dcmotor_set_speed(1,0);
		dcmotor_set_speed(2,0);
	}
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

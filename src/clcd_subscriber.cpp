#include "ros/ros.h"                          // ROS Default Header File
#include "ros_tutorials_topic/MsgTutorial.h"  // MsgTutorial Message File Header. The header file is automatically created when building the package.
#include <geometry_msgs/Twist.h>
#include <actionlib_msgs/GoalStatusArray.h>
#include "../include/gpio_ctrl.h"
#include "../include/clcd_ctrl.h"

#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define RIGHT_MOTOR 1
#define LEFT_MOTOR 2
#define RIGHT_MOTOR_DIR 12
#define LEFT_MOTOR_DIR 6

#define LIGHT_RED 118
#define LIGHT_GREEN 117

#define INIT_PERIOD 10000

int fd;
int run_stat=0;
void msgCallback(const geometry_msgs::Twist& cmd_vel_msg)
{
	char vel_lin[32],vel_ang[32],stat_run[32];
	float vel_linear,vel_angular;
	memset(vel_lin,0,sizeof(vel_lin));
	memset(vel_ang,0,sizeof(vel_ang));
	memset(stat_run,0,sizeof(stat_run));
	vel_linear = cmd_vel_msg.linear.x;
	vel_angular = cmd_vel_msg.angular.z;

	sprintf(stat_run,"Stat : %d", run_stat);
	sprintf(vel_lin,"Lin : %f", vel_linear);
	sprintf(vel_ang,"Ang : %f", vel_angular);
	printf("LINE=%d\n",__LINE__);
	//	clcd_clear(fd);
	clcd_setcursor(fd,0,0);
	clcd_write(fd,"WaveM Wabot2020");
	clcd_setcursor(fd,0,1);
	clcd_write(fd,stat_run);
	clcd_setcursor(fd,0,2);
	clcd_write(fd,vel_lin);
	clcd_setcursor(fd,0,3);
	clcd_write(fd,vel_ang);
}
void statmsgCallback(const actionlib_msgs::GoalStatusArray& stat_msg)
{
	if (!stat_msg.status_list.empty())
	{
		actionlib_msgs::GoalStatus goalStatus = stat_msg.status_list[0];
		run_stat=stat_msg.status_list[0].status;
	}
}
int main(int argc, char **argv)                         // Node Main Function
{
	ros::init(argc, argv, "clcd_subscriber");            // Initializes Node Name
	ros::NodeHandle nh;                                   // Node handle declaration for communication with ROS system

	fd = serialOpen("/dev/ttymxc1",115200);
	clcd_init(fd);
	clcd_setcursor(fd,0,0);
	clcd_write(fd,"WaveM Wabot2020");
	clcd_setcursor(fd,0,1);
	clcd_write(fd,"Stat : 0");
	clcd_setcursor(fd,0,2);
	clcd_write(fd,"Lin : no");
	clcd_setcursor(fd,0,3);
	clcd_write(fd,"Ang : no");

	ros::Subscriber ros_tutorial_sub = nh.subscribe("cmd_vel", 1, msgCallback);
	ros::Subscriber stat_tutorial_sub = nh.subscribe("move_base/status", 1, statmsgCallback);

	ros::spin();
	serialClose(fd);
	return 0;
}

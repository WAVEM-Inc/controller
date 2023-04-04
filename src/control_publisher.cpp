#include "ros/ros.h"                            // ROS Default Header File
#include "ros_tutorials_topic/MsgTutorial.h"    // MsgTutorial Message File Header. The header file is automatically created when building the package.
#include <geometry_msgs/Twist.h>

#define ROS_TOPIC "/cmd_vel"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<time.h>

int bt_fd;
int get_bt_val(int bt_bak)
{
	int lp;
	char buff[64], UlSonic[8];
	memset(buff,0,sizeof(buff));
	read(bt_fd , buff, 256);
	if(strstr(buff,"FORWARD")!=NULL)
	{
		return 1;
	}
	else if(strstr(buff,"LF")!=NULL)
	{
		return 2;
	}
	else if(strstr(buff,"RF")!=NULL)
	{
		return 3;
	}
	else if(strstr(buff,"LEFT")!=NULL)
	{
		return 4;
	}
	else if(strstr(buff,"RIGHT")!=NULL)
	{
		return 5;
	}
	else if(strstr(buff,"LB")!=NULL)
	{
		return 6;
	}
	else if(strstr(buff,"RB")!=NULL)
	{
		return 7;
	}
	else if(strstr(buff,"BACK")!=NULL)
	{
		return 8;
	}
	else if(strstr(buff,"STOP")!=NULL)
	{
		return 0;
	}
	else if(strstr(buff,"EMERGENCY")!=NULL)
	{
		return 0;
	}
	else
	{
		return 0;
	}
}
int main(int argc, char **argv)                 // Node Main Function
{
	int bt_val = 0, bt_val_bak=0;
	float linear_x, angular_z = 0.0;
	bt_fd = open( "/dev/rfcomm0" , O_RDONLY);

	ros::init(argc, argv, "control_publisher");     // Initializes Node Name
	ros::NodeHandle n;

	geometry_msgs::Twist cmd;
	ros::Publisher velocityPublisher;

	cmd.linear.x = cmd.linear.y = cmd.angular.z = 0.0;
	velocityPublisher = n.advertise<geometry_msgs::Twist>(ROS_TOPIC, 1);

	ros::Rate loop_rate(10);
	while (ros::ok())
	{
		bt_val=get_bt_val(bt_val_bak);
		bt_val_bak=bt_val;
		switch(bt_val)
		{
			case 0:	cmd.linear.x = 0; cmd.angular.z =0;		break;
			case 1:	cmd.linear.x = 0.8; cmd.angular.z =0;		break;
			case 2:	cmd.linear.x = 0.8; cmd.angular.z =0.8;		break;
			case 3:	cmd.linear.x = 0.8; cmd.angular.z =-0.8;	break;
			case 4:	cmd.linear.x = 0.8; cmd.angular.z =1.6;		break;
			case 5:	cmd.linear.x = 0.8; cmd.angular.z =-1.6;	break;
			case 6:	cmd.linear.x = -1; cmd.angular.z =1.6;	break;
			case 7:	cmd.linear.x = -1; cmd.angular.z =-1.6;	break;
			case 8:	cmd.linear.x = -1; cmd.angular.z =0;		break;

			default:
					return -2 ;
		}
		velocityPublisher.publish(cmd);

		ros::spinOnce();
		loop_rate.sleep();
	}
	close(bt_fd);
	return 0;
}

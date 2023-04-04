/**
 * @file 	clcd_subscriber_jbk.cpp
 * @author	BMS -> JBK
 * @date 	2021-03-04
 * @brief	mpc_follow_mode Topic msg show on LCD Module.
 */

#include "ros_tutorials_topic/MsgTutorial.h" 
#include "ros/ros.h"                          
#include <mpc_follow_mode/UiClient.h>
#include <mpc_follow_mode/Detect.h>

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
int mode_stat = 0;
char *c_mode;

/**
 * @brief	Follw Mode Info Msg Callback function
 * @param	const mpc_follow_mode::UiClientConstPtr &ui_clinet
 */
void statmsgCallback(const mpc_follow_mode::UiClient &ui_client)
{
	char c_ui_client[32];

	memset(c_ui_client, 0, sizeof(c_ui_client));

	mode_stat = ui_client.cmd;


	switch(mode_stat)
	{
		case 1:
			c_mode = "Start";
			clcd_clear(fd);
			sprintf(c_ui_client,"Mode : %s", c_mode);
			clcd_setcursor(fd, 0, 1);
			clcd_write(fd, c_ui_client);
			break;
		case 2:
			c_mode = "ReStart";
			clcd_clear(fd);
			sprintf(c_ui_client,"Mode : %s", c_mode);
			clcd_setcursor(fd, 0, 1);
			clcd_write(fd, c_ui_client);
			break;
		case 3:
			c_mode = "Stop";
			clcd_clear(fd);
			sprintf(c_ui_client,"Mode : %s", c_mode);
			clcd_setcursor(fd, 0, 1);
			clcd_write(fd, c_ui_client);
			break;
		case 4:
			c_mode = "Follow";
			clcd_clear(fd);
			sprintf(c_ui_client,"Mode : %s", c_mode);
			clcd_setcursor(fd, 0, 1);
			clcd_write(fd, c_ui_client);
			break;
		case 5:
			c_mode = "Drive";
			clcd_clear(fd);
			sprintf(c_ui_client,"Mode : %s", c_mode);
			clcd_setcursor(fd, 0, 1);
			clcd_write(fd, c_ui_client);
			break;
		default:
			c_mode = "Wait";
			sprintf(c_ui_client,"Mode : %s", c_mode);
			clcd_setcursor(fd, 0, 1);
			clcd_write(fd, c_ui_client);
			break;
	}
}

void trackingErrormsgCallback(const mpc_follow_mode::TrackerUserArray &ptr)
{
	if (ptr.run == 1)
	{
		clcd_setcursor(fd, 0, 1);
		clcd_write(fd, "Tracking Person");
		clcd_setcursor(fd, 0, 2);
		clcd_write(fd, "Move Forward ");
		clcd_setcursor(fd, 0, 3);
		clcd_write(fd, "Skip Detection");
	}
	else if (ptr.run == 2)
	{
		clcd_setcursor(fd, 0, 1);
		clcd_write(fd, "I don't know");
		clcd_setcursor(fd, 0, 2);
		clcd_write(fd, "I don't know");
		clcd_setcursor(fd, 0, 3);
		clcd_write(fd, "FFD!!");
	}
	else if (ptr.run == 4)
	{
		clcd_setcursor(fd, 0, 1);
		clcd_write(fd, "Tracker Fail");
		clcd_setcursor(fd, 0, 2);
		clcd_write(fd, "Because of ");
		clcd_setcursor(fd, 0, 3);
		clcd_write(fd, "Skip Detection");
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

	ros::Subscriber stat_tutorial_sub = nh.subscribe("ui/client", 1, statmsgCallback);
	ros::Subscriber ros_tutorial_sub = nh.subscribe("mpc/detectuser", 1, trackingErrormsgCallback);

	ros::spin();
	serialClose(fd);
	return 0;
}

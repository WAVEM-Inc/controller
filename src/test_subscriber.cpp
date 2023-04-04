#include "ros/ros.h"                          // ROS Default Header File
#include "../include/gpio_ctrl.h"

#include "sensor_msgs/LaserScan.h"
// message named 'ros_tutorial_msg' is received. As an input message,
// the 'MsgTutorial' message of the 'ros_tutorials_topic' package is received.
float ac_angular_bak = 0;
void msgCallback(const sensor_msgs::LaserScan& scan)
{
		// 	src/slam_gmapping/gmapping/src/slam_gmapping.cpp
	double* ranges_double = new double[scan.ranges.size()];
	int num_ranges = scan.ranges.size();
	
	sensor_msgs::LaserScan scan_msg;     
	for(unsigned int i=0; i < scan.ranges.size(); i++)
	{
		if(scan.ranges[i] < scan.range_min)
			ranges_double[i] = (double)scan.range_max;
		else
			ranges_double[i] = (double)scan.ranges[i];
	}
	for(int lp=0;lp < num_ranges;lp++)
	{
	printf("%f, ",ranges_double[lp]);
	}
	printf("\n\n\n");
	
	sleep(1);
}

int main(int argc, char **argv)                         // Node Main Function
{
	ros::init(argc, argv, "test_subscriber");            // Initializes Node Name
	ros::NodeHandle nh;                                   // Node handle declaration for communication with ROS system
	ros::Subscriber ros_tutorial_sub = nh.subscribe("scan", 100, msgCallback);

	ros::spin();

	return 0;
}

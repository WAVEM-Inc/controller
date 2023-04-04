#include "ros/ros.h"                          // ROS Default Header File
#include "ros_tutorials_topic/robot.h"  // MsgTutorial Message File Header. The header file is automatically created when building the package.


void msgCallback(const ros_tutorials_topic::robot::ConstPtr& msg){
ROS_INFO("%f",msg->data);

}
int main(int argc, char **argv)                         // Node Main Function
{
	ros::init(argc, argv, "topic_subscriber");            // Initializes Node Name
	ros::NodeHandle nh;   
	ros::Subscriber ros_tutorial_sub = nh.subscribe("robot", 100, msgCallback);

	ros::spin();

	return 0;
}

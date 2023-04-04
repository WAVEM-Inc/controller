#include "ros/ros.h"                            // ROS Default Header File
#include "ros_tutorials_topic/MsgTutorial.h"    // MsgTutorial Message File Header. The header file is automatically created when building the package.
#include "ros_tutorials_topic/robot.h"

int main(int argc, char **argv)                 // Node Main Function
{
  ros::init(argc, argv, "topic_publisher");     // Initializes Node Name
  ros::NodeHandle nh;       
	ros::NodeHandle n;  // Node handle declaration for communication with ROS system
  ros::Publisher robot_pose_pub =n.advertise<ros_tutorials_topic::robot>("robot",100);
  ros::Publisher ros_tutorial_pub = nh.advertise<ros_tutorials_topic::MsgTutorial>("ros_tutorial_msg", 100);

  // Set the loop period. '10' refers to 10 Hz and the main loop repeats at 0.1 second intervals
  ros::Rate loop_rate(10);
  ros_tutorials_topic::robot rp_msg;
  ros_tutorials_topic::MsgTutorial msg;     // Declares message 'msg' in 'MsgTutorial' message file format
  int count = 0;                            // Variable to be used in message

  while (ros::ok())
  {
    msg.stamp = ros::Time::now();           // Save current time in the stamp of 'msg'
    msg.data  = count;                      // Save the the 'count' value in the data of 'msg'
	rp_msg.data=M_PI;
    ROS_INFO("send msg = %d", msg.stamp.sec);   // Prints the 'stamp.sec' message
    ROS_INFO("send msg = %d", msg.stamp.nsec);  // Prints the 'stamp.nsec' message
    ROS_INFO("send msg = %d", msg.data);        // Prints the 'data' message
	robot_pose_pub.publish(rp_msg);
    ros_tutorial_pub.publish(msg);          // Publishes 'msg' message
    ROS_INFO("send pose msg = %f",rp_msg.data);
	
    loop_rate.sleep();                      // Goes to sleep according to the loop rate defined above.

    ++count;                                // Increase count variable by one
  }

  return 0;
}

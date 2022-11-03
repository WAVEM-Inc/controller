
//#include "common/common.hpp"
//
#include "motor_subscriber/cl_motor_manager.hpp"

int main(int argc, char **argv)                         // Node Main Function
{
	ros::init(argc, argv, "cdrmotor_subscriber");
	cl_motor_manager motor_manager;
	motor_manager.test_read();

	return 0;
}

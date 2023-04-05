#include "wm_motion_controller/wm_motion_controller.hpp"
/**
 * @brief Construct a new Wm Motion Controller:: Wm Motion Controller object
 * 
 */
WmMotionController::WmMotionController()
:Node("WmMotionController"){

}

/**
 * @brief 
 * 
 * @return int 
 */
int WmMotionController::fn_can_motor_init(){

}
/**
 * @brief The main function of the WmMotionController node.
 * @param argc int paramter , Number of factors delivered at the start of the program
 * @param argv char**, The factors you gave me at the start of the program
 * @return int Program normal operation
 */
int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<WmMotionController>();
    rclcpp::spin(node);	
	rclcpp::shutdown();
	return 0;
}
#include "wm_motion_controller/wm_motion_controller.hpp"
#include "can/can_manager.hpp"

/**
 * @brief The main function of the WmMotionController node.
 * @param argc int paramter , Number of factors delivered at the start of the program
 * @param argv char**, The factors you gave me at the start of the program
 * @return int Program normal operation
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.06
 */
int main(int argc, char** argv){
    rclcpp::init(argc, argv);
	std::cout<< R"(=======================================================================================================================
███    ███  ██████  ████████ ██  ██████  ███    ██          ██████  ██████  ███    ██ ████████ ██████   ██████  ██     
████  ████ ██    ██    ██    ██ ██    ██ ████   ██         ██      ██    ██ ████   ██    ██    ██   ██ ██    ██ ██     
██ ████ ██ ██    ██    ██    ██ ██    ██ ██ ██  ██         ██      ██    ██ ██ ██  ██    ██    ██████  ██    ██ ██     
██  ██  ██ ██    ██    ██    ██ ██    ██ ██  ██ ██         ██      ██    ██ ██  ██ ██    ██    ██   ██ ██    ██ ██     
██      ██  ██████     ██    ██  ██████  ██   ████ ███████  ██████  ██████  ██   ████    ██    ██   ██  ██████  ███████
=======================================================================================================================)"<<std::endl;

	std::cout<<"main start"<<std::endl;
	std::shared_ptr<ConcreteMotionMediator> mediator = std::make_shared<ConcreteMotionMediator>();
	
	std::shared_ptr<CanMGR> can_mgr =  std::make_shared<CanMGR>(mediator);
	mediator->fn_set_can_mgr(can_mgr);
    auto node = std::make_shared<WmMotionController>(mediator,can_mgr);
	mediator->fn_set_wm_motion_controller(node);
    rclcpp::spin(node);	
	rclcpp::shutdown();

	return 0;
}
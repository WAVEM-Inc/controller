#include "wm_motion_controller/wm_motion_controller.hpp"

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
    std::cout<<
             R"(=======================================================================================================================
███    ███  ██████  ████████ ██  ██████  ███    ██          ██████  ██████  ███    ██ ████████ ██████   ██████  ██
████  ████ ██    ██    ██    ██ ██    ██ ████   ██         ██      ██    ██ ████   ██    ██    ██   ██ ██    ██ ██
██ ████ ██ ██    ██    ██    ██ ██    ██ ██ ██  ██         ██      ██    ██ ██ ██  ██    ██    ██████  ██    ██ ██
██  ██  ██ ██    ██    ██    ██ ██    ██ ██  ██ ██         ██      ██    ██ ██  ██ ██    ██    ██   ██ ██    ██ ██
██      ██  ██████     ██    ██  ██████  ██   ████ ███████  ██████  ██████  ██   ████    ██    ██   ██  ██████  ███████
=======================================================================================================================)"<<std::endl;

    std::cout<<"main start"<<std::endl;
    //std::shared_ptr<ConcreteMotionMediator> mediator = std::make_shared<ConcreteMotionMediator>();
    //std::shared_ptr<Manager> manager = std::make_shared<Manager>();

    rclcpp::spin(std::make_shared<WmMotionController>());
#if DEBUG_MODE==1
    std::cout<<"[main] : "<<__LINE__<<std::endl;
#endif
    //manager->fn_run();
    return 0;
}
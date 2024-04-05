//
// Created by nuc-bt on 24. 4. 5.
//
#include "can/can_manager.hpp"
int main(int argc,char** argv){
    rclcpp::init(argc,argv);
    std::shared_ptr<CanMGR> manager = std::make_shared<CanMGR>();
    std::thread thread_run(&CanMGR::fn_can_run,manager);
    rclcpp::spin(manager);
    thread_run.join();
    return 0;
}
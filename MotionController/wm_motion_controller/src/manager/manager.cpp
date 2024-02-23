#include"manager/manager.hpp"

Manager::Manager(){

}
Manager::~Manager(){

}

void Manager::fn_run(){
    shared_ptr<Manager> manager = std::shared_ptr<Manager>(this);
    can_manager_ = std::make_shared<CanMGR>(manager);
	std::thread thread_run(&CanMGR::fn_can_run,can_manager_);
	thread_run.detach();
    std::cout<<"test"<<std::endl;
    rclcpp::spin(std::make_shared<WmMotionController>(manager));	
    rclcpp::shutdown();
}

void Manager::fn_map_up(std::string key, MANAGER::SETUP value){
    auto itr = map_setup_.find(key);
    if(itr==map_setup_.end()){
        map_setup_.insert({key,value});
    }
}

void Manager::fn_motion_send_data(int test){
    can_manager_->fn_test(test);
}
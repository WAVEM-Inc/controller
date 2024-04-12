#include"manager/manager.hpp"

Manager::Manager(){

}
Manager::~Manager(){

}

void Manager::fn_run(){
#if DEBUG_MODE==1
    std::cout<<"[Manager]-[fn_run] : "<<__LINE__<<std::endl;
#endif
    //shared_ptr<Manager> manager = std::shared_ptr<Manager>(this);

/*
	//can_manager_->fn_can_run();*/

/*    std::shared_ptr<CanMGR> can_manager_=std::make_shared<CanMGR>();
    std::thread thread_run(&CanMGR::fn_can_run,can_manager_);
    thread_run.detach();*/

    wm_motion_controller_ = std::make_shared<WmMotionController>();
    //std::thread thread_run(&CanMGR::fn_can_run,can_manager_);
    auto ros_thread = std::thread([](auto node){rclcpp::spin(node);},wm_motion_controller_);

/*    wm_motion_controller_ = std::make_shared<WmMotionController>();
    //rclcpp::spin(wm_motion_controller_);
    rclcpp::executors::MultiThreadedExecutor excutor;
    excutor.add_node(wm_motion_controller_);

    //excutor.add_node(std::make_shared<CanMGR>());
    excutor.spin();*/

    ros_thread.join();

    //
    std::cout<<"test"<<"!"<<std::endl;
    //rclcpp::spin(temp);
/*    while(1){

    }*/

    // 결과 출력
    //thread_run.join();
}

void Manager::fn_map_up(std::string key, MANAGER::SETUP value){
    auto itr = map_setup_.find(key);
    if(itr==map_setup_.end()){
        map_setup_.insert({key,value});
    }
}




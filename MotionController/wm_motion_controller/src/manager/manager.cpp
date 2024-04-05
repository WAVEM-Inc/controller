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
    std::shared_ptr<CanMGR> can_manager_=std::make_shared<CanMGR>();
    wm_motion_controller_ = std::make_shared<WmMotionController>();
    //std::thread thread_run(&CanMGR::fn_can_run,can_manager_);
    auto can_thread = std::thread([](auto node){rclcpp::spin(node);}, can_manager_);
    auto ros_thread = std::thread([](auto node){rclcpp::spin(node);},wm_motion_controller_);
    can_manager_->fn_can_run();
/*    wm_motion_controller_ = std::make_shared<WmMotionController>();
    //rclcpp::spin(wm_motion_controller_);
    rclcpp::executors::MultiThreadedExecutor excutor;
    excutor.add_node(wm_motion_controller_);

    //excutor.add_node(std::make_shared<CanMGR>());
    excutor.spin();*/

    can_thread.join();
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

void Manager::fn_can_send_led_and_horn(const can_msgs::msg::ControlHardware::SharedPtr can_chw){
  //  can_manager_->fn_send_control_hardware(can_chw->horn,can_chw->head_light,can_chw->right_light,can_chw->left_light);
}

void Manager::fn_can_send_steering(float angular){
    std::string key = "CanMGR";
    if(map_setup_.find(key)!=map_setup_.end()){
       // can_manager_->fn_send_control_steering(angular);
    }
}
void Manager::fn_can_send_vel(float linear){
//    can_manager_->fn_send_control_vel(linear);
}
void Manager::fn_can_send_break(UGV::BREAK break_status){
 //   can_manager_->static_break(break_status);
}

void Manager::can_send_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time){
    std::string key = "WmMotionController";
    if(map_setup_.find(key)!=map_setup_.end()){
        //wm_motion_controller_->fn_recv_rpm(rpm,cur_time);
    }
}


#include"mediator/concrete_motion_mediator.hpp"
/**
 * @brief WmMotionController Handed Over to Arbitrator
 * @author changunAn(changun516@wavem.net)
 * @param wm_motion_controller 
 */
void ConcreteMotionMediator::fn_set_wm_motion_controller(std::shared_ptr<WmMotionController> wm_motion_controller){
    m_wm_motion_controller=wm_motion_controller;
}

/**
 * @brief CanMGR Handed Over to Arbitrator
 * @author changunAn(changun516@wavem.net)
 * @param can_mgr 
 */
void ConcreteMotionMediator::fn_set_can_mgr(std::shared_ptr<CanMGR> can_mgr){
    m_can_mgr = can_mgr;
}
/**
 * @brief Data exchange through arbitrator, lock to prevent other data from entering
 * @author changunAn(changun516@wavem.net)
 * @param value 
 * @param sender 
 */
void ConcreteMotionMediator::fn_send_value(const int& value,std::shared_ptr<IMotionColleague> sender){
    //std::cout<<"test1"<<std::endl;
   if(sender == m_can_mgr){
        std::cout<<"mediator.cpp"<<__LINE__<<std::endl;
        if(m_wm_motion_controller.use_count()>0){
            std::lock_guard<std::mutex> lock(m_mutex); // 뮤텍스 락
            //std::cout<<m_wm_motion_controller.use_count()<<'\n';
            m_wm_motion_controller->fn_recv_value(value);
        }
   }
   else if(sender == m_wm_motion_controller){
        //std::cout<<"test3"<<std::endl;
        std::cout<<"mediator.cpp"<<__LINE__<<std::endl;
        if(m_can_mgr.use_count()>0){
            std::lock_guard<std::mutex> lock(m_mutex); // 뮤텍스 락
            std::cout<<m_can_mgr.use_count()<<'\n';
            m_can_mgr->fn_recv_value(value);
        }
   }
}

/**
 * @brief 
 * 
 * @param rpm 
 * @param cur_time 
 * @param sender 
 */
void ConcreteMotionMediator::fn_send_rpm(const float& rpm, const std::chrono::system_clock::time_point cur_time, std::shared_ptr<IMotionColleague> sender){
    std::cout<<"rpm_test"<<std::endl;
    if(sender == m_can_mgr){
        std::cout<<"rpm_test2"<<std::endl;
        std::lock_guard<std::mutex> lock(m_mutex); // 뮤텍스 락
        if(m_wm_motion_controller.use_count()>0&&m_can_mgr.use_count()>0){
            m_wm_motion_controller->fn_recv_rpm(rpm,cur_time);
        }
        else{
            std::cout<<m_wm_motion_controller.use_count()<<'\n';
        }
   }
   else if(sender == m_wm_motion_controller){
        std::cout<<"rpm_test3"<<std::endl;
        if(m_can_mgr.use_count()>0&& m_wm_motion_controller.use_count()>0){
            std::lock_guard<std::mutex> lock(m_mutex); // 뮤텍스 락
            m_can_mgr->fn_recv_rpm(rpm,cur_time);
        }
   }

}

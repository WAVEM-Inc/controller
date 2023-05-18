#ifndef MOTION_COLLEAGUE
#define MOTION_COLLEAGUE
#include "mediator/i_motion_mediator.hpp"
#include <memory>
#include <chrono>
class IMotionMediator;

/**
 * @brief Collegue interface for using mediator patterns
 * @author changunAn(changun516@wavem.net)
 */
class IMotionColleague{
    public : 
        IMotionColleague(std::shared_ptr<IMotionMediator> motion_mediator):m_i_motion_mediator(motion_mediator){};
        virtual void fn_recv_value(const int& value)=0;
        virtual void fn_send_value(const int& value)=0;
        virtual void fn_send_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time)=0;
        virtual void fn_recv_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time)=0;
    protected :
       std::shared_ptr<IMotionMediator> m_i_motion_mediator; 

};
#endif
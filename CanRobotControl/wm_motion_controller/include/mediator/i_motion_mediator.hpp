#ifndef I_MOTION_MEDIATOR
#define I_MOTION_MEDIATOR
#include "colleague/i_motion_colleague.hpp"
#include <memory>
#include <chrono>
class IMotionColleague;

/**
 * @brief Arbitrator interface for using arbitrator patterns
 * @author changunAn(changun516@wavem.net)
 * @details 
 */
class IMotionMediator{
    public :
        virtual void fn_send_value(const int& value, std::shared_ptr<IMotionColleague> sender)=0;
        virtual void fn_send_rpm(const float& rpm, const std::chrono::system_clock::time_point cur_time ,std::shared_ptr<IMotionColleague> sender)=0;
};
#endif
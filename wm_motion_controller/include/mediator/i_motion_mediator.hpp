#ifndef I_MOTION_MEDIATOR
#define I_MOTION_MEDIATOR
#include "colleague/i_motion_colleague.hpp"
#include <memory>
class IMotionColleague;
class IMotionMediator{
    public :
        virtual void fn_send_value(const int& value, std::shared_ptr<IMotionColleague> sender)=0;
};
#endif
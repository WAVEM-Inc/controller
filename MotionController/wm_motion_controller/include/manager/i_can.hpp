#ifndef MANAGER__I__CAN__HPP__
#define MANAGER__I__CAN__HPP__
#include <chrono> // time
class ICAN{
    public :

    virtual void can_send_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time)=0;
};

#endif 
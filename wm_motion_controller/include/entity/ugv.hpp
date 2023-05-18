#ifndef WM_MOTION_CONTROLLER__ENTITY__UGV_HPP_
#define WM_MOTION_CONTROLLER__ENTITY__UGV_HPP_
#include <iostream>
#include <chrono> // time
namespace ENTITY{
    class UGV{
        private :
            const float wheel_;
            const std::string ugv_id_;
            const float max_speed_;
            const int gear_ratio_;
            float cur_rpm_;
            std::chrono::system_clock::time_point cur_time_;
        public : 
            UGV();
            // set function
            void set_cur_rpm(const float& cur_rpm);
            void set_cur_time(const std::chrono::system_clock::time_point& cur_time);
            // get function 
            const int get_gear_ratio();
            const float get_wheel();
            const float get_cur_rpm();
            const std::chrono::system_clock::time_point get_cur_time();
    };
}

#endif
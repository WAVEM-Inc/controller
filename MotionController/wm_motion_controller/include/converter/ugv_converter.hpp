#ifndef WM_MOTION_CONTROLLER__CONVERTER__UGV_CONVERTER_HPP_
#define WM_MOTION_CONTROLLER__OONVERTER__UGV_CONVERTER_HPP_
#include "converter/df_ugv_converter.hpp"
#include "entity/ugv.hpp"
//
#include<memory>
#include<chrono>
namespace CONVERTER{
    /**
     * @brief 
     * @author changun516@wavem.net
     */
    class UGVConverter{
        private :
            const int rpm_standard_;
            std::unique_ptr<ENTITY::UGV> target_ugv_;
            float odometry_offset_;
            long long calculate_time_difference(const std::chrono::system_clock::time_point& startTime, const std::chrono::system_clock::time_point& endTime);
        public : 
            UGVConverter();
            float rpm_to_speed();
            float rpm_to_distance(ENTITY::UGV prev_ugv, ENTITY::UGV cur_ugv);
            void set_odometry_offset(float offset);


    };
}



#endif
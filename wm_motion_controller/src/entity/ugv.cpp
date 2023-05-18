#include"entity/ugv.hpp"
#include"entity/df_ugv.hpp"
ENTITY::UGV::UGV():
    wheel_(WHEEL),
    ugv_id_(UGV_ID),
    max_speed_(MAX_SPEED),
    gear_ratio_(GEAR_RATIO){
        //cur_rpm = 0;
}

/**
 * @brief 
 * 
 * @return const int 
 */
const int ENTITY::UGV::get_gear_ratio(){
    return gear_ratio_;
}

/**
 * @brief 
 * @return const float 
 */
const float ENTITY::UGV::get_wheel(){
    return wheel_;
}

/**
 * @brief set the current rpm
 * @param cur_rpm 
 */
void ENTITY::UGV::set_cur_rpm(const float& cur_rpm){
    cur_rpm_ = cur_rpm;
}

/**
 * @brief set the current time
 * @param cur_time 
 */
void ENTITY::UGV::set_cur_time(const std::chrono::system_clock::time_point& cur_time){
    cur_time_=cur_time;
}
const float ENTITY::UGV::get_cur_rpm(){
    return cur_rpm_;
}
const std::chrono::system_clock::time_point  ENTITY::UGV::get_cur_time(){
    return cur_time_;
}
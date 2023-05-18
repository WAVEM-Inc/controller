#include"converter/ugv_converter.hpp"
#include <cmath>
CONVERTER::UGVConverter::UGVConverter():
    rpm_standard_(RPM_STANDARD){
    target_ugv_ = std::make_unique<ENTITY::UGV>();
}

float CONVERTER::UGVConverter::rpm_to_speed(){

}


float CONVERTER::UGVConverter::rpm_to_distance(ENTITY::UGV prev_ugv, ENTITY::UGV cur_ugv){
    //(cur_ugv.get_wheel()*M_PI) * ()
}

// * @details ((wheel * PI) * (prev_rpm+cur_rpm)/2 * (cur_time-prev_time)/60)/gear_ratio
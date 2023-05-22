#include"converter/ugv_converter.hpp"
#include <cmath>
CONVERTER::UGVConverter::UGVConverter():
    rpm_standard_(RPM_STANDARD){
    target_ugv_ = std::make_unique<ENTITY::UGV>();
}

float CONVERTER::UGVConverter::rpm_to_speed(){

}


float CONVERTER::UGVConverter::rpm_to_distance(ENTITY::UGV prev_ugv, ENTITY::UGV cur_ugv){
    std::cout<<"rpm_to_distance : "<<prev_ugv.get_cur_rpm()<<' '<<cur_ugv.get_cur_rpm()<<'\n';
    //auto time_dif=calculate_time_difference(prev_ugv.get_cur_time(),cur_ugv.get_cur_time());
    float time_dif=0.2;
    std::cout<<cur_ugv.get_wheel()<<' '<<cur_ugv.get_wheel()*M_PI <<' '<<((RPM_STANDARD-prev_ugv.get_cur_rpm())+(RPM_STANDARD-cur_ugv.get_cur_rpm()))/2<< time_dif/60<<' '<<cur_ugv.get_gear_ratio()<<'\n';
    auto result = (cur_ugv.get_wheel()*M_PI) * ((RPM_STANDARD-prev_ugv.get_cur_rpm())+(RPM_STANDARD-cur_ugv.get_cur_rpm()))/2 * (time_dif/60) / cur_ugv.get_gear_ratio();
    std::cout<<"result "<< result<<'\n';
    return static_cast<float>(result);
}

// * @details ((wheel * PI) * (prev_rpm+cur_rpm)/2 * (cur_time-prev_time)/60)/gear_ratio



long long CONVERTER::UGVConverter::calculate_time_difference(const std::chrono::system_clock::time_point& startTime, const std::chrono::system_clock::time_point& endTime) {
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
	return duration.count();
}
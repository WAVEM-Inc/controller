//
// Created by nuc-bt on 24. 4. 30.
//

#ifndef CAN_MANAGER_KEC_CODE_DEFIE_HPP
#define CAN_MANAGER_KEC_CODE_DEFIE_HPP
namespace KEC{
    enum class ErrorCode{
        kCan = 100, // can 통신 에러
        kMotor = 150, // 모터 고장
        kOverload = 160, // 과부하
        kOvercurrent = 161, // 과전류
        kPowerLowVoltage = 501, // 전원 공급 장치 저전압 오류
        kPowerOverVoltge = 502, // 전원 공급 장치 과전압 오류.
        kBms = 460
    };
}
#endif //CAN_MANAGER_KEC_CODE_DEFIE_HPP

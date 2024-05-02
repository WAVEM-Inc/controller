//
// Created by nuc-bt on 24. 4. 30.
//

#ifndef CAN_MANAGER_KEC_CODE_DEFIE_HPP
#define CAN_MANAGER_KEC_CODE_DEFIE_HPP
namespace KEC{
    enum class BMS_Sys_Sts{
        kCan = 100, // can 통신 에러
        kMotor = 150, // 모터 고장
        kOverload = 160, // 과부하
        kOvercurrent = 161, // 과전류
        kPowerLowVoltage = 501, // 전원 공급 장치 저전압 오류
        kPowerOverVoltge = 502, // 전원 공급 장치 과전압 오류.
        kBms = 460
    };
    enum class DBS_Fault_Code : unsigned long long {
        kOverLoadProtection = 0b000000000000000000000001, // 1Bit: 과부하 보호
        kOverTemperatureProtection = 0b000000000000000000000011, // 2Bit: 과온 보호
        kOverCurrentProtection = 0b000000000000000000000111, // 3Bit: 과전류 보호
        kPowerSupplyUndervoltageFault = 0b000000000000000000001111, // 4Bit: 전원 부족 전압 고장
        kPowerOvervoltageFailure = 0b000000000000000000011111, // 5Bit: 전원 과전압 고장
        kInsufficientPressure = 0b000000000000000000111111, // 6Bit: 압력 부족
        kMotorFailure = 0b000000000000000001111111, // 7Bit: 모터 고장
        kCommunicationFailure = 0b000000000000000011111111, // 8Bit: 통신 장애
        kCurrentSamplingFailure = 0b000000000000000111111111, // 9Bit: 전류 샘플링 고장
        kDriveFailure = 0b000000000000001111111111, // 10Bit: 구동 고장
        kMagneticCompilationFailure = 0b000000000000011111111111, // 11Bit: 자석의 고장
        kPressureSensorFailure = 0b000000000000111111111111, // 12Bit: 압력 센서 고장
        kPedalPositionSensorFailure = 0b000000000001111111111111, // 13Bit: 페달 위치 센서 고장
        kOtherFailures = 0b000000000011111111111111 // 14Bit: 기타 고장
    };
}

#endif //CAN_MANAGER_KEC_CODE_DEFIE_HPP

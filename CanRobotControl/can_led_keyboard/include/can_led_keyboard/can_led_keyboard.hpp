#ifndef LED_KEYBOARD
#define LED_KEYBOARD

#include <cstdio>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "rclcpp/rclcpp.hpp"
#include "can_msgs/msg/control_hardware.hpp"
#include "can_led_keyboard/df_can_led_keyboard.hpp"
using namespace std::chrono_literals;

class KeyboardPublisher : public rclcpp::Node
{
public:
  KeyboardPublisher();
private:
  void fn_timer_callback();
  bool fn_kbhit();
  void fn_start();
  void fn_print_key();
  const std::string tp_control_hardware;
  rclcpp::Publisher<can_msgs::msg::ControlHardware>::SharedPtr m_publisher;
  rclcpp::TimerBase::SharedPtr m_timer;
};

#endif
// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from can_msgs:msg/ControlHardware.idl
// generated code does not contain a copyright notice

#ifndef CAN_MSGS__MSG__DETAIL__CONTROL_HARDWARE__BUILDER_HPP_
#define CAN_MSGS__MSG__DETAIL__CONTROL_HARDWARE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "can_msgs/msg/detail/control_hardware__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace can_msgs
{

namespace msg
{

namespace builder
{

class Init_ControlHardware_right_light
{
public:
  explicit Init_ControlHardware_right_light(::can_msgs::msg::ControlHardware & msg)
  : msg_(msg)
  {}
  ::can_msgs::msg::ControlHardware right_light(::can_msgs::msg::ControlHardware::_right_light_type arg)
  {
    msg_.right_light = std::move(arg);
    return std::move(msg_);
  }

private:
  ::can_msgs::msg::ControlHardware msg_;
};

class Init_ControlHardware_left_light
{
public:
  explicit Init_ControlHardware_left_light(::can_msgs::msg::ControlHardware & msg)
  : msg_(msg)
  {}
  Init_ControlHardware_right_light left_light(::can_msgs::msg::ControlHardware::_left_light_type arg)
  {
    msg_.left_light = std::move(arg);
    return Init_ControlHardware_right_light(msg_);
  }

private:
  ::can_msgs::msg::ControlHardware msg_;
};

class Init_ControlHardware_head_light
{
public:
  explicit Init_ControlHardware_head_light(::can_msgs::msg::ControlHardware & msg)
  : msg_(msg)
  {}
  Init_ControlHardware_left_light head_light(::can_msgs::msg::ControlHardware::_head_light_type arg)
  {
    msg_.head_light = std::move(arg);
    return Init_ControlHardware_left_light(msg_);
  }

private:
  ::can_msgs::msg::ControlHardware msg_;
};

class Init_ControlHardware_horn
{
public:
  Init_ControlHardware_horn()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ControlHardware_head_light horn(::can_msgs::msg::ControlHardware::_horn_type arg)
  {
    msg_.horn = std::move(arg);
    return Init_ControlHardware_head_light(msg_);
  }

private:
  ::can_msgs::msg::ControlHardware msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::can_msgs::msg::ControlHardware>()
{
  return can_msgs::msg::builder::Init_ControlHardware_horn();
}

}  // namespace can_msgs

#endif  // CAN_MSGS__MSG__DETAIL__CONTROL_HARDWARE__BUILDER_HPP_

// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from can_msgs:msg/Mode.idl
// generated code does not contain a copyright notice

#ifndef CAN_MSGS__MSG__DETAIL__MODE__BUILDER_HPP_
#define CAN_MSGS__MSG__DETAIL__MODE__BUILDER_HPP_

#include "can_msgs/msg/detail/mode__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace can_msgs
{

namespace msg
{

namespace builder
{

class Init_Mode_slam_mode
{
public:
  Init_Mode_slam_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::can_msgs::msg::Mode slam_mode(::can_msgs::msg::Mode::_slam_mode_type arg)
  {
    msg_.slam_mode = std::move(arg);
    return std::move(msg_);
  }

private:
  ::can_msgs::msg::Mode msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::can_msgs::msg::Mode>()
{
  return can_msgs::msg::builder::Init_Mode_slam_mode();
}

}  // namespace can_msgs

#endif  // CAN_MSGS__MSG__DETAIL__MODE__BUILDER_HPP_

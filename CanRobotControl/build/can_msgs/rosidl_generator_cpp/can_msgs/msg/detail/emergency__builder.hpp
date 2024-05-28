// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from can_msgs:msg/Emergency.idl
// generated code does not contain a copyright notice

#ifndef CAN_MSGS__MSG__DETAIL__EMERGENCY__BUILDER_HPP_
#define CAN_MSGS__MSG__DETAIL__EMERGENCY__BUILDER_HPP_

#include "can_msgs/msg/detail/emergency__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace can_msgs
{

namespace msg
{

namespace builder
{

class Init_Emergency_stop
{
public:
  explicit Init_Emergency_stop(::can_msgs::msg::Emergency & msg)
  : msg_(msg)
  {}
  ::can_msgs::msg::Emergency stop(::can_msgs::msg::Emergency::_stop_type arg)
  {
    msg_.stop = std::move(arg);
    return std::move(msg_);
  }

private:
  ::can_msgs::msg::Emergency msg_;
};

class Init_Emergency_header
{
public:
  Init_Emergency_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Emergency_stop header(::can_msgs::msg::Emergency::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Emergency_stop(msg_);
  }

private:
  ::can_msgs::msg::Emergency msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::can_msgs::msg::Emergency>()
{
  return can_msgs::msg::builder::Init_Emergency_header();
}

}  // namespace can_msgs

#endif  // CAN_MSGS__MSG__DETAIL__EMERGENCY__BUILDER_HPP_

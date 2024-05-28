// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from can_msgs:msg/Emergency.idl
// generated code does not contain a copyright notice

#ifndef CAN_MSGS__MSG__DETAIL__EMERGENCY__TRAITS_HPP_
#define CAN_MSGS__MSG__DETAIL__EMERGENCY__TRAITS_HPP_

#include "can_msgs/msg/detail/emergency__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<can_msgs::msg::Emergency>()
{
  return "can_msgs::msg::Emergency";
}

template<>
inline const char * name<can_msgs::msg::Emergency>()
{
  return "can_msgs/msg/Emergency";
}

template<>
struct has_fixed_size<can_msgs::msg::Emergency>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<can_msgs::msg::Emergency>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<can_msgs::msg::Emergency>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CAN_MSGS__MSG__DETAIL__EMERGENCY__TRAITS_HPP_

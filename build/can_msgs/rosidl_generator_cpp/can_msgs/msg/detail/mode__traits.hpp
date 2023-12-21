// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from can_msgs:msg/Mode.idl
// generated code does not contain a copyright notice

#ifndef CAN_MSGS__MSG__DETAIL__MODE__TRAITS_HPP_
#define CAN_MSGS__MSG__DETAIL__MODE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "can_msgs/msg/detail/mode__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace can_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Mode & msg,
  std::ostream & out)
{
  out << "{";
  // member: slam_mode
  {
    out << "slam_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.slam_mode, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Mode & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: slam_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "slam_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.slam_mode, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Mode & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace can_msgs

namespace rosidl_generator_traits
{

[[deprecated("use can_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const can_msgs::msg::Mode & msg,
  std::ostream & out, size_t indentation = 0)
{
  can_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use can_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const can_msgs::msg::Mode & msg)
{
  return can_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<can_msgs::msg::Mode>()
{
  return "can_msgs::msg::Mode";
}

template<>
inline const char * name<can_msgs::msg::Mode>()
{
  return "can_msgs/msg/Mode";
}

template<>
struct has_fixed_size<can_msgs::msg::Mode>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<can_msgs::msg::Mode>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<can_msgs::msg::Mode>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CAN_MSGS__MSG__DETAIL__MODE__TRAITS_HPP_

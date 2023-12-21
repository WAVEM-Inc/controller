// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from can_msgs:msg/ControlHardware.idl
// generated code does not contain a copyright notice

#ifndef CAN_MSGS__MSG__DETAIL__CONTROL_HARDWARE__TRAITS_HPP_
#define CAN_MSGS__MSG__DETAIL__CONTROL_HARDWARE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "can_msgs/msg/detail/control_hardware__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace can_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const ControlHardware & msg,
  std::ostream & out)
{
  out << "{";
  // member: horn
  {
    out << "horn: ";
    rosidl_generator_traits::value_to_yaml(msg.horn, out);
    out << ", ";
  }

  // member: head_light
  {
    out << "head_light: ";
    rosidl_generator_traits::value_to_yaml(msg.head_light, out);
    out << ", ";
  }

  // member: left_light
  {
    out << "left_light: ";
    rosidl_generator_traits::value_to_yaml(msg.left_light, out);
    out << ", ";
  }

  // member: right_light
  {
    out << "right_light: ";
    rosidl_generator_traits::value_to_yaml(msg.right_light, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ControlHardware & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: horn
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "horn: ";
    rosidl_generator_traits::value_to_yaml(msg.horn, out);
    out << "\n";
  }

  // member: head_light
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "head_light: ";
    rosidl_generator_traits::value_to_yaml(msg.head_light, out);
    out << "\n";
  }

  // member: left_light
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_light: ";
    rosidl_generator_traits::value_to_yaml(msg.left_light, out);
    out << "\n";
  }

  // member: right_light
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_light: ";
    rosidl_generator_traits::value_to_yaml(msg.right_light, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ControlHardware & msg, bool use_flow_style = false)
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
  const can_msgs::msg::ControlHardware & msg,
  std::ostream & out, size_t indentation = 0)
{
  can_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use can_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const can_msgs::msg::ControlHardware & msg)
{
  return can_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<can_msgs::msg::ControlHardware>()
{
  return "can_msgs::msg::ControlHardware";
}

template<>
inline const char * name<can_msgs::msg::ControlHardware>()
{
  return "can_msgs/msg/ControlHardware";
}

template<>
struct has_fixed_size<can_msgs::msg::ControlHardware>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<can_msgs::msg::ControlHardware>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<can_msgs::msg::ControlHardware>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CAN_MSGS__MSG__DETAIL__CONTROL_HARDWARE__TRAITS_HPP_

// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from can_msgs:msg/ControlHardware.idl
// generated code does not contain a copyright notice
#include "can_msgs/msg/detail/control_hardware__rosidl_typesupport_fastrtps_cpp.hpp"
#include "can_msgs/msg/detail/control_hardware__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace can_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_can_msgs
cdr_serialize(
  const can_msgs::msg::ControlHardware & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: horn
  cdr << (ros_message.horn ? true : false);
  // Member: head_light
  cdr << (ros_message.head_light ? true : false);
  // Member: left_light
  cdr << (ros_message.left_light ? true : false);
  // Member: right_light
  cdr << (ros_message.right_light ? true : false);
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_can_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  can_msgs::msg::ControlHardware & ros_message)
{
  // Member: horn
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.horn = tmp ? true : false;
  }

  // Member: head_light
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.head_light = tmp ? true : false;
  }

  // Member: left_light
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.left_light = tmp ? true : false;
  }

  // Member: right_light
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.right_light = tmp ? true : false;
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_can_msgs
get_serialized_size(
  const can_msgs::msg::ControlHardware & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: horn
  {
    size_t item_size = sizeof(ros_message.horn);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: head_light
  {
    size_t item_size = sizeof(ros_message.head_light);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: left_light
  {
    size_t item_size = sizeof(ros_message.left_light);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: right_light
  {
    size_t item_size = sizeof(ros_message.right_light);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_can_msgs
max_serialized_size_ControlHardware(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: horn
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: head_light
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: left_light
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: right_light
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static bool _ControlHardware__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const can_msgs::msg::ControlHardware *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _ControlHardware__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<can_msgs::msg::ControlHardware *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _ControlHardware__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const can_msgs::msg::ControlHardware *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _ControlHardware__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_ControlHardware(full_bounded, 0);
}

static message_type_support_callbacks_t _ControlHardware__callbacks = {
  "can_msgs::msg",
  "ControlHardware",
  _ControlHardware__cdr_serialize,
  _ControlHardware__cdr_deserialize,
  _ControlHardware__get_serialized_size,
  _ControlHardware__max_serialized_size
};

static rosidl_message_type_support_t _ControlHardware__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_ControlHardware__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace can_msgs

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_can_msgs
const rosidl_message_type_support_t *
get_message_type_support_handle<can_msgs::msg::ControlHardware>()
{
  return &can_msgs::msg::typesupport_fastrtps_cpp::_ControlHardware__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, can_msgs, msg, ControlHardware)() {
  return &can_msgs::msg::typesupport_fastrtps_cpp::_ControlHardware__handle;
}

#ifdef __cplusplus
}
#endif

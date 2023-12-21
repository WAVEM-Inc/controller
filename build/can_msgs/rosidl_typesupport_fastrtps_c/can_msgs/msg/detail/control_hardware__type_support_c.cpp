// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from can_msgs:msg/ControlHardware.idl
// generated code does not contain a copyright notice
#include "can_msgs/msg/detail/control_hardware__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "can_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "can_msgs/msg/detail/control_hardware__struct.h"
#include "can_msgs/msg/detail/control_hardware__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _ControlHardware__ros_msg_type = can_msgs__msg__ControlHardware;

static bool _ControlHardware__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _ControlHardware__ros_msg_type * ros_message = static_cast<const _ControlHardware__ros_msg_type *>(untyped_ros_message);
  // Field name: horn
  {
    cdr << (ros_message->horn ? true : false);
  }

  // Field name: head_light
  {
    cdr << (ros_message->head_light ? true : false);
  }

  // Field name: left_light
  {
    cdr << (ros_message->left_light ? true : false);
  }

  // Field name: right_light
  {
    cdr << (ros_message->right_light ? true : false);
  }

  return true;
}

static bool _ControlHardware__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _ControlHardware__ros_msg_type * ros_message = static_cast<_ControlHardware__ros_msg_type *>(untyped_ros_message);
  // Field name: horn
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->horn = tmp ? true : false;
  }

  // Field name: head_light
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->head_light = tmp ? true : false;
  }

  // Field name: left_light
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->left_light = tmp ? true : false;
  }

  // Field name: right_light
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->right_light = tmp ? true : false;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_can_msgs
size_t get_serialized_size_can_msgs__msg__ControlHardware(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ControlHardware__ros_msg_type * ros_message = static_cast<const _ControlHardware__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name horn
  {
    size_t item_size = sizeof(ros_message->horn);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name head_light
  {
    size_t item_size = sizeof(ros_message->head_light);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name left_light
  {
    size_t item_size = sizeof(ros_message->left_light);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name right_light
  {
    size_t item_size = sizeof(ros_message->right_light);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _ControlHardware__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_can_msgs__msg__ControlHardware(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_can_msgs
size_t max_serialized_size_can_msgs__msg__ControlHardware(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: horn
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: head_light
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: left_light
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: right_light
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = can_msgs__msg__ControlHardware;
    is_plain =
      (
      offsetof(DataType, right_light) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _ControlHardware__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_can_msgs__msg__ControlHardware(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_ControlHardware = {
  "can_msgs::msg",
  "ControlHardware",
  _ControlHardware__cdr_serialize,
  _ControlHardware__cdr_deserialize,
  _ControlHardware__get_serialized_size,
  _ControlHardware__max_serialized_size
};

static rosidl_message_type_support_t _ControlHardware__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ControlHardware,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, can_msgs, msg, ControlHardware)() {
  return &_ControlHardware__type_support;
}

#if defined(__cplusplus)
}
#endif

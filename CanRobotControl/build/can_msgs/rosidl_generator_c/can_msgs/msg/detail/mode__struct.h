// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from can_msgs:msg/Mode.idl
// generated code does not contain a copyright notice

#ifndef CAN_MSGS__MSG__DETAIL__MODE__STRUCT_H_
#define CAN_MSGS__MSG__DETAIL__MODE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Mode in the package can_msgs.
typedef struct can_msgs__msg__Mode
{
  bool slam_mode;
} can_msgs__msg__Mode;

// Struct for a sequence of can_msgs__msg__Mode.
typedef struct can_msgs__msg__Mode__Sequence
{
  can_msgs__msg__Mode * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} can_msgs__msg__Mode__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CAN_MSGS__MSG__DETAIL__MODE__STRUCT_H_

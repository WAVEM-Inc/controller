// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from can_msgs:msg/Emergency.idl
// generated code does not contain a copyright notice

#ifndef CAN_MSGS__MSG__DETAIL__EMERGENCY__STRUCT_H_
#define CAN_MSGS__MSG__DETAIL__EMERGENCY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

// Struct defined in msg/Emergency in the package can_msgs.
typedef struct can_msgs__msg__Emergency
{
  std_msgs__msg__Header header;
  bool stop;
} can_msgs__msg__Emergency;

// Struct for a sequence of can_msgs__msg__Emergency.
typedef struct can_msgs__msg__Emergency__Sequence
{
  can_msgs__msg__Emergency * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} can_msgs__msg__Emergency__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CAN_MSGS__MSG__DETAIL__EMERGENCY__STRUCT_H_

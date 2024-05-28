// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from can_msgs:msg/ControlHardware.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "can_msgs/msg/detail/control_hardware__rosidl_typesupport_introspection_c.h"
#include "can_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "can_msgs/msg/detail/control_hardware__functions.h"
#include "can_msgs/msg/detail/control_hardware__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void ControlHardware__rosidl_typesupport_introspection_c__ControlHardware_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  can_msgs__msg__ControlHardware__init(message_memory);
}

void ControlHardware__rosidl_typesupport_introspection_c__ControlHardware_fini_function(void * message_memory)
{
  can_msgs__msg__ControlHardware__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember ControlHardware__rosidl_typesupport_introspection_c__ControlHardware_message_member_array[4] = {
  {
    "horn",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(can_msgs__msg__ControlHardware, horn),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "head_light",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(can_msgs__msg__ControlHardware, head_light),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "left_light",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(can_msgs__msg__ControlHardware, left_light),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "right_light",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(can_msgs__msg__ControlHardware, right_light),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers ControlHardware__rosidl_typesupport_introspection_c__ControlHardware_message_members = {
  "can_msgs__msg",  // message namespace
  "ControlHardware",  // message name
  4,  // number of fields
  sizeof(can_msgs__msg__ControlHardware),
  ControlHardware__rosidl_typesupport_introspection_c__ControlHardware_message_member_array,  // message members
  ControlHardware__rosidl_typesupport_introspection_c__ControlHardware_init_function,  // function to initialize message memory (memory has to be allocated)
  ControlHardware__rosidl_typesupport_introspection_c__ControlHardware_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t ControlHardware__rosidl_typesupport_introspection_c__ControlHardware_message_type_support_handle = {
  0,
  &ControlHardware__rosidl_typesupport_introspection_c__ControlHardware_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_can_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, can_msgs, msg, ControlHardware)() {
  if (!ControlHardware__rosidl_typesupport_introspection_c__ControlHardware_message_type_support_handle.typesupport_identifier) {
    ControlHardware__rosidl_typesupport_introspection_c__ControlHardware_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &ControlHardware__rosidl_typesupport_introspection_c__ControlHardware_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from can_msgs:msg/ControlHardware.idl
// generated code does not contain a copyright notice

#ifndef CAN_MSGS__MSG__DETAIL__CONTROL_HARDWARE__STRUCT_HPP_
#define CAN_MSGS__MSG__DETAIL__CONTROL_HARDWARE__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__can_msgs__msg__ControlHardware __attribute__((deprecated))
#else
# define DEPRECATED__can_msgs__msg__ControlHardware __declspec(deprecated)
#endif

namespace can_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ControlHardware_
{
  using Type = ControlHardware_<ContainerAllocator>;

  explicit ControlHardware_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->horn = false;
      this->head_light = false;
      this->left_light = false;
      this->right_light = false;
    }
  }

  explicit ControlHardware_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->horn = false;
      this->head_light = false;
      this->left_light = false;
      this->right_light = false;
    }
  }

  // field types and members
  using _horn_type =
    bool;
  _horn_type horn;
  using _head_light_type =
    bool;
  _head_light_type head_light;
  using _left_light_type =
    bool;
  _left_light_type left_light;
  using _right_light_type =
    bool;
  _right_light_type right_light;

  // setters for named parameter idiom
  Type & set__horn(
    const bool & _arg)
  {
    this->horn = _arg;
    return *this;
  }
  Type & set__head_light(
    const bool & _arg)
  {
    this->head_light = _arg;
    return *this;
  }
  Type & set__left_light(
    const bool & _arg)
  {
    this->left_light = _arg;
    return *this;
  }
  Type & set__right_light(
    const bool & _arg)
  {
    this->right_light = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    can_msgs::msg::ControlHardware_<ContainerAllocator> *;
  using ConstRawPtr =
    const can_msgs::msg::ControlHardware_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<can_msgs::msg::ControlHardware_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<can_msgs::msg::ControlHardware_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      can_msgs::msg::ControlHardware_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<can_msgs::msg::ControlHardware_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      can_msgs::msg::ControlHardware_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<can_msgs::msg::ControlHardware_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<can_msgs::msg::ControlHardware_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<can_msgs::msg::ControlHardware_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__can_msgs__msg__ControlHardware
    std::shared_ptr<can_msgs::msg::ControlHardware_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__can_msgs__msg__ControlHardware
    std::shared_ptr<can_msgs::msg::ControlHardware_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ControlHardware_ & other) const
  {
    if (this->horn != other.horn) {
      return false;
    }
    if (this->head_light != other.head_light) {
      return false;
    }
    if (this->left_light != other.left_light) {
      return false;
    }
    if (this->right_light != other.right_light) {
      return false;
    }
    return true;
  }
  bool operator!=(const ControlHardware_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ControlHardware_

// alias to use template instance with default allocator
using ControlHardware =
  can_msgs::msg::ControlHardware_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace can_msgs

#endif  // CAN_MSGS__MSG__DETAIL__CONTROL_HARDWARE__STRUCT_HPP_

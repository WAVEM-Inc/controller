// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from can_msgs:msg/Mode.idl
// generated code does not contain a copyright notice

#ifndef CAN_MSGS__MSG__DETAIL__MODE__STRUCT_HPP_
#define CAN_MSGS__MSG__DETAIL__MODE__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__can_msgs__msg__Mode __attribute__((deprecated))
#else
# define DEPRECATED__can_msgs__msg__Mode __declspec(deprecated)
#endif

namespace can_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Mode_
{
  using Type = Mode_<ContainerAllocator>;

  explicit Mode_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->slam_mode = false;
    }
  }

  explicit Mode_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->slam_mode = false;
    }
  }

  // field types and members
  using _slam_mode_type =
    bool;
  _slam_mode_type slam_mode;

  // setters for named parameter idiom
  Type & set__slam_mode(
    const bool & _arg)
  {
    this->slam_mode = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    can_msgs::msg::Mode_<ContainerAllocator> *;
  using ConstRawPtr =
    const can_msgs::msg::Mode_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<can_msgs::msg::Mode_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<can_msgs::msg::Mode_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      can_msgs::msg::Mode_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<can_msgs::msg::Mode_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      can_msgs::msg::Mode_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<can_msgs::msg::Mode_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<can_msgs::msg::Mode_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<can_msgs::msg::Mode_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__can_msgs__msg__Mode
    std::shared_ptr<can_msgs::msg::Mode_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__can_msgs__msg__Mode
    std::shared_ptr<can_msgs::msg::Mode_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Mode_ & other) const
  {
    if (this->slam_mode != other.slam_mode) {
      return false;
    }
    return true;
  }
  bool operator!=(const Mode_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Mode_

// alias to use template instance with default allocator
using Mode =
  can_msgs::msg::Mode_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace can_msgs

#endif  // CAN_MSGS__MSG__DETAIL__MODE__STRUCT_HPP_

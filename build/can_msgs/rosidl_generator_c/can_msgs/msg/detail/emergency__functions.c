// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from can_msgs:msg/Emergency.idl
// generated code does not contain a copyright notice
#include "can_msgs/msg/detail/emergency__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
can_msgs__msg__Emergency__init(can_msgs__msg__Emergency * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    can_msgs__msg__Emergency__fini(msg);
    return false;
  }
  // stop
  return true;
}

void
can_msgs__msg__Emergency__fini(can_msgs__msg__Emergency * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // stop
}

bool
can_msgs__msg__Emergency__are_equal(const can_msgs__msg__Emergency * lhs, const can_msgs__msg__Emergency * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // stop
  if (lhs->stop != rhs->stop) {
    return false;
  }
  return true;
}

bool
can_msgs__msg__Emergency__copy(
  const can_msgs__msg__Emergency * input,
  can_msgs__msg__Emergency * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // stop
  output->stop = input->stop;
  return true;
}

can_msgs__msg__Emergency *
can_msgs__msg__Emergency__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  can_msgs__msg__Emergency * msg = (can_msgs__msg__Emergency *)allocator.allocate(sizeof(can_msgs__msg__Emergency), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(can_msgs__msg__Emergency));
  bool success = can_msgs__msg__Emergency__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
can_msgs__msg__Emergency__destroy(can_msgs__msg__Emergency * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    can_msgs__msg__Emergency__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
can_msgs__msg__Emergency__Sequence__init(can_msgs__msg__Emergency__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  can_msgs__msg__Emergency * data = NULL;

  if (size) {
    data = (can_msgs__msg__Emergency *)allocator.zero_allocate(size, sizeof(can_msgs__msg__Emergency), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = can_msgs__msg__Emergency__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        can_msgs__msg__Emergency__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
can_msgs__msg__Emergency__Sequence__fini(can_msgs__msg__Emergency__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      can_msgs__msg__Emergency__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

can_msgs__msg__Emergency__Sequence *
can_msgs__msg__Emergency__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  can_msgs__msg__Emergency__Sequence * array = (can_msgs__msg__Emergency__Sequence *)allocator.allocate(sizeof(can_msgs__msg__Emergency__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = can_msgs__msg__Emergency__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
can_msgs__msg__Emergency__Sequence__destroy(can_msgs__msg__Emergency__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    can_msgs__msg__Emergency__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
can_msgs__msg__Emergency__Sequence__are_equal(const can_msgs__msg__Emergency__Sequence * lhs, const can_msgs__msg__Emergency__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!can_msgs__msg__Emergency__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
can_msgs__msg__Emergency__Sequence__copy(
  const can_msgs__msg__Emergency__Sequence * input,
  can_msgs__msg__Emergency__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(can_msgs__msg__Emergency);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    can_msgs__msg__Emergency * data =
      (can_msgs__msg__Emergency *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!can_msgs__msg__Emergency__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          can_msgs__msg__Emergency__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!can_msgs__msg__Emergency__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}

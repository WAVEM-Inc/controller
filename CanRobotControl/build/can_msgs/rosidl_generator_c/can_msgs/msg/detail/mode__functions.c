// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from can_msgs:msg/Mode.idl
// generated code does not contain a copyright notice
#include "can_msgs/msg/detail/mode__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
can_msgs__msg__Mode__init(can_msgs__msg__Mode * msg)
{
  if (!msg) {
    return false;
  }
  // slam_mode
  return true;
}

void
can_msgs__msg__Mode__fini(can_msgs__msg__Mode * msg)
{
  if (!msg) {
    return;
  }
  // slam_mode
}

bool
can_msgs__msg__Mode__are_equal(const can_msgs__msg__Mode * lhs, const can_msgs__msg__Mode * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // slam_mode
  if (lhs->slam_mode != rhs->slam_mode) {
    return false;
  }
  return true;
}

bool
can_msgs__msg__Mode__copy(
  const can_msgs__msg__Mode * input,
  can_msgs__msg__Mode * output)
{
  if (!input || !output) {
    return false;
  }
  // slam_mode
  output->slam_mode = input->slam_mode;
  return true;
}

can_msgs__msg__Mode *
can_msgs__msg__Mode__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  can_msgs__msg__Mode * msg = (can_msgs__msg__Mode *)allocator.allocate(sizeof(can_msgs__msg__Mode), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(can_msgs__msg__Mode));
  bool success = can_msgs__msg__Mode__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
can_msgs__msg__Mode__destroy(can_msgs__msg__Mode * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    can_msgs__msg__Mode__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
can_msgs__msg__Mode__Sequence__init(can_msgs__msg__Mode__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  can_msgs__msg__Mode * data = NULL;

  if (size) {
    data = (can_msgs__msg__Mode *)allocator.zero_allocate(size, sizeof(can_msgs__msg__Mode), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = can_msgs__msg__Mode__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        can_msgs__msg__Mode__fini(&data[i - 1]);
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
can_msgs__msg__Mode__Sequence__fini(can_msgs__msg__Mode__Sequence * array)
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
      can_msgs__msg__Mode__fini(&array->data[i]);
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

can_msgs__msg__Mode__Sequence *
can_msgs__msg__Mode__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  can_msgs__msg__Mode__Sequence * array = (can_msgs__msg__Mode__Sequence *)allocator.allocate(sizeof(can_msgs__msg__Mode__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = can_msgs__msg__Mode__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
can_msgs__msg__Mode__Sequence__destroy(can_msgs__msg__Mode__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    can_msgs__msg__Mode__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
can_msgs__msg__Mode__Sequence__are_equal(const can_msgs__msg__Mode__Sequence * lhs, const can_msgs__msg__Mode__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!can_msgs__msg__Mode__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
can_msgs__msg__Mode__Sequence__copy(
  const can_msgs__msg__Mode__Sequence * input,
  can_msgs__msg__Mode__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(can_msgs__msg__Mode);
    can_msgs__msg__Mode * data =
      (can_msgs__msg__Mode *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!can_msgs__msg__Mode__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          can_msgs__msg__Mode__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!can_msgs__msg__Mode__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}

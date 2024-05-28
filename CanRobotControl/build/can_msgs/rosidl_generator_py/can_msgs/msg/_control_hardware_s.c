// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from can_msgs:msg/ControlHardware.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "can_msgs/msg/detail/control_hardware__struct.h"
#include "can_msgs/msg/detail/control_hardware__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool can_msgs__msg__control_hardware__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[47];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("can_msgs.msg._control_hardware.ControlHardware", full_classname_dest, 46) == 0);
  }
  can_msgs__msg__ControlHardware * ros_message = _ros_message;
  {  // horn
    PyObject * field = PyObject_GetAttrString(_pymsg, "horn");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->horn = (Py_True == field);
    Py_DECREF(field);
  }
  {  // head_light
    PyObject * field = PyObject_GetAttrString(_pymsg, "head_light");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->head_light = (Py_True == field);
    Py_DECREF(field);
  }
  {  // left_light
    PyObject * field = PyObject_GetAttrString(_pymsg, "left_light");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->left_light = (Py_True == field);
    Py_DECREF(field);
  }
  {  // right_light
    PyObject * field = PyObject_GetAttrString(_pymsg, "right_light");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->right_light = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * can_msgs__msg__control_hardware__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of ControlHardware */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("can_msgs.msg._control_hardware");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "ControlHardware");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  can_msgs__msg__ControlHardware * ros_message = (can_msgs__msg__ControlHardware *)raw_ros_message;
  {  // horn
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->horn ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "horn", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // head_light
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->head_light ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "head_light", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // left_light
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->left_light ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "left_light", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // right_light
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->right_light ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "right_light", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

# generated from rosidl_generator_py/resource/_idl.py.em
# with input from can_msgs:msg/ControlHardware.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ControlHardware(type):
    """Metaclass of message 'ControlHardware'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('can_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'can_msgs.msg.ControlHardware')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__control_hardware
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__control_hardware
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__control_hardware
            cls._TYPE_SUPPORT = module.type_support_msg__msg__control_hardware
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__control_hardware

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ControlHardware(metaclass=Metaclass_ControlHardware):
    """Message class 'ControlHardware'."""

    __slots__ = [
        '_horn',
        '_head_light',
        '_left_light',
        '_right_light',
    ]

    _fields_and_field_types = {
        'horn': 'boolean',
        'head_light': 'boolean',
        'left_light': 'boolean',
        'right_light': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.horn = kwargs.get('horn', bool())
        self.head_light = kwargs.get('head_light', bool())
        self.left_light = kwargs.get('left_light', bool())
        self.right_light = kwargs.get('right_light', bool())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.horn != other.horn:
            return False
        if self.head_light != other.head_light:
            return False
        if self.left_light != other.left_light:
            return False
        if self.right_light != other.right_light:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def horn(self):
        """Message field 'horn'."""
        return self._horn

    @horn.setter
    def horn(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'horn' field must be of type 'bool'"
        self._horn = value

    @property
    def head_light(self):
        """Message field 'head_light'."""
        return self._head_light

    @head_light.setter
    def head_light(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'head_light' field must be of type 'bool'"
        self._head_light = value

    @property
    def left_light(self):
        """Message field 'left_light'."""
        return self._left_light

    @left_light.setter
    def left_light(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'left_light' field must be of type 'bool'"
        self._left_light = value

    @property
    def right_light(self):
        """Message field 'right_light'."""
        return self._right_light

    @right_light.setter
    def right_light(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'right_light' field must be of type 'bool'"
        self._right_light = value

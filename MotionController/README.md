### WmMotionController
Ros2 WmMotionController is a program that receives calculated result values and controls movement to the robot and delivers the result values through can communication.

CAN (Controller Area Network) is a communication protocol used in control systems such as cars and robots, suitable for fast data transmission and ensuring reliability. In ROS 2, CAN communication is supported through the can_msgs package.

First, obtain the cmd_vel value published by ros2 and calculate it according to the movement.

Next, the nodes that control the robot transmit accordingly to the command protocol over CAN communication.

### 개발환경
* ![Dev badge](https://img.shields.io/badge/ROS2-Foxy-orange?style=flat&logo=ROS&logoColor=white)
* ![Dev_badge](https://img.shields.io/badge/Ubuntu-20.04-brightgreen?style=flat&logo=Ubuntu&logoColor=white)
* ![Dev_badge](https://img.shields.io/badge/HardWare-NUC12-lightgrey)
* ![Dev_badge](https://img.shields.io/badge/Robot-Wabot3-blue)

### Network dev
* CAN
* DDS
* IPC

### Compile
1. can_msgs
    ```
    ${packages_dir} / colcon build --packages-select can_msgs
    ```
2. wm_motion_controller
    ```
    ${packages_dir} / colcon build --packages-select wm_motion_controller
    ```

### Test
0. Setting
    ```bash
    source ./.bashrc or ./.bashrc_foxy
    source ${packages_dir}/install/setup.bash
    ```

1. Compile<br/>
    1.1. can_led_keyboard
    ```bash
    ${packages_dir} / colcon build --packages-select can_led_keyboard
    ```
2. Run<br/>
    2.1. wm_motion_controller run
    ```bash
    ros2 run wm_motion_controller_node
    ```
    2.2 can_led_keyboard
    ```bash
    ros2 run can_led_keyboard
    h : horrn, l : head_light, j : left_light, k : right_light, s : all off, a : all on
    ```

### Topic
* Subscriber
    + cmd_vel<br/>
    + can/control_hardware<br/>

* Publisher 
    + can/control_hardware<br/>    


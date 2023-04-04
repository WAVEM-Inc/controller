### WmMotionController
Ros2 WmMotionController is a program that receives calculated result values and controls movement to the robot and delivers the result values through can communication.

CAN (Controller Area Network) is a communication protocol used in control systems such as cars and robots, suitable for fast data transmission and ensuring reliability. In ROS 2, CAN communication is supported through the can_msgs package.

First, obtain the cmd_vel value published by ros2 and calculate it according to the movement.

Next, the nodes that control the robot transmit accordingly to the command protocol over CAN communication.

### 개발환경
* ![Dev badge](https://img.shields.io/badge/ROS2-Foxy-orange/white?style=flat&logo=ROS&logoColor=white)
* ![Dev_badge](https://img.shields.io/badge/Ubuntu-20.04-brightgreen?style=flat&logo=Ubuntu&logoColor=white)
* ![Dev_badge](https://img.shields.io/badge/HardWare-NUC12-lightgrey)
* ![Dev_badge](https://img.shields.io/badge/Target-Wabot3-blue)

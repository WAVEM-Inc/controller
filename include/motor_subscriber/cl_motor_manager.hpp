#ifndef MOTOR_MANAGER
#define MOTOR_MANAGER
#include"common/common_header.hpp"
#include"common/common.hpp"
#include<fstream>
#include<pthread.h>
#include<thread>
#include<cstring>
#include "motor_subscriber/cl_motor_recv_data.hpp"
//==
#include "ros/ros.h"                          // ROS Default Header File
#include <geometry_msgs/Twist.h>
#include "../include/gpio_ctrl.h"

#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <fcntl.h>
//==
#include <time.h>
class cl_motor_manager{
    public :
        cl_motor_recv_data m_motor_recv_data;
        cl_motor_manager();
        void test_read();
        static void msgCallback(const geometry_msgs::Twist& cmd_vel_msg);
        static int fn_get_speed(float vel_linear, float x,float y);
        int m_old_encoder;
        ros::Time m_old_time;
    private :
        //pthread_t m_device_read;
        //static void* fn_device_read(void* data);
        int r_ro_val;
        int l_ro_val;
        void fn_device_read_();
        void do_encoder();
        void fn_ros_run();
        char* fn_substr(char* str, int start, int end);
        
};
#endif
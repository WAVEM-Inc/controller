#include "ros/ros.h"                          // ROS Default Header File
#include "ros_tutorials_topic/MsgTutorial.h"  // MsgTutorial Message File Header. The header file is automatically created when building the package.
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

#define RIGHT_MOTOR 1
#define LEFT_MOTOR 2
#define RIGHT_MOTOR_DIR 12
#define LEFT_MOTOR_DIR 6

#define AC_PULS2 15
#define AC_SIGN2  97

#define LIGHT_RED 118
#define LIGHT_GREEN 117

#define INIT_PERIOD 10000

#define  ESS_KEY     9527
#define  ESS_SIZE    sizeof(struct epoll_sensor_info)
#define  KEY_NUM     9527
#define  MEM_SIZE    1024

struct left_encor_info{
	int encor_left;
};

struct right_encor_info{
	int encor_right;
};

struct epoll_sensor_info {
	struct left_encor_info left_encor_data;
	struct right_encor_info right_encor_data;
};
/////////////////////////////////////minseok//////////////////////////////
static pthread_t acmotor_thread;

float vel_linear,vel_angular;

int writeAcPulse(int motor_num,int num)
{
	int lp;
	int pulse_num;
	int ac_pulse;
	pulse_num=abs(num);
	if(num < 0)
	{
		ac_pulse = AC_SIGN2;
	}
	else if (num > 0)
	{
		ac_pulse = AC_PULS2;
	}
	for(lp=0;lp<pulse_num;lp++)
	{
		gpio_set_val(ac_pulse,0);
		usleep(1);
		gpio_set_val(ac_pulse,1);
		usleep(1);
	}
}

void *do_acmotor(void *arg)
{
	int   epoll_shm_id;//minseok
	struct epoll_sensor_info *epoll_shm;//minseok
	struct encor_info *encor_data;//minseok

	struct left_encor_info *left_encor_data;//minseok
	struct right_encor_info *right_encor_data;//minseok

	int r_ro_val=0;
	int l_ro_val=0;
	int *left_sem_val,*right_sem_val, l_sem_val, r_sem_val;
	int *sem_arg;

	sem_t *left_sem;
	sem_t *right_sem;
//	sem_unlink("left_sem");
//	sem_unlink("right_sem");
	left_sem_val=&l_sem_val;
	right_sem_val=&r_sem_val;
	if((left_sem = sem_open("left_sem", O_CREAT, 0777, 0)) == NULL)
	{
		perror("Sem Open Error");
	}

	if((right_sem = sem_open("right_sem", O_CREAT, 0777, 0)) == NULL)
	{
		perror("Sem Open Error");
	}

	if (-1 == (epoll_shm_id = shmget((key_t)KEY_NUM, MEM_SIZE, IPC_CREAT|0666)))
	{
		printf( "Create share mem fail\n");
	}

	if ((void *)-1 == ( epoll_shm = static_cast<epoll_sensor_info*>(shmat( epoll_shm_id, 0x0, 0))))
	{
		printf( "Insert share mem fail\n");
	}
		
	left_encor_data = &epoll_shm->left_encor_data;
	right_encor_data = &epoll_shm->right_encor_data;
	while(1)
	{
		l_ro_val= l_ro_val + 30*(vel_linear + vel_angular);
		r_ro_val= r_ro_val + 30*(vel_linear - vel_angular);
		ROS_INFO("l_ro_val=%d, r_ro_val=%d\n",l_ro_val, r_ro_val);
		sem_getvalue(left_sem,left_sem_val);
		if(l_sem_val < 1)
		{
			sem_post(left_sem);
			left_encor_data->encor_left = l_ro_val;
			l_ro_val=0;
		}
		sem_getvalue(right_sem,right_sem_val);
		if(r_sem_val < 1)
		{
			sem_post(right_sem);
			right_encor_data->encor_right = r_ro_val;
			r_ro_val=0;
		}
		usleep(100000);
	}
}

int initAc(void)
{
	gpio_export(AC_PULS2);
	gpio_export(AC_SIGN2);
	gpio_set_output(AC_PULS2);
	gpio_set_output(AC_SIGN2);
	gpio_set_val(AC_PULS2,1);
	gpio_set_val(AC_SIGN2,1);

	pthread_create(&acmotor_thread, 0, do_acmotor, 0);
	pthread_detach(acmotor_thread);
}

////////////////////////////////////////////////////////

// Message callback function. This is a function is called when a topic
// message named 'ros_tutorial_msg' is received. As an input message,
// the 'MsgTutorial' message of the 'ros_tutorials_topic' package is received.
float ac_angular_bak = 0;
void msgCallback(const geometry_msgs::Twist& cmd_vel_msg)
{
	vel_linear = cmd_vel_msg.linear.x;
	vel_angular = cmd_vel_msg.angular.z;
	printf("linear = %.02f,angular = %.02f\n", vel_linear, vel_angular);
}

int main(int argc, char **argv)                         // Node Main Function
{
	initAc();	
	ros::init(argc, argv, "acmotor_subscriber");            // Initializes Node Name
	ros::NodeHandle nh;                                   // Node handle declaration for communication with ROS system
	ros::Subscriber ros_tutorial_sub = nh.subscribe("cmd_vel", 100, msgCallback);

	ros::spin();

	return 0;
}

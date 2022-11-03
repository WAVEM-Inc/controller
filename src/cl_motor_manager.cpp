#include"motor_subscriber/cl_motor_manager.hpp"
#include <signal.h>
#include <unistd.h>
#include "motor_subscriber/motor_data.hpp"

#include <fstream>
cl_motor_manager::cl_motor_manager(){
    
}

void cl_motor_manager::test_read(){
    //pthread_t device_read;
    //pthread_create(&device_read,NULL, &cl_motor_manager::fn_device_read, (void*) this);
    //pthread_detach(device_read);
	ros::Time::init();
    std::thread thread_read(&cl_motor_manager::fn_device_read_,this);
	std::thread thread_encoder(&cl_motor_manager::do_encoder,this);
	std::thread thread_ros_move(&cl_motor_manager::fn_ros_run,this);
	thread_read.join();
	thread_encoder.join();
	thread_ros_move.join();
    //fn_device_read();
}

void cl_motor_manager::msgCallback(const geometry_msgs::Twist& cmd_vel_msg){
	float vel_linear,vel_angular;
	int fd;
	int l_speed, r_speed;
	char cdr_motor_buf[64];
	vel_linear = cmd_vel_msg.linear.x;
	vel_angular = cmd_vel_msg.angular.z;
	fd=open(CDR_MOTOR_TTY, O_RDWR);

	/**
	 * @brief pwm control
	 * @date 22.10.19
	 * @author ChangunAn
	*/
	//std::cout<<"[vel_linear]"<< vel_linear<<std::endl;
	//std::cout<<"[vel_angular]"<< vel_angular<<std::endl;
	//l_speed = 1000*(vel_linear - vel_angular);
	//r_speed = 1000*(vel_linear + vel_angular);

	l_speed = fn_get_speed(vel_linear - ((vel_angular*0.225)),vel_linear,vel_angular);
	r_speed = fn_get_speed(vel_linear + ((vel_angular*0.225)),vel_linear,vel_angular);

	//std::cout<<"[vel_linear]"<< vel_linear<<std::endl;
	//std::cout<<"[l_speed]"<< l_speed<<std::endl;
	//std::cout<<"[r_speed]"<< r_speed<<std::endl;
	memset(cdr_motor_buf,0,sizeof(cdr_motor_buf));
	int l_dir, r_dir;
	if(l_speed < 0){
		l_dir = 1;
	}
	else {
		l_dir = 0;
	}
	if(r_speed<0){
		r_dir = 1;
	}
	else{
		r_dir = 0;
	}
	sprintf(cdr_motor_buf,"<M%01d%04d,%01d%04d,11>",l_dir,abs(l_speed),r_dir,abs(r_speed));
	printf("STR=-->%s<--\n",cdr_motor_buf);
	write(fd, cdr_motor_buf,strlen(cdr_motor_buf));
	close(fd);
	printf("linear = %.02f,angular = %.02f\n", vel_linear, vel_angular);
}

void cl_motor_manager::fn_device_read_(){
	char* recv_data;
	m_old_encoder=0;
	m_old_time= ros::Time::now();
	int read_flag=1;
	int read_success_check=0;
	while(true){
		

		std::ifstream stream_read(CDR_MOTOR_TTY,std::ios_base::in);
		recv_data=new char[RECV_SIZE];
		memset(recv_data,0,sizeof(char)*RECV_SIZE);
		stream_read>>recv_data;
		char *left_angle_bracket = 0;
		char *right_angle_bracket = 0;
		std::cout<<"[read]"<<recv_data<<' ';
		left_angle_bracket=strchr(recv_data,'<');
		right_angle_bracket=strrchr(recv_data,'>');
		if((right_angle_bracket-recv_data)-(left_angle_bracket-recv_data)==14){
			std::cout<<"Packet Read Success ";
			m_motor_recv_data.fn_set_left_move((std::atoi(fn_substr(recv_data,RECV_LEFT_START,RECV_LEFT_END))));
			//m_motor_recv_data.fn_set_left_move((std::atoi(fn_substr(recv_data,RECV_LEFT_START,RECV_LEFT_END)))*3.0);
			m_motor_recv_data.fn_set_left_move((std::atoi(fn_substr(recv_data,RECV_LEFT_START,RECV_LEFT_END))));
			m_motor_recv_data.fn_set_right_move(std::atoi(fn_substr(recv_data,RECV_RIGHT_START, RECV_RIGHT_END)));
			std::cout<<"left"<<m_motor_recv_data.fn_get_left_move()<<" "<<left_angle_bracket-recv_data<<' ';
			std::cout<<"right"<<m_motor_recv_data.fn_get_right_move()<<" "<<right_angle_bracket-recv_data<<std::endl;
			read_success_check=0;
		}
		else{
			std::cout<<"Packet Read Failed"<<std::endl;
			read_success_check++;
		}

		if(read_success_check==3){
			std::cout<<"Program Down"<<std::endl;
			
		}
		signal(SIGINT, SIG_DFL); 
	}
}
void cl_motor_manager::do_encoder(){
    while(1){
		std::cout<<"[do_ecnoder]"<<std::endl;
		int   epoll_shm_id;//minseok
		struct epoll_sensor_info *epoll_shm;//minseok
		struct encor_info *encor_data;//minseok

		struct left_encor_info *left_encor_data;//minseok
		struct right_encor_info *right_encor_data;//minseok

		int *left_sem_val,*right_sem_val, l_sem_val, r_sem_val;
		int *sem_arg;

		sem_t *left_sem;
		sem_t *right_sem;
		//	sem_unlink("left_sem");
		//	sem_unlink("right_sem");
		left_sem_val=&l_sem_val;
		right_sem_val=&r_sem_val;
		if((left_sem = sem_open("left_sem", O_CREAT, 0777, 0)) == NULL){
			perror("Sem Open Error");
		}

		if((right_sem = sem_open("right_sem", O_CREAT, 0777, 0)) == NULL){
			perror("Sem Open Error");
		}

		if (-1 == (epoll_shm_id = shmget((key_t)KEY_NUM, MEM_SIZE, IPC_CREAT|0666))){
			printf( "Create share mem fail\n");
		}

		if ((void *)-1 == ( epoll_shm = static_cast<epoll_sensor_info*>(shmat( epoll_shm_id, 0x0, 0)))){
			printf( "Insert share mem fail\n");
		}

		left_encor_data = &epoll_shm->left_encor_data;
		right_encor_data = &epoll_shm->right_encor_data;
		int read_left_flag = 1;
		int read_right_flag =1; 
		//
		std::ofstream write_file;
		write_file.open("/home/ubuntu/Project/result.txt");
		//
		while(ros::ok)
		{
			sem_getvalue(left_sem,left_sem_val);

			if(l_sem_val < 1)
			{
				sem_post(left_sem);
				l_ro_val = m_motor_recv_data.fn_get_left_move();
				
				time_t cur_time = time(NULL);
				struct tm* local = localtime(&cur_time);
				write_file<<local->tm_year << ':'<<local->tm_mon<<':'<<local->tm_mday<<'_'<<local->tm_hour<<':'<<local->tm_min <<" [l_ro_val]"<<l_ro_val<<std::endl;
				
				if(read_left_flag==1 && l_ro_val!=0){
					m_motor_recv_data.fn_set_old_left_move(l_ro_val);
					//	std::cout<<"[read_left_flag]"<<l_ro_val <<' '<<m_motor_recv_data.fn_get_old_left_move()<<std::endl;
					read_left_flag=0;
				}
				else{
					//std::cout<<"[sema_test_l_old]"<<l_ro_val<<" "<<m_motor_recv_data.fn_get_old_left_move()<<std::endl;
					int left_check = l_ro_val-m_motor_recv_data.fn_get_old_left_move();
					if(left_check<-OVER_NUMBER_CHECK){
						left_encor_data->encor_left= l_ro_val-m_motor_recv_data.fn_get_old_left_move()+OVER_NUMBER;
					}else if(left_check>OVER_NUMBER_CHECK){
							left_encor_data->encor_left= l_ro_val-m_motor_recv_data.fn_get_old_left_move()-OVER_NUMBER;
					}
					else if((std::abs(left_check)<1000)||l_ro_val==0){
						left_encor_data->encor_left = l_ro_val-m_motor_recv_data.fn_get_old_left_move();
					}
					else {
						std::cout<< "[Left Encoder Data] : "<<left_check <<std::endl;
					}

					if(left_encor_data->encor_left!=0){
						std::cout<<"[sema_test_l]"<<left_encor_data->encor_left <<std::endl;
					}
					m_motor_recv_data.fn_set_old_left_move(l_ro_val);
				}
			}
			sem_getvalue(right_sem,right_sem_val);
			if(r_sem_val < 1)
			{
				sem_post(right_sem);
				r_ro_val = m_motor_recv_data.fn_get_right_move();
				
					time_t cur_time = time(NULL);
				struct tm* local = localtime(&cur_time);
				write_file<<local->tm_year << ':'<<local->tm_mon<<':'<<local->tm_mday<<'_'<<local->tm_hour<<':'<<local->tm_min <<" [r_ro_val]"<<r_ro_val<<std::endl;
				
				if(read_right_flag==1 && r_ro_val!=0){
					m_motor_recv_data.fn_set_old_right_move(r_ro_val);
					read_right_flag=0;
				}
				else{
				//	std::cout<<"[sema_test_r_old]"<<r_ro_val<<" "<<m_motor_recv_data.fn_get_old_right_move()<<std::endl;
					int right_check = r_ro_val-m_motor_recv_data.fn_get_old_right_move();
					if(right_check<-OVER_NUMBER_CHECK){
						right_encor_data->encor_right= r_ro_val-m_motor_recv_data.fn_get_old_right_move()+OVER_NUMBER;
					}else if(right_check>OVER_NUMBER_CHECK){
							right_encor_data->encor_right= r_ro_val-m_motor_recv_data.fn_get_old_right_move()-OVER_NUMBER;
					}
					else if((std::abs(right_check)<1000||r_ro_val==0)){
						right_encor_data->encor_right = r_ro_val-m_motor_recv_data.fn_get_old_right_move();
					}
					else {
						std::cout<< "[Right Encoder Data] : "<<right_check <<std::endl;
					}

					if(right_encor_data->encor_right!=0){
						std::cout<<"[sema_test_r]"<<right_encor_data->encor_right <<std::endl;
					}
					m_motor_recv_data.fn_set_old_right_move(r_ro_val);
				}
			}
			usleep(10);	
			signal(SIGINT, SIG_DFL); 
		}
		write_file.close();
		sleep(1);
	}
	////////////////////////////////////////////////
}

char* cl_motor_manager::fn_substr(char*str, int start, int end){
	int size = end - start;
	if(start>end){
		return NULL;
	}
	char* result = new char[size+1];
	strncpy(result,str+start,size+1);
	result[size+1]=0;
	return result;
}

void cl_motor_manager::fn_ros_run(){
	ros::NodeHandle nh;                                   // Node handle declaration for communication with ROS system
	ros::Subscriber ros_tutorial_sub = nh.subscribe("cmd_vel", 1, &cl_motor_manager::msgCallback);
	ros::spin();
}

int cl_motor_manager::fn_get_speed(float vel_motor, float x,float y){
	int result_speed = 0;
	//std::cout<<"[vel]"<<vel_motor<<std::endl;
	float abs_vel_motor = std::abs(vel_motor);
	if(abs_vel_motor>0&&abs_vel_motor<=MOTOR_HALF){
		result_speed = 0+(600)*(VEL_COEFFICIENT*abs_vel_motor);
		//std::cout<<vel_linear<<" "<<result_speed<<" "<<(0+650)<<" "<<(0+650)*VEL_COEFFICIENT<<" "<<(0+650)*(VEL_COEFFICIENT*x)<<" "<<MOTOR_HALF<<std::endl;
	}
	else if(abs_vel_motor>MOTOR_HALF && abs_vel_motor<=MOTOR_FIRST){
		result_speed = 600+(350*(VEL_COEFFICIENT*(abs_vel_motor - MOTOR_HALF)));
		//std::cout<<vel_linear<<" "<<result_speed<<" "<<(300+650)<<" "<<(300+650)*VEL_COEFFICIENT<<" "<<(300+650)*(VEL_COEFFICIENT*x)<<" "<<MOTOR_FIRST<<std::endl;
	
	}
	else if(abs_vel_motor>MOTOR_FIRST && abs_vel_motor<=MOTOR_FIRST_HALF){
		result_speed = 950+(212*(VEL_COEFFICIENT*(abs_vel_motor - MOTOR_FIRST)));
	}
	else if(abs_vel_motor>MOTOR_FIRST_HALF && abs_vel_motor<=MOTOR_SECOND){
		result_speed = 1162+(108*(VEL_COEFFICIENT*(abs_vel_motor - MOTOR_FIRST_HALF)));
		
	}
	else if(abs_vel_motor>MOTOR_SECOND && abs_vel_motor<=MOTOR_SECOND_HALF){
		result_speed = 1270+(55*(VEL_COEFFICIENT*(abs_vel_motor-MOTOR_SECOND)));
	}
	else if(abs_vel_motor>MOTOR_SECOND_HALF && abs_vel_motor<=MOTOR_THIRD){
		result_speed = 1325+(40*(VEL_COEFFICIENT*(abs_vel_motor-MOTOR_SECOND_HALF)));
	}
	else if(abs_vel_motor>MOTOR_THIRD && abs_vel_motor<=MOTOR_THIRD_HALF){
		result_speed = 1365+(31*(VEL_COEFFICIENT*(abs_vel_motor-MOTOR_THIRD)));
	}
	else if(abs_vel_motor>MOTOR_THIRD_HALF && abs_vel_motor<=MOTOR_FOURTH){
		result_speed = 1396+(24*(VEL_COEFFICIENT*(abs_vel_motor-MOTOR_THIRD_HALF)));
	}
	else if(abs_vel_motor>MOTOR_FOURTH && abs_vel_motor<=MOTOR_FOURTH_HALF){
		result_speed = 1420+(18*(VEL_COEFFICIENT*(abs_vel_motor-MOTOR_FOURTH)));
	}
	else if(abs_vel_motor>MOTOR_FOURTH_HALF && abs_vel_motor<=MOTOR_FIFTH){
		result_speed = 1438+(12*(VEL_COEFFICIENT*(abs_vel_motor-MOTOR_FOURTH_HALF)));
	}
	//std::cout<<"[vel2]"<<vel_motor<<" "<<result_speed<<std::endl;

	return vel_motor>0 ?result_speed:-result_speed;
	//return result_speed;
}

/*
//
		int left_move = m_motor_recv_data.fn_get_left_move();
		int right_move = m_motor_recv_data.fn_get_right_move();
		if((right_move-m_old_encoder)>=30){
			
			double test_time = ros::Time::now().toSec()-m_old_time.toSec();
		
			std::cout<<"[Time!!]"<<test_time<<" L "<<left_move<<" R "<<right_move<<" "<<m_old_encoder<<std::endl;
			std::cout<<"[Velocity]"<< ((right_move-m_old_encoder))*1.57/test_time<<std::endl;
			
			std::cout<<std::endl;
			std::cout<<std::endl;
			std::cout<<std::endl;
			std::cout<<std::endl;
			
			m_old_time= ros::Time::now();
			m_old_encoder = m_motor_recv_data.fn_get_right_move();
		}
		//
*/

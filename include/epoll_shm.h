/**
 * @file         epoll_shm.h
 * @author       geminit
 * @date         2017-05-12
 * @brief        Sensor program header
 */

#ifndef __EPOLL_SHM__
#define __EPOLL_SHM__

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#define  ESS_KEY     9527
#define  ESS_SIZE    sizeof(struct epoll_sensor_info)

struct dust_info {
	struct timeval dust_time;
	int dust;
	float dust_val;
	float dust_M;
};

struct gyro_info{
	struct timeval gyro_time;
	int acclX_f;
	int acclY_f;
	int acclZ_f;
	float gyro_X_f;
	float gyro_Y_f;
	float gyro_Z_f;
	float gyroX_f;
	float gyroY_f;
};

struct gps_info{
	struct timeval gps_time;
	float Lat_fix;
	float Long_fix;
	int satell_num;
};

struct temp_info{
	struct timeval temp_time;
	int temp_val;
	int hum_val;
	int temp_a_val;
	int hum_a_val;
};

struct fire_info{
	struct timeval fire_time;
	int fire_D1;
	int fire_D2;
	int fire_D3;
	int fire_D4;
};

struct epoll_sensor_info {
	struct dust_info dust_data;
	struct gps_info gps_data;
	struct gyro_info gyro_data;
	struct temp_info temp_data;
	struct fire_info fire_data;
};

#endif //__EPOLL_SHM_

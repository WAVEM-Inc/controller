/**
 * @file         pack_data.c
 * @author       geminit
 * @brief        pack_data 소스 파일
 * @date         2017-07-14
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <wiringSerial.h>
#include <pack_data.h>
#include <epoll_shm.h>
#include <mkpacket.h>
#include <gutil.h>

static int pack_len;
static char prod_id[8], dev_id[8], prod_date[8], dev_num[16], prot_ver[8], firm_ver[16], com_type[8];
static char server_ip[50], server_port[5], api_ver[15], device_token[20], service_id[25], device_id[25];
static char now_time[128];
char pack[1024];
char front_pack[128];
static struct tm *t;
static int tty_at_fd;

/**
 * @brief        시리얼 데이터를 가져오는 함수
 * @param        char *data : 읽어온 시리얼 데이터 값 
 * @param        int len : 읽어올 시리얼 데이터 크기 
 * @return       읽어온 데이터 길이
 */
int get_serial_data(char *data, int len)
{
	int ret = 0;
//	printf("File: %s, LINE: %d\n",__FILE__,__LINE__);
	while(serialDataAvail(tty_at_fd))
	{
		*data = serialGetchar(tty_at_fd);
//		printf("%c", *data );
		printf("%c", *data );
		data++;
		ret++;
		if(ret>=len)
		{
			printf("ret>=len, %s, %d\n",__FILE__,__LINE__);
			break;
		}
	}
	printf("\n");
//	printf("File: %s, LINE: %d\n",__FILE__,__LINE__);
	return ret;
}
int get_serial_data_hex(char *data, int len)
{
	int ret = 0;
//	char buffer[2048];
//	memset(buffer,0,sizeof(buffer));
//	data=buffer + strlen(buffer);
//	printf("File: %s, LINE: %d\n",__FILE__,__LINE__);
	while(serialDataAvail(tty_at_fd))
	{
		sprintf(data,"%02x",serialGetchar(tty_at_fd));
//		printf("%s\n", buffer );
		data+=2;
		ret++;
		if(ret>=len)
		{
			printf("ret>=len, %s, %d\n",__FILE__,__LINE__);
			break;
		}
	}
//	strcpy(data,buffer);
	printf("\n");
//	printf("File: %s, LINE: %d\n",__FILE__,__LINE__);
	return ret;
}

int get_config_data(void)
{
	int    fd;
	int front_i;
	int dev_num_val;
	char   f_buff[256];
	char *dev_ver;
	memset(f_buff,0,sizeof(f_buff));
	memset(front_pack,0,sizeof(front_pack));
	memset(prod_id,0,sizeof(prod_id));
	memset(dev_id,0,sizeof(dev_id));
	memset(dev_num,0,sizeof(dev_num));
	memset(prod_date,0,sizeof(prod_date));
	memset(prot_ver,0,sizeof(prot_ver));
	memset(firm_ver,0,sizeof(firm_ver));
	memset(com_type,0,sizeof(com_type));
	if( 0 < (fd = open( "/home/root/at/env_config", O_RDONLY)))
	{
		read( fd, f_buff, 256);
		close(fd);
	}
	else
	{
		printf("config file open error\n");
	}
	for(front_i=0; front_i<4; front_i++)
	{
		if(strstr(f_buff,"Manufacturer:")==NULL)
		{
			printf("Manufacturer read error\n");
			return -1;
		}
		else if(strstr(f_buff,"Manufacturer:")[front_i+13] ==';')
		{
			break;
		}
		else
		{
			prod_id[front_i] = strstr(f_buff,"Manufacturer:")[front_i+13];
			//			printf("prod_id=%s\n",prod_id);
		}
	}
	for(front_i=0; front_i<4; front_i++)
	{
		if(strstr(f_buff,"Model:")==NULL)
		{
			printf("Model read error\n");
			return -1;
		}
		else if(strstr(f_buff,"Model:")[front_i+6] ==';')
		{
			break;
		}
		else
		{
			dev_id[front_i] = strstr(f_buff,"Model:")[front_i+6];
			//			printf("dev_id=%s\n",dev_id);
		}
	}
	for(front_i=0; front_i<3; front_i++)
	{
		if(strstr(f_buff,"Date_of_maufacture:")==NULL)
		{
			printf("Date read error\n");
			return -1;
		}
		else if(strstr(f_buff,"Date_of_maufacture:")[front_i+19] ==';')
		{
			break;
		}
		else
		{
			prod_date[front_i] = strstr(f_buff,"Date_of_maufacture:")[front_i+19];
			//			printf("prod_date=%s\n",prod_date);
		}
	}
	for(front_i=0; front_i<5; front_i++)
	{
		if(strstr(f_buff,"Serial_number:")==NULL)
		{
			printf("Serial_number read error\n");
			return -1;
		}
		else if(strstr(f_buff,"Serial_number:")[front_i+14] ==';')
		{
			break;
		}
		else
		{
			dev_num[front_i] = strstr(f_buff,"Serial_number:")[front_i+14];
			//			printf("dev_num=%s\n",dev_num);
		}
	}	
	for(front_i=0; front_i<3; front_i++)
	{
		if(strstr(f_buff,"Protocol_ver:")==NULL)
		{
			printf("Protocol_ver read error\n");
			return -1;
		}
		else if(strstr(f_buff,"Protocol_ver:")[front_i+13] ==';')
		{
			break;
		}
		else
		{
			prot_ver[front_i] = strstr(f_buff,"Protocol_ver:")[front_i+13];
			//			printf("protocol_num=%s\n",prot_ver);
		}
	}	
	for(front_i=0; front_i<10; front_i++)
	{
		if(strstr(f_buff,"firm_ver:")==NULL)
		{
			printf("firm_ver read error\n");
			return -1;
		}
		else if(strstr(f_buff,"firm_ver:")[front_i+9] ==';')
		{
			break;
		}
		else
		{
			firm_ver[front_i] = strstr(f_buff,"firm_ver:")[front_i+9];
			//			printf("firm_ver=%s\n",firm_ver);
		}
	}	
	for(front_i=0; front_i<1; front_i++)
	{
		if(strstr(f_buff,"Communication_type:")==NULL)
		{
			printf("Communication_type read error\n");
			return -1;
			break;
		}
		else if((strstr(f_buff,"Communication_type:")[front_i+19] ==';'))
		{
			break;
		}
		else
		{
			com_type[front_i] = strstr(f_buff,"Communication_type:")[front_i+19];
//			printf("com_type=%s\n",com_type);
		}
	}
	close(fd);
//	sprintf(dev_ver,"KT Sensor Detect Program\nModel:%s\nfirm ver:%s\nSerial number:%s\nDate of manufacture:%s\n",prod_id,firm_ver,dev_num,prod_date);
//	printf("KT Sensor Detect Program to OMNI Server\nModel:%s\nfirm ver:%s\nSerial number:%s\nDate of manufacture:%s\n",prod_id,firm_ver,dev_num,prod_date);
}

int get_config_data_samsung(void)
{
	int    fd;
	int front_i;
	int dev_num_val;
	char   f_buff[512];
	char *dev_ver;
	memset(server_ip,0,sizeof(server_ip));
	memset(server_port,0,sizeof(server_port));
	memset(api_ver,0,sizeof(api_ver));
	memset(device_token,0,sizeof(device_token));
	memset(service_id,0,sizeof(service_id));
	memset(device_id,0,sizeof(device_id));
	if( 0 < (fd = open( "/home/root/at/env_config", O_RDONLY)))
	{
		read( fd, f_buff, 512);
		close(fd);
	}
	else
	{
		printf("config file open error\n");
	}
	for(front_i=0; front_i<50; front_i++)
	{
		if(strstr(f_buff,"Server IP:")==NULL)
		{
			printf("Server IP read error\n");
			return -1;
		}
		else if(strstr(f_buff,"Server IP:")[front_i+10] ==';')
		{
			break;
		}
		else
		{
			server_ip[front_i] = strstr(f_buff,"Server IP:")[front_i+10];
//			printf("server ip=%s\n",server_ip);
		}
	}
	printf("server ip=%s\n",server_ip);
	for(front_i=0; front_i<5; front_i++)
	{
		if(strstr(f_buff,"Server Port:")==NULL)
		{
			printf("Server Port read error\n");
			return -1;
		}
		else if(strstr(f_buff,"Server Port:")[front_i+12] ==';')
		{
			break;
		}
		else
		{
			server_port[front_i] = strstr(f_buff,"Server Port:")[front_i+12];
			//			printf("dev_id=%s\n",dev_id);
		}
	}
	printf("server port=%s\n",server_port);
	for(front_i=0; front_i<15; front_i++)
	{
		if(strstr(f_buff,"API Version:")==NULL)
		{
			printf("API Version read error\n");
			return -1;
		}
		else if(strstr(f_buff,"API Version:")[front_i+12] ==';')
		{
			break;
		}
		else
		{
			api_ver[front_i] = strstr(f_buff,"API Version:")[front_i+12];
			//			printf("prod_date=%s\n",prod_date);
		}
	}
	printf("api_ver=%s\n",api_ver);
	for(front_i=0; front_i<20; front_i++)
	{
		if(strstr(f_buff,"Device token:")==NULL)
		{
			printf("Device token read error\n");
			return -1;
		}
		else if(strstr(f_buff,"Device token:")[front_i+13] ==';')
		{
			break;
		}
		else
		{
			device_token[front_i] = strstr(f_buff,"Device token:")[front_i+13];
			//			printf("dev_num=%s\n",dev_num);
		}
	}	
	printf("device_token=%s\n",device_token);
	for(front_i=0; front_i<25; front_i++)
	{
		if(strstr(f_buff,"Service ID:")==NULL)
		{
			printf("Service ID token read error\n");
			return -1;
		}
		else if(strstr(f_buff,"Service ID:")[front_i+11] ==';')
		{
			break;
		}
		else
		{
			service_id[front_i] = strstr(f_buff,"Service ID:")[front_i+11];
			//			printf("dev_num=%s\n",dev_num);
		}
	}	
	printf("service_id=%s\n",service_id);
	for(front_i=0; front_i<25; front_i++)
	{
		if(strstr(f_buff,"Device ID:")==NULL)
		{
			printf("Device ID read error\n");
			return -1;
		}
		else if(strstr(f_buff,"Device ID:")[front_i+10] ==';')
		{
			break;
		}
		else
		{
			device_id[front_i] = strstr(f_buff,"Device ID:")[front_i+10];
			//			printf("dev_num=%s\n",dev_num);
		}
	}	
	printf("device_id=%s\n",device_id);

	close(fd);
//	sprintf(dev_ver,"KT Sensor Detect Program\nModel:%s\nfirm ver:%s\nSerial number:%s\nDate of manufacture:%s\n",prod_id,firm_ver,dev_num,prod_date);
//	printf("KT Sensor Detect Program to OMNI Server\nModel:%s\nfirm ver:%s\nSerial number:%s\nDate of manufacture:%s\n",prod_id,firm_ver,dev_num,prod_date);
}
/**
* @brief       	에러 로그 생성 함수 날짜별 로그파일 생성, 시간을 읽어와서 에러 메세지 앞에 표시 
* @param        *dev_data : 생성할 로그메세ㅑ지
*/
int dev_log(char *dev_data)
{
	time_t new_time;
	int fd;
	char err_write[64];
	memset(now_time,0,sizeof(now_time));
	memset(err_write,0,sizeof(err_write));
	new_time = time(NULL);
	t = localtime(&new_time);
	strftime(now_time, sizeof(now_time),"/home/root/at/log/env_log_%04Y%02m%02d",t); 
	fd = open( now_time, O_WRONLY | O_CREAT | O_APPEND, 0644);
	sprintf(err_write, "%04d.%02d.%02d %02d:%02d:%02d, %s\n",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec, dev_data);
	write(fd, err_write,strlen(err_write));
	close(fd);
	printf("%s\n",dev_data);
}
int dev_log_iot(char *dev_data)
{
	time_t new_time;
	int fd;
	char err_write[64];
	memset(now_time,0,sizeof(now_time));
	memset(err_write,0,sizeof(err_write));
	new_time = time(NULL);
	t = localtime(&new_time);
	strftime(now_time, sizeof(now_time),"/home/root/iot/log/env_log_%04Y%02m%02d",t); 
	fd = open( now_time, O_WRONLY | O_CREAT | O_APPEND, 0644);
	sprintf(err_write, "%04d.%02d.%02d %02d:%02d:%02d, %s\n",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec, dev_data);
	write(fd, err_write,strlen(err_write));
	close(fd);
	printf("%s\n",dev_data);
}

int get_front_data(int pack_typ)
{	
	memset(front_pack, 0, sizeof(front_pack));
	sprintf(front_pack, "%4s%4s%3s%05d%02d      ",prod_id, dev_id, prod_date, atoi(dev_num), pack_typ);
}
int get_boot_data(char *front_data, char *tel)
{
	char body[512];
	memset(body, 0, sizeof(body));	
	mkpacket_begin(1024);
	mkpacket_add_id(front_data, PACK_DEVICE_ID_LEN);
	sprintf( body, "{\"tel\":\"%s\",\"ver\":\"%s\",\"fvr\":\"%s\",\"cty\":%s}",tel,prot_ver,firm_ver,com_type);
	mkpacket_add_body(1, body, strlen(body));
	mkpacket_end();
	memset( pack, 0, sizeof( pack ));
	pack_len = mkpacket_get( &pack[12] );
	strncpy( pack, "AT@TCPWRITE=", 12 );
	pack[strlen(pack)] = '\r';
	pack[strlen(pack)] = '\n';
	//sprintf( pack, "AT@TCPWRITE=%s\r\n", &pack[12] );
	printf("PAK: %s(%d)\n", pack, pack_len );
}

static struct epoll_sensor_info *epoll_shm;
static int   epoll_shm_id;

int get_body_data_init(void )
{

	if (-1 == (epoll_shm_id = shmget((key_t)KEY_NUM, MEM_SIZE, IPC_CREAT|0666)))
	{
		printf( "Create share mem fail\n");
		return -1;
	}

	if ((void *)-1 == ( epoll_shm = shmat( epoll_shm_id, ( void *)0, 0)))
	{
		printf( "Insert share mem fail\n");
		return -1;
	}
}

void get_body_data_remove( void )
{
	shmdt(epoll_shm);
	shmctl(epoll_shm_id, IPC_RMID, 0);
}

int get_body_data(char *front_data)
{
	time_t new_time;
	struct dust_info *dust_data;
	struct gps_info *gps_data;
	struct gyro_info *gyro_data;
	struct temp_info *temp_data;
	struct fire_info *fire_data;
	char body[512],body_1[512];
	char lat[32], lon[32],dust[32],roll[32],pitch[32],gyro_x[32],gyro_y[32],temp[32],hum[32],rtm[32],fire_1[32],fire_2[32],fire_3[32],fire_4[32];

	dust_data = &epoll_shm->dust_data;
	gps_data = &epoll_shm->gps_data;
	gyro_data = &epoll_shm->gyro_data;
	temp_data = &epoll_shm->temp_data;	
	fire_data = &epoll_shm->fire_data;
	new_time = time(NULL);
	t = localtime(&new_time);
	mkpacket_begin(1024);
	mkpacket_add_id(front_data, PACK_DEVICE_ID_LEN);
	memset(lon,0,sizeof(lon));
	memset(lat,0,sizeof(lat));
	memset(dust,0,sizeof(dust));
	memset(roll,0,sizeof(roll));
	memset(pitch,0,sizeof(pitch));
	memset(temp,0,sizeof(temp));
	memset(hum,0,sizeof(hum));
	memset(gyro_x,0,sizeof(gyro_x));
	memset(gyro_y,0,sizeof(gyro_y));
	memset(fire_1,0,sizeof(fire_1));
	memset(fire_2,0,sizeof(fire_2));
	memset(fire_3,0,sizeof(fire_3));
	memset(fire_4,0,sizeof(fire_4));
	memset(rtm,0,sizeof(rtm));
	sprintf(lon, "\"long\":\"%f ,E\"", gps_data->Long_fix); 
	sprintf(lat, "\"lat\":\"%f ,N\"", gps_data->Lat_fix);
	sprintf(dust, "\"dust\":%.2f",dust_data->dust_M);
	sprintf(temp, "\"tmp\":%d.0",temp_data->temp_a_val);
	sprintf(hum, "\"hum\":%d",temp_data->hum_a_val);
	sprintf(roll,"\"roll\":%.1f",gyro_data->gyro_X_f);
	sprintf(pitch,"\"pitch\":%.1f",gyro_data->gyro_Y_f);
	sprintf(gyro_x,"\"xde\":%.1f",gyro_data->gyro_X_f);
	sprintf(gyro_y,"\"yde\":%.1f",gyro_data->gyro_Y_f);
	sprintf(fire_1,"\"fire1\":%d",fire_data->fire_D1);
	sprintf(fire_2,"\"fire2\":%d",fire_data->fire_D2);
	sprintf(fire_3,"\"fire3\":%d",fire_data->fire_D3);
	sprintf(fire_4,"\"fire4\":%d",fire_data->fire_D4);
	sprintf(now_time, "\"rtm\":\"%04d%02d%02d%02d%02d%02d\"", t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
	printf("time : %s\n",now_time);
	//	printf("temp :->%s<-\n",temp);
	memset(body, 0, sizeof(body));	
	memset(body_1, 0, sizeof(body_1));	
	sprintf( body, "{%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s}",temp, hum, roll, pitch, gyro_x, gyro_y, fire_1, fire_2, fire_3, fire_4, dust, lon, lat, now_time);
	sprintf( body_1, "{%s,%s,%s,%s,%s,%s,%s,%s,%s,%s}",temp, hum, roll, pitch, gyro_x, gyro_y, dust, lon, lat, now_time);
	if((t->tm_hour > 20) || (t->tm_hour < 5))
		mkpacket_add_body(1, body, strlen(body));
	else
		mkpacket_add_body(1, body_1, strlen(body_1));
	mkpacket_end();
	memset( pack, 0, sizeof( pack ));
	pack_len = mkpacket_get( &pack[12] );
	strncpy( pack, "AT@TCPWRITE=", 12 );
	pack[strlen(pack)] = '\r';
	pack[strlen(pack)] = '\n';
	//sprintf( pack, "AT@TCPWRITE=%s\r\n", &pack[12] );
	printf("PAK: %s(%d)\n", pack, pack_len );
}

int get_body_data_one(char *front_data)
{
	time_t new_time;
	struct dust_info *dust_data;
	struct gps_info *gps_data;
	struct gyro_info *gyro_data;
	char body[1024];
	char lat[32], lon[32],dust[32],roll[32],pitch[32],yaw[32],gyro_x[32],gyro_y[32],rtm[32],accX[32],accY[32],accZ[32];
	dust_data = &epoll_shm->dust_data;
	gps_data = &epoll_shm->gps_data;
	gyro_data = &epoll_shm->gyro_data;
	new_time = time(NULL);
	t = localtime(&new_time);
	mkpacket_begin(1024);
	mkpacket_add_id(front_data, PACK_DEVICE_ID_LEN);
	memset(lon,0,sizeof(lon));
	memset(lat,0,sizeof(lat));
	memset(dust,0,sizeof(dust));
	memset(roll,0,sizeof(roll));
	memset(pitch,0,sizeof(pitch));
	memset(yaw,0,sizeof(yaw));
	memset(gyro_x,0,sizeof(gyro_x));
	memset(gyro_y,0,sizeof(gyro_y));
	memset(rtm,0,sizeof(rtm));
	memset(accX,0,sizeof(accX));
	memset(accY,0,sizeof(accY));
	memset(accZ,0,sizeof(accZ));
	sprintf(lon, "\"long\":\"%f ,E\"", gps_data->Long_fix); 
	sprintf(lat, "\"lat\":\"%f ,N\"", gps_data->Lat_fix);
	sprintf(dust, "\"dust\":%.2f",dust_data->dust_M);
	sprintf(roll,"\"roll\":%.1f",gyro_data->gyro_X_f);
	sprintf(pitch,"\"pitch\":%.1f",gyro_data->gyro_Y_f);
	sprintf(yaw,"\"yaw\":%.1f",gyro_data->gyro_Z_f);
	sprintf(gyro_x,"\"xde\":%.1f",gyro_data->gyro_X_f);
	sprintf(gyro_y,"\"yde\":%.1f",gyro_data->gyro_Y_f);
	sprintf(accX,"\"vib_x\":%d",gyro_data->acclX_f);
	sprintf(accY,"\"vib_y\":%d",gyro_data->acclY_f);
	sprintf(accZ,"\"vib_z\":%d",gyro_data->acclZ_f);
	sprintf(now_time, "\"rtm\":\"%04d%02d%02d%02d%02d%02d\"", t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
	printf("time : %s\n",now_time);
	memset(body, 0, sizeof(body));	
	sprintf( body, "{%s,%s,%s,%s,%s,%s,%s,%s,%s,%s}", yaw, roll, pitch, accX, accY, accZ, dust, lon, lat, now_time);
	mkpacket_add_body(1, body, strlen(body));
	mkpacket_end();
	memset( pack, 0, sizeof( pack ));
	pack_len = mkpacket_get( &pack[12] );
	strncpy( pack, "AT@TCPWRITE=", 12 );
	pack[strlen(pack)] = '\r';
	pack[strlen(pack)] = '\n';
	//sprintf( pack, "AT@TCPWRITE=%s\r\n", &pack[12] );
	printf("PAK: %s(%d)\n", pack, pack_len );
}

int get_body_data_temp(char *front_data)
{
	time_t new_time;
	struct gps_info *gps_data;
	struct temp_info *temp_data;
	char body[1024];
	char lat[32], lon[32],temp[32],hum[32],rtm[32];
	gps_data = &epoll_shm->gps_data;
	temp_data = &epoll_shm->temp_data;	
	new_time = time(NULL);
	t = localtime(&new_time);
	mkpacket_begin(1024);
	mkpacket_add_id(front_data, PACK_DEVICE_ID_LEN);
	memset(lon,0,sizeof(lon));
	memset(lat,0,sizeof(lat));
	memset(temp,0,sizeof(temp));
	memset(hum,0,sizeof(hum));
	memset(rtm,0,sizeof(rtm));
	sprintf(lon, "\"long\":\"%f ,E\"", gps_data->Long_fix); 
	sprintf(lat, "\"lat\":\"%f ,N\"", gps_data->Lat_fix);
	sprintf(temp, "\"tmp\":%d.0",temp_data->temp_a_val);
	sprintf(hum, "\"hum\":%d",temp_data->hum_a_val);
	sprintf(now_time, "\"rtm\":\"%04d%02d%02d%02d%02d%02d\"", t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
	printf("time : %s\n",now_time);
	//	printf("temp :->%s<-\n",temp);
	memset(body, 0, sizeof(body));	
	sprintf( body, "{%s,%s,%s,%s,%s}",temp, hum, lon, lat, now_time);
	mkpacket_add_body(1, body, strlen(body));
	mkpacket_end();
	memset( pack, 0, sizeof( pack ));
	pack_len = mkpacket_get( &pack[12] );
	strncpy( pack, "AT@TCPWRITE=", 12 );
	pack[strlen(pack)] = '\r';
	pack[strlen(pack)] = '\n';
	//sprintf( pack, "AT@TCPWRITE=%s\r\n", &pack[12] );
	printf("PAK: %s(%d)\n", pack, pack_len );
}

int get_body_data_fire(char *front_data)
{
	time_t new_time;
	struct gps_info *gps_data;
	struct fire_info *fire_data;
	char body[1024];
	char lat[32], lon[32],rtm[32],fire_1[32],fire_2[32],fire_3[32],fire_4[32];
	gps_data = &epoll_shm->gps_data;
	fire_data = &epoll_shm->fire_data;
	new_time = time(NULL);
	t = localtime(&new_time);
	mkpacket_begin(1024);
	mkpacket_add_id(front_data, PACK_DEVICE_ID_LEN);
	memset(lon,0,sizeof(lon));
	memset(lat,0,sizeof(lat));
	memset(fire_1,0,sizeof(fire_1));
	memset(fire_2,0,sizeof(fire_2));
	memset(fire_3,0,sizeof(fire_3));
	memset(fire_4,0,sizeof(fire_4));
	memset(rtm,0,sizeof(rtm));
	sprintf(lon, "\"long\":\"%f ,E\"", gps_data->Long_fix); 
	sprintf(lat, "\"lat\":\"%f ,N\"", gps_data->Lat_fix);
	sprintf(fire_1,"\"fire1\":%d",fire_data->fire_D1);
	sprintf(fire_2,"\"fire2\":%d",fire_data->fire_D2);
	sprintf(fire_3,"\"fire3\":%d",fire_data->fire_D3);
	sprintf(fire_4,"\"fire4\":%d",fire_data->fire_D4);
	sprintf(now_time, "\"rtm\":\"%04d%02d%02d%02d%02d%02d\"", t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
	printf("time : %s\n",now_time);
	//	printf("temp :->%s<-\n",temp);
	memset(body, 0, sizeof(body));	
	sprintf( body, "{%s,%s,%s,%s,%s,%s,%s}", fire_1, fire_2, fire_3, fire_4, lon, lat, now_time);
	mkpacket_add_body(1, body, strlen(body));
	mkpacket_end();
	memset( pack, 0, sizeof( pack ));
	pack_len = mkpacket_get( &pack[12] );
	strncpy( pack, "AT@TCPWRITE=", 12 );
	pack[strlen(pack)] = '\r';
	pack[strlen(pack)] = '\n';
	//sprintf( pack, "AT@TCPWRITE=%s\r\n", &pack[12] );
	printf("PAK: %s(%d)\n", pack, pack_len );
}

int get_body_data_samsung(void)
{
	time_t new_time;
	struct dust_info *dust_data;
	struct gps_info *gps_data;
	struct gyro_info *gyro_data;
	struct temp_info *temp_data;
	struct fire_info *fire_data;
	char body[512],body_1[512];
	char lat[32], lon[32],dust[32],roll[32],pitch[32],gyro_x[32],gyro_y[32],gyro_z[32],accX[32],accY[32],accZ[32],temp[32],hum[32],rtm[32],fire_1[32],fire_2[32],fire_3[32],fire_4[32];

	dust_data = &epoll_shm->dust_data;
	gps_data = &epoll_shm->gps_data;
	gyro_data = &epoll_shm->gyro_data;
	temp_data = &epoll_shm->temp_data;	
	fire_data = &epoll_shm->fire_data;
	new_time = time(NULL);
	t = localtime(&new_time);
	memset(lon,0,sizeof(lon));
	memset(lat,0,sizeof(lat));
	memset(dust,0,sizeof(dust));
	memset(roll,0,sizeof(roll));
	memset(pitch,0,sizeof(pitch));
	memset(temp,0,sizeof(temp));
	memset(hum,0,sizeof(hum));
	memset(gyro_x,0,sizeof(gyro_x));
	memset(gyro_y,0,sizeof(gyro_y));
	memset(gyro_z,0,sizeof(gyro_z));
	memset(accX,0,sizeof(accX));
	memset(accY,0,sizeof(accY));
	memset(accZ,0,sizeof(accZ));
	memset(fire_1,0,sizeof(fire_1));
	memset(fire_2,0,sizeof(fire_2));
	memset(fire_3,0,sizeof(fire_3));
	memset(fire_4,0,sizeof(fire_4));
	memset(rtm,0,sizeof(rtm));
	sprintf(lon, "\"long\":\"%f\"", gps_data->Long_fix); 
	sprintf(lat, "\"lat\":\"%f\"", gps_data->Lat_fix);
	sprintf(dust, "\"dust\":\"%.2f\"",dust_data->dust_M);
	sprintf(temp, "\"temp\":\"%d.0\"",temp_data->temp_a_val);
	sprintf(hum, "\"hum\":\"%d\"",temp_data->hum_a_val);
	sprintf(gyro_x,"\"tx\":\"%.1f\"",gyro_data->gyro_X_f);
	sprintf(gyro_y,"\"ty\":\"%.1f\"",gyro_data->gyro_Y_f);
	sprintf(gyro_z,"\"tz\":\"%.1f\"",gyro_data->gyro_Z_f);
	sprintf(accX,"\"vx\":\"%d\"",gyro_data->acclX_f);
	sprintf(accY,"\"vy\":\"%d\"",gyro_data->acclY_f);
	sprintf(accZ,"\"vz\":\"%d\"",gyro_data->acclZ_f);
	sprintf(fire_1,"\"fl\":\"%d\"",fire_data->fire_D1);
	sprintf(fire_2,"\"fb\":\"%d\"",fire_data->fire_D2);
	sprintf(fire_3,"\"fr\":\"%d\"",fire_data->fire_D3);
	sprintf(fire_4,"\"ft\":\"%d\"",fire_data->fire_D4);
	sprintf(now_time, "\"time\":\"%04d%02d%02d%02d%02d%02d\"", t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
//	printf("time : %s\n",now_time);
	//	printf("temp :->%s<-\n",temp);
	memset(body, 0, sizeof(body));	
	memset(body_1, 0, sizeof(body_1));	
	sprintf( body, "{%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s}\r\n",lon,lat,temp,hum,dust,fire_1,fire_2,fire_3,fire_4,gyro_x,gyro_y,gyro_z,accX,accY,accZ,now_time);
//	sprintf( body, "{%s,%s}\r\n",lon,lat);
	memset( pack, 0, sizeof( pack ));
	sprintf( pack, "AT+NONIPSEND=%s", body );
	//sprintf( pack, "AT@TCPWRITE=%s\r\n", &pack[12] );
	printf("PAK: %s\n", pack, pack_len );
}

/**
* @brief        REMS를 이용, AT커맨드로 데이터를 보내는 함수
* @param       	*cmd : 보낼 AT 커맨드 내용
* @param        cmd_size : AT커맨드 길이 \r\n 길이 고려
* @param        *rdata : REMS에서 받는 응답 시리얼 데이터
* @param        rdata_size : 받을 길이
* @param       	time_out : AT명령 실행 후 sleep 타임
* @return       읽어온 데이터 길이
*/
int send_at( char *cmd, int cmd_size, char *rdata, int rdata_size, int timeout )
{
	int ret = 0;
	serialPuts(tty_at_fd, cmd);
	sleep(timeout);
	memset( rdata, 0, rdata_size);
	ret = get_serial_data( rdata, rdata_size);
	serialFlush(tty_at_fd);
	return ret;
}
int send_at_open( char *cmd, int cmd_size, char *rdata, int rdata_size, int timeout )
{
	int ret = 0;
	int lp = 0;
	serialPuts(tty_at_fd, cmd);
//	sleep(timeout);
	memset( rdata, 0, rdata_size);
	sleep(1);
	for(lp=0;lp < timeout;lp++)
	{
		sleep(1);
		ret = get_serial_data( rdata, rdata_size);
		if(strstr(rdata,"@TCPOPEN") != NULL)
		{
			break;
		}
	}
	serialFlush(tty_at_fd);
	return ret;
}

int send_at_send( char *cmd, int cmd_size, char *rdata, int rdata_size, int timeout )
{
	int ret = 0;
	int lp = 0;
	serialPuts(tty_at_fd, cmd);
//	sleep(timeout);
	memset( rdata, 0, rdata_size);
	sleep(1);
	for(lp=0;lp < timeout;lp++)
	{
		sleep(1);
		ret = get_serial_data( rdata, rdata_size);
		if(strstr(rdata,"@TCPRECVDONE") != NULL)
		{
			break;
		}
	}
	serialFlush(tty_at_fd);
	return ret;
}
int send_at_nb( char *cmd, int cmd_size, char *rdata, int rdata_size, int timeout )
{
	int ret = 0;
	int lp = 0;
	serialPuts(tty_at_fd, cmd);
	sleep(timeout);
	memset( rdata, 0, rdata_size);
	ret = get_serial_data( rdata, rdata_size);
	serialFlush(tty_at_fd);
	return ret;
}
int send_at_nb_hex( char *cmd, int cmd_size, char *rdata, int rdata_size, int timeout )
{
	int ret = 0;
	int lp = 0;
	serialPuts(tty_at_fd, cmd);
//	sleep(timeout);
	memset( rdata, 0, rdata_size);
	sleep(1);
	for(lp=0;lp < timeout; lp++)
	{
		sleep(1);
		ret = get_serial_data_hex( rdata, rdata_size);
		if(strstr(rdata,"40534f434b5243563d") != NULL)
		{
			break;
		}
	}
	serialFlush(tty_at_fd);
//	printf("File: %s, LINE: %d\n",__FILE__,__LINE__);
	return ret;
}
int send_at_nb_open( char *cmd, int cmd_size, char *rdata, int rdata_size, int timeout )
{
	int ret = 0;
	int lp = 0;
	serialPuts(tty_at_fd, cmd);
//	sleep(timeout);
	memset( rdata, 0, rdata_size);
	sleep(1);
	for(lp=0;lp < timeout; lp++)
	{
		sleep(1);
		ret = get_serial_data( rdata, rdata_size);
		if(strstr(rdata,"@SOCKOPEN") != NULL)
		{
			break;
		}
	}
	serialFlush(tty_at_fd);
//	printf("File: %s, LINE: %d\n",__FILE__,__LINE__);
	return ret;
}
int serial_open(char *file, int baud)
{
	tty_at_fd = serialOpen(file,baud);
	return tty_at_fd;
}
/**
* @brief        바디 데이터 전송 함수 시간 갱신, REMS 네트워크 연결 여부 확인, AT명령어 후 응답 받도록 설정, TCP OPEN, TCP WRITE 순으로 진행, 진행 도중 에러나면 -1 리턴
* @return       ok = 1, error = -1
*/
int send_body_data(void)
{
	char time_y[4], time_M[2], time_d[2], time_h[2], time_m[2], time_s[2], now_date[128];
	int ret = 0;
	char rdata[1024];

	memset(rdata,0,sizeof(rdata));

	printf("AT@MSTIME?\n");
	ret = send_at("AT@MSTIME?\r\n", 12, rdata, sizeof(rdata), 1);
	if(strstr(rdata,"@MSTIME:") != NULL)
	{
		memset(now_date,0,sizeof(now_date));
		sprintf(time_y, "%c%c%c%c",rdata[12],rdata[13],rdata[14],rdata[15]);
		sprintf(time_M, "%c%c",rdata[17],rdata[18]);
		sprintf(time_d, "%c%c",rdata[20],rdata[21]);
		sprintf(time_h, "%c%c",rdata[23],rdata[24]);
		sprintf(time_m, "%c%c",rdata[26],rdata[27]);
		sprintf(time_s, "%c%c",rdata[29],rdata[30]);
		sprintf(now_date, "date -s '%s-%s-%s %s:%s:%s'", time_y, time_M, time_d, time_h, time_m, time_s);
		//				printf("now=%s\n",now_date);
		ret = system(now_date);
		//				printf("date:%s%s%s%s%s%s\n",time_y, time_M, time_d, time_h, time_m,time_s);	
	}
	printf("AT@NSI\n");
	ret = send_at("AT@NSI\r\n", 8, rdata, sizeof( rdata), 1);
	if(strstr(rdata,"IN SRV") == NULL)
	{
		dev_log("REMS No Service");
		return -1;
	}
	printf("AT@NOTISET=2\n");
	ret = send_at("AT@NOTISET=2\r\n", 14, rdata, sizeof(rdata), 1);
	if(strstr(rdata,"OK") == NULL)
	{
		dev_log("AT@NOTISET ERROR");
		return -1;
	}	
	printf("AT@TCPOPEN\n");
	ret = send_at_open("AT@TCPOPEN=220.72.216.152,7000\r\n",32, rdata, sizeof(rdata), 10);
	if(strstr(rdata,"@TCPOPEN") == NULL)
	{
		dev_log("AT@TCPOPEN error");
		printf("AT@TCPCLOSE\n");
		ret = send_at("AT@TCPCLOSE\r\n", 13, rdata, sizeof(rdata), 1);
		printf("AT@NOTISET=0\n");
		ret = send_at("AT@NOTISET=0\r\n",14, rdata, sizeof(rdata), 1);
		return -1;
	}
	printf("AT@TCPWRITE\n");
	ret = send_at_send(pack,strlen(pack), rdata, sizeof(rdata), 10);
	if(strstr(rdata,"@TCPRECVDONE") != NULL)
	{
		printf("AT@TCPCLOSE\n");
		ret = send_at("AT@TCPCLOSE\r\n", 13, rdata, sizeof(rdata), 1);
		printf("AT@NOTISET=0\n");
		ret = send_at("AT@NOTISET=0\r\n",14, rdata, sizeof(rdata), 1);
	}
	else
	{
		dev_log("AT@TCPWRITE error");
		printf("AT@TCPCLOSE\n");
		ret = send_at("AT@TCPCLOSE\r\n", 13, rdata, sizeof(rdata), 1);
		printf("AT@NOTISET=0\n");
		ret = send_at("AT@NOTISET=0\r\n",14, rdata, sizeof(rdata), 1);
		return -1;
	}
	return 1;
}

int send_body_data_samsung(void)
{
	char time_y[4], time_M[2], time_d[2], time_h[2], time_m[2], time_s[2], now_date[128];
	char tcp_open[128];
	int ret = 0;
	char rdata[1024];
	memset(tcp_open,0,sizeof(tcp_open));
	memset(rdata,0,sizeof(rdata));

	printf("AT@MSTIME?\n");
	ret = send_at("AT@MSTIME?\r\n", 12, rdata, sizeof(rdata), 1);
	if(strstr(rdata,"@MSTIME:") != NULL)
	{
		memset(now_date,0,sizeof(now_date));
		sprintf(time_y, "%c%c%c%c",rdata[23],rdata[24],rdata[25],rdata[26]);
		sprintf(time_M, "%c%c",rdata[28],rdata[29]);
		sprintf(time_d, "%c%c",rdata[31],rdata[32]);
		sprintf(time_h, "%c%c",rdata[34],rdata[35]);
		sprintf(time_m, "%c%c",rdata[37],rdata[38]);
		sprintf(time_s, "%c%c",rdata[40],rdata[41]);
		sprintf(now_date, "date -s '%s-%s-%s %s:%s:%s'", time_y, time_M, time_d, time_h, time_m, time_s);
		//				printf("now=%s\n",now_date);
		ret = system(now_date);
		//				printf("date:%s%s%s%s%s%s\n",time_y, time_M, time_d, time_h, time_m,time_s);	
	}

	printf("AT@NSI\n");
	ret = send_at("AT@NSI\r\n", 8, rdata, sizeof( rdata), 1);
	if(strstr(rdata,"IN SRV") == NULL)
	{
		dev_log("No Service");
		return -1;
	}

//	sprintf(tcp_open, "AT+SKTPCON=1,MQTTS,%s,%s,60,%s,%s,%s,%s\r\n",server_ip,server_port,api_ver,device_token,service_id,device_token);
/*	if(strstr(rdata,"+SKTPCON=0") == NULL)
	{
		dev_log("+SKTPCON error");
		printf("AT@TCPCLOSE\n");
		ret = send_at("AT@TCPCLOSE\r\n", 13, rdata, sizeof(rdata), 1);
		printf("AT@NOTISET=0\n");
		ret = send_at("AT@NOTISET=0\r\n",14, rdata, sizeof(rdata), 1);
		return -1;
	}
*/
	printf("AT+NONIPSTATUS?\n");
	ret = send_at("AT+NONIPSTATUS?\r\n", 17, rdata, sizeof(rdata), 1);
	if(strstr(rdata,"NONIPSTATUS=CONNECT") == NULL)
	{
		dev_log("SERVER CONNECT ERROR");
		sprintf(tcp_open, "AT+NONIPCON\r\n");
		printf("SERVER_OPEN CMD=%s\n",tcp_open);
		ret = send_at_open(tcp_open,strlen(tcp_open), rdata, sizeof(rdata), 3);
		return -1;
	}	
	printf("DATA_WRITE=%s\n",pack);
	ret = send_at_send(pack,strlen(pack), rdata, sizeof(rdata), 4);
/*	if(strstr(rdata,"@TCPRECVDONE") != NULL)
	{
		printf("AT@TCPCLOSE\n");
		ret = send_at("AT@TCPCLOSE\r\n", 13, rdata, sizeof(rdata), 1);
		printf("AT@NOTISET=0\n");
		ret = send_at("AT@NOTISET=0\r\n",14, rdata, sizeof(rdata), 1);
	}
	else
	{
		dev_log("AT@TCPWRITE error");
		printf("AT@TCPCLOSE\n");
		ret = send_at("AT@TCPCLOSE\r\n", 13, rdata, sizeof(rdata), 1);
		printf("AT@NOTISET=0\n");
		ret = send_at("AT@NOTISET=0\r\n",14, rdata, sizeof(rdata), 1);
		return -1;
	}
*/
	printf("AT+NONIPRESULT?\n");
	ret = send_at("AT+NONIPRESULT?\r\n", 17, rdata, sizeof(rdata), 1);
	if(strstr(rdata,"SUCCESS") == NULL)
	{
		dev_log("DATA SEND ERROR");
		return -1;
	}	
	return 1;
}

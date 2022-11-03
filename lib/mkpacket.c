/**
 * @file         mkpacket.c
 * @author       geminit
 * @brief        mkpacket 소스 파일
 * @date         2017-07-14
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <epoll_shm.h>
#include <time.h>
#include <mkpacket.h>
#include <gutil.h>

char *packet_data;
int   packet_len;
int   packet_pos;
char tmp_packet[1024];

/**
 * @brief        패킷 생생 시작 함수, 패킷 데이터 초기화
 * @param        int size : 패킷 길이 설정
 */
void mkpacket_begin( int size )
{
	packet_data = tmp_packet;
	packet_len = size;
	memset( packet_data, 0, packet_len );
	memset( packet_data, '0', POS_DEVICE_ID * 2 );
	packet_pos = POS_DEVICE_ID * 2;
	packet_len = 0;

	//printf("%s) POS: %d, LEN: %d\n", __func__, packet_pos, packet_len );
}

/**
 * @brief        디바이스 정보 부분, 바디 데이터 앞 부트 데이터 패킷 부분을 추가하는 함수
 * @param        char *id : 
 * @param        int len : 
 */
int mkpacket_add_id(char *id, int len)
{
	//	memset( &packet_data[packet_pos], 0x20, PACK_DEVICE_ID_LEN);
	//	memcpy( &packet_data[packet_pos], id, len);
	conv_2byte_hex( &packet_data[packet_pos], id, len );
	//	packet_pos += PACK_DEVICE_ID_LEN + 4;
	packet_pos += PACK_DEVICE_ID_LEN * 2;
	packet_len += PACK_DEVICE_ID_LEN;

	strncpy( &packet_data[packet_pos], "202020202020", 12 );
	packet_pos += 6 * 2;
	packet_len += 6;
	//	printf("%s) POS: %d, LEN: %d, BD: %s(%d)\n\n", __func__, packet_pos, packet_len, packet_data, strlen(packet_data));

	return packet_len;
}

int mkpacket_add_body( int index, char *data, int len )
{
	/*
	   memcpy( &packet_data[packet_pos], data, len );
	   packet_pos += len;
	   packet_len += len;
	 */
	conv_2byte_hex( &packet_data[packet_pos], data, len );
	packet_pos += len * 2;
	packet_len += len;
	//	printf("%s) POS: %d, LEN: %d, BD: %s(%d)\n\n", __func__, packet_pos, packet_len, packet_data, strlen(packet_data));
	return packet_len;
}

int mkpacket_end()
{
	char tmp[POS_DEVICE_ID +1];
	char tmp_hex[POS_DEVICE_ID*2+1];
	memset( tmp, 0, sizeof( tmp ));
	sprintf( tmp, "%04d", packet_len );
	conv_2byte_hex(tmp_hex, tmp, strlen(tmp) );
	memcpy( packet_data, tmp_hex, POS_DEVICE_ID*2);
//	printf("%s) : %s\n", __func__, tmp );
//	printf("%s) POS: %d, LEN: %d\n", __func__, packet_pos, packet_len );
	return packet_pos;
}

int mkpacket_get( char *packet )
{
//	printf("get pack=%s\n",packet_data);
	memcpy( packet, packet_data, packet_pos );
	return packet_pos;
}

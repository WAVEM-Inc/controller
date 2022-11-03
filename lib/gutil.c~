/**
 * @file         gutil.c
 * @author       geminit
 * @brief        gutil 소스 파일
 * @date         2017-07-14
 */
#include <stdio.h>
#include <string.h>
#include <gutil.h>
#include <unistd.h>

#define READ_SIZE 256

/**
 * @brief        ascii 값을 2byte hex 값으로 변환 하는 함수
 * @param        *val : 변환된 2byte hex 데이터
 * @param        *data : 2byte hex 값으로 바꿀 ascii 데이터
 * @param        len : 2byte hex값의 길이
 */
int conv_2byte_hex( char *val, char *data, int len )
{
	int lp;
	for( lp=0 ; lp<len ; lp++ )
	{
		sprintf( &val[lp*2], "%02x", data[lp] );
		//              printf("VAL:%c%c, DATA:%02x\n", val[lp], val[lp+1], data[lp] );
	}
}

/**
 * @brief        ascii 값을 2byte hex 값으로 변환 하는 함수
 * @param        int fd : 파일 디스크립터
 * @param        char *value : 파일에서 읽은 결과값
 * @param        char *cmd : 파싱할 문자열
 * @param        int size : value의 길이
 * @return	 -1 error : cmd의 문자와 파싱되는 문자가 없을 경우
 */
int gu_get_value_form_fd( int fd, char *value, char *cmd, int size )
{
	int lp;
	int pars_point;
	char r_buff[READ_SIZE], val_data[32];

	memset(r_buff,0,sizeof(r_buff));
	memset(val_data,0,sizeof(val_data));
	lseek(fd,0,SEEK_SET);
	read(fd, r_buff, READ_SIZE);
	pars_point = strlen(cmd);
	size = sizeof(val_data);

	for(lp=0; lp<32; lp++)
	{
		if(strstr(r_buff,cmd)==NULL)
		{
			printf("%s read error\n",cmd);
			return -1;
		}
		else if(strstr(r_buff,cmd)[lp+pars_point] =='\n')
		{
			break;
		}
		else
		{
			val_data[lp] = strstr(r_buff,cmd)[lp+pars_point];
			//	printf("protocol_num=%s\n",prot_ver);
		}
	}
	if(lp >= size)
	{
		printf("value size error\n");
		return -1;
	}
	else
	{
		memcpy(value, val_data, strlen(val_data));
	}
}

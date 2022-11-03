/**
 * @file         pack_data.h
 * @author       geminit
 * @brief        pack_data 헤더파일
 * @date         2017-07-14
 */

#ifndef __PACK_DATA_H__
#define __PACK_DATA_H__

#define  KEY_NUM     9527
#define  MEM_SIZE    1024
extern int send_at( char *cmd, int cmd_size, char *rdata, int rdata_size, int timeout );
extern int send_at_open( char *cmd, int cmd_size, char *rdata, int rdata_size, int timeout );
extern int send_at_send( char *cmd, int cmd_size, char *rdata, int rdata_size, int timeout );
extern int send_at_nb( char *cmd, int cmd_size, char *rdata, int rdata_size, int timeout );
extern int send_at_nb_hex( char *cmd, int cmd_size, char *rdata, int rdata_size, int timeout );
extern int send_body_data(void);
extern int send_body_data_samsung(void);
extern int dev_log(char *dev_data);
extern int dev_log_iot(char *dev_data);
extern int get_config_data(void);
extern int get_config_data_samsung(void);
extern int get_front_data(int pack_typ);
extern int get_body_data_init(void);
extern void get_body_data_remove(void);
extern int get_boot_data(char *front_data, char *tel);
extern int get_body_data(char *front_data);
extern int get_body_data_one(char *front_data);
extern int get_body_data_temp(char *front_data);
extern int get_body_data_fire(char *front_data);
extern int get_body_data_samsung(void);
extern int serial_open(char *file, int baud);

#endif //__PACK_DATA_H__


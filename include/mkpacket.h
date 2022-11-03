/**
 * @file         mkpacket.h
 * @author       geminit
 * @brief        mkpacket 헤더파일
 * @date         2017-07-14
 */

#ifndef __MKPAK_H__
#define __MKPAK_H__

#define PACK_DEVICE_ID_LEN	18
#define POS_DEVICE_ID		4


int conv_2byte_hex( char *val, char *data, int len );
void mkpacket_begin( int size );
int mkpacket_add_id(char *id, int len);
int mkpacket_add_body( int index, char *data, int len );
int mkpacket_end();
int mkpacket_get( char *packet );
int get_serial_data(char *data, int len);
int send_at( char *cmd, int cmd_size, char *rdata, int rdata_size, int timeout );

#endif

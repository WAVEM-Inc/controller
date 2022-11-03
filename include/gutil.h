/**
 * @file         gutil.h
 * @author       geminit
 * @brief        gutil 헤더파일
 * @date         2017-07-14
 */

#ifndef __GUTIL_H__
#define __GUTIL_H__

extern int conv_2byte_hex( char *val, char *data, int len );
extern int gu_get_value_form_fd( int fd, char *value, char *cmd, int size );

#endif

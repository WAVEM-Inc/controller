#ifndef LED_H
#define LED_H

#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdint.h>

int serialOpen (const char *device, const int baud);
void serialClose (const int fd);
void serialPutchar (const int fd, const unsigned char c);
void serialPuts (const int fd, const char *s);
int serialDataAvail (const int fd);
int serialGetchar (const int fd);
int get_serial_data(int fd, char *data, int len);
int get_serial_data_hex(int fd, char *data, int len);
int clcd_test(int fd, char *data);
int clcd_init(int fd);
int clcd_setcursor(int fd, int cur_x, int cur_y);
int clcd_write(int fd, char *data);
int clcd_clear(int fd);
int clcd_backlight_on(int fd);
int clcd_backlight_off(int fd);

#endif

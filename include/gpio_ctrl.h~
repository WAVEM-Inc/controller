/**
 * @file         led.h
 * @author       geminit
 * @brief        led 헤더파일
 * @date         2017-07-14
 */

#ifndef LED_H
#define LED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
//#include <fcntl.h>
#include <errno.h>

#define GPIO_OUTPUT	0
#define GPIO_INPUT	1
#define GPIO_HIGH	1
#define GPIO_LOW	0

#define GPIO_NONE	"none"
#define GPIO_FALLIN	"fallin"
#define GPIO_RISING	"rising"
#define GPIO_BOTH	"both"

#define SYSFS_GPIO_DIR	"/sys/class/gpio"
#define SYSFS_ADC_DIR	"/sys/bus/iio/devices/iio:device"

#define MAX_BUF 64

int gpio_export(unsigned int gpio);
int gpio_unexport(unsigned int gpio);
int gpio_get_dir(unsigned int gpio, unsigned int *dir);
int gpio_set_dir(unsigned int gpio, unsigned int dir, unsigned int val);
int gpio_get_val(unsigned int gpio, unsigned int *val);
int gpio_set_input(unsigned int gpio);
int gpio_set_output(unsigned int gpio);
int gpio_set_val(unsigned int gpio, unsigned int val);
int gpio_set_edge(unsigned int gpio, char *edge);
int gpio_open(unsigned int gpio);
int gpio_close(int fd);
int gpio_read(int fd, unsigned int *val);
int adc_get_val(unsigned int adc, unsigned int *val);
int pwm_export(unsigned int pwm);
int pwm_set_enable(unsigned pwm);
int pwm_set_disable(unsigned pwm);
int pwm_set_period(unsigned int pwm, unsigned long val);
int pwm_set_dutycycle(unsigned int pwm, unsigned long val);

#endif

/**
 * @file         gpio_ctrl.c
 * @author       geminit
 * @brief        gpio_ctrl 소스 파일
 * @date         2017-07-14
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
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
#define SYSFS_ADC_DIR	"/sys/bus/iio/devices/iio:device0"
#define SYSFS_PWM_DIR	"/sys/class/pwm"

#define MAX_BUF 128

int gpio_export(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];

	fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);

	if(fd < 0) {
		fprintf(stderr, "Can't export GPIO %d pin: %s\n", gpio, strerror(errno));
		return fd;
	}

	len = snprintf(buf, sizeof(buf), "%d", gpio);
	write(fd, buf, len);

	close(fd);

	return 0;
}

int gpio_unexport(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];

	fd = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);

	if(fd < 0) {
		fprintf(stderr, "Can't unexport GPIO %d pin: %s\n", gpio, strerror(errno));
		return fd;
	}

	len = snprintf(buf, sizeof(buf), "%d", gpio);
	write(fd, buf, len);

	close(fd);

	return 0;
}

int gpio_get_dir(unsigned int gpio, unsigned int *dir)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", gpio);

	fd = open(buf, O_RDONLY);

	if(fd < 0) {
		fprintf(stderr, "Can't get GPIO %d pin direction: %s\n", gpio, strerror(errno));
		return fd;
	}

	read(fd, &buf, MAX_BUF);
	close(fd);

	if(strcmp(buf, "in") == 0)
		*dir = GPIO_INPUT;
	else
		*dir = GPIO_OUTPUT;

	return 0;
}

int gpio_set_dir(unsigned int gpio, unsigned int dir, unsigned int val)
{
	int fd, len;
	char buf[MAX_BUF];
 
	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);
 
	fd = open(buf, O_WRONLY);
 
	if (fd < 0) {
		fprintf(stderr, "Can't set GPIO %d pin direction: %s\n", gpio, strerror(errno));
		return fd;
	}
 
	if (dir == GPIO_OUTPUT) {
		if (val == GPIO_HIGH)
			write(fd, "high", 5);
		else
			write(fd, "out", 4);
	} else
		write(fd, "in", 3);
 
	close(fd);
 
	return 0;
}

int gpio_get_val(unsigned int gpio, unsigned int *val)
{
	int fd, len;
	char buf[MAX_BUF];
 
	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

	fd = open(buf, O_RDONLY);
 
	if (fd < 0) {
		fprintf(stderr, "Can't get GPIO %d pin value: %s\n", gpio, strerror(errno));
		return fd;
	}
 
	read(fd, buf, 1);
	close(fd);
 
	if (*buf != '0')
		*val = GPIO_HIGH;
	else
		*val = GPIO_LOW;
 
	return 0;
}

int gpio_set_input(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", gpio);

	fd = open(buf, O_WRONLY);

	if(fd < 0) {
		fprintf(stderr, "Can't set GPIO %d pin value: %s\n", gpio, strerror(errno));
		return fd;
	}

	write(fd, "in", 3);

	close(fd);

	return 0;
}

int gpio_set_output(unsigned int gpio)
{
        int fd, len;
        char buf[MAX_BUF];

        len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", gpio);

        fd = open(buf, O_WRONLY);

        if(fd < 0) {
                fprintf(stderr, "Can't set GPIO %d pin value: %s\n", gpio, strerror(errno));
                return fd;
        }

        write(fd, "out", 4);

        close(fd);

        return 0;
}
 
int gpio_set_val(unsigned int gpio, unsigned int val)
{
	int fd, len;
	char buf[MAX_BUF];
 
	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
 
	fd = open(buf, O_WRONLY);
 
	if (fd < 0) {
		fprintf(stderr, "Can't set GPIO %d pin value: %s\n", gpio, strerror(errno));
		return fd;
	}
 
	if (val == GPIO_HIGH)
		write(fd, "1", 2);
	else
		write(fd, "0", 2);
 
	close(fd);

	return 0;
}
 
 int gpio_set_edge(unsigned int gpio, char *edge)
 {
     int fd, len;
     char buf[MAX_BUF];
 
     len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", gpio);
 
     fd = open(buf, O_WRONLY);
 
     if (fd < 0) {
         fprintf(stderr, "Can't set GPIO %d pin edge: %s\n", gpio, strerror(errno));
         return fd;
     }
 
     write(fd, edge, strlen(edge)+1);
     close(fd);
 
     return 0;
 }
 
 int gpio_open(unsigned int gpio)
 {
     int fd, len;
     char buf[MAX_BUF];
 
     len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
 
     fd = open(buf, O_RDONLY|O_NONBLOCK);
 
     if (fd < 0)
         fprintf(stderr, "Can't open GPIO %d pin: %s\n", gpio, strerror(errno));
 
     return fd;
 }
 
 int gpio_close(int fd)
 {
     return close(fd);
 }
 
 int gpio_read(int fd, unsigned int *val)
 {
     int ret;
     char ch; 
 
     lseek(fd, 0, SEEK_SET);
 
     ret = read(fd, &ch, 1);
 
     if (ret != 1) {
         fprintf(stderr, "Can't read GPIO %d pin: %s\n", fd, strerror(errno));
         return ret;
     }
 
     if (ch != '0')
         *val = GPIO_HIGH;
     else
         *val = GPIO_LOW;
 
     return 0;
 }

int adc_get_val(unsigned int adc, unsigned int *val)
{
	int fd, len;
	char buf[MAX_BUF];

	if(val == NULL) { fprintf(stderr, "Called by NULL\n"); return -1; }

	len = snprintf(buf, sizeof(buf), SYSFS_ADC_DIR "/in_voltage%d_raw", adc);

	fd = open(buf, O_RDONLY);

	if (fd < 0) {
		fprintf(stderr, "Can't get ADC %d pin value: %s\n", adc, strerror(errno));
		return fd;
	}

	read(fd, buf, 4);
	close(fd);

	*val = atoi(buf);

	return 0;
}

int pwm_export(unsigned int pwm)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_PWM_DIR "/pwmchip%d/export", pwm);

	fd = open(buf, O_WRONLY);

	if(fd < 0) {
		fprintf(stderr, "Can't export PWM %d pin: %s\n", pwm, strerror(errno));
		return fd;
	}
	
	write(fd, "0", 2);

	close(fd);

	return 0;
}

int pwm_set_enable(unsigned int pwm)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_PWM_DIR "/pwmchip%d/pwm0/enable", pwm);

	fd = open(buf, O_WRONLY);

	if(fd < 0) {
		fprintf(stderr, "Can't set PWM %d pin enable: %s\n", pwm, strerror(errno));
		return fd;
	}

	write(fd, "1", 2);
	close(fd);

	return 0;
}

int pwm_set_disable(unsigned int pwm)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_PWM_DIR "/pwmchip%d/pwm0/enable", pwm);

	fd = open(buf, O_WRONLY);

	if(fd < 0) {
		fprintf(stderr, "Can't set PWM %d pin disable: %s\n", pwm, strerror(errno));
		return fd;
	}
	write(fd, "0", 2);
	close(fd);
}

int pwm_set_period(unsigned int pwm, unsigned long val)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_PWM_DIR "/pwmchip%d/pwm0/period", pwm);

	fd = open(buf, O_WRONLY);

	if (fd < 0) {
		fprintf(stderr, "Can't set PWM %d pin period: %s\n", pwm, strerror(errno));
		return fd;
	}

    len = sprintf(buf, "%ld", val);
	write(fd, buf, len +1);

	close(fd);

	return 0;
}
int pwm_set_dutycycle(unsigned int pwm, unsigned long val)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_PWM_DIR "/pwmchip%d/pwm0/duty_cycle", pwm);

	fd = open(buf, O_WRONLY);

	if (fd < 0) {
		fprintf(stderr, "Can't set PWM %d pin duty-cycle: %s\n", pwm, strerror(errno));
		return fd;
	}

	len = sprintf(buf, "%ld", val);
	write(fd, buf, len +1);

	close(fd);

	return 0;
}


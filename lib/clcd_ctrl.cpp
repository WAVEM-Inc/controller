#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdint.h>
#include <clcd_ctrl.h>

int serialOpen (const char *device, const int baud)
{
	struct termios options ;
	speed_t myBaud ;
	int     status, fd ;

	switch (baud)
	{
		case      50:	myBaud =      B50 ; break ;
		case      75:	myBaud =      B75 ; break ;
		case     110:	myBaud =     B110 ; break ;
		case     134:	myBaud =     B134 ; break ;
		case     150:	myBaud =     B150 ; break ;
		case     200:	myBaud =     B200 ; break ;
		case     300:	myBaud =     B300 ; break ;
		case     600:	myBaud =     B600 ; break ;
		case    1200:	myBaud =    B1200 ; break ;
		case    1800:	myBaud =    B1800 ; break ;
		case    2400:	myBaud =    B2400 ; break ;
		case    4800:	myBaud =    B4800 ; break ;
		case    9600:	myBaud =    B9600 ; break ;
		case   19200:	myBaud =   B19200 ; break ;
		case   38400:	myBaud =   B38400 ; break ;
		case   57600:	myBaud =   B57600 ; break ;
		case  115200:	myBaud =  B115200 ; break ;
		case  230400:	myBaud =  B230400 ; break ;
		case  460800:	myBaud =  B460800 ; break ;
		case  500000:	myBaud =  B500000 ; break ;
		case  576000:	myBaud =  B576000 ; break ;
		case  921600:	myBaud =  B921600 ; break ;
		case 1000000:	myBaud = B1000000 ; break ;
		case 1152000:	myBaud = B1152000 ; break ;
		case 1500000:	myBaud = B1500000 ; break ;
		case 2000000:	myBaud = B2000000 ; break ;
		case 2500000:	myBaud = B2500000 ; break ;
		case 3000000:	myBaud = B3000000 ; break ;
		case 3500000:	myBaud = B3500000 ; break ;
		case 4000000:	myBaud = B4000000 ; break ;

		default:
				return -2 ;
	}

	if ((fd = open (device, O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK)) == -1)
		return -1 ;

	fcntl (fd, F_SETFL, O_RDWR) ;

	// Get and modify current options:

	tcgetattr (fd, &options) ;

	cfmakeraw   (&options) ;
	cfsetispeed (&options, myBaud) ;
	cfsetospeed (&options, myBaud) ;

	options.c_cflag |= (CLOCAL | CREAD) ;
	options.c_cflag &= ~PARENB ;
	options.c_cflag &= ~CSTOPB ;
	options.c_cflag &= ~CSIZE ;
	options.c_cflag |= CS8 ;
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG) ;
	options.c_oflag &= ~OPOST ;

	options.c_cc [VMIN]  =   0 ;
	options.c_cc [VTIME] = 100 ;	// Ten seconds (100 deciseconds)

	tcsetattr (fd, TCSANOW, &options) ;

	ioctl (fd, TIOCMGET, &status);

	status |= TIOCM_DTR ;
	status |= TIOCM_RTS ;

	ioctl (fd, TIOCMSET, &status);

	usleep (10000) ;	// 10mS

	return fd ;
}
void serialClose (const int fd)
{
	close (fd) ;
}


/*
 * serialPutchar:
 *	Send a single character to the serial port
 *********************************************************************************
 */

void serialPutchar (const int fd, const unsigned char c)
{
	write (fd, &c, 1) ;
}


/*
 * serialPuts:
 *	Send a string to the serial port
 *********************************************************************************
 */

void serialPuts (const int fd, const char *s)
{
	write (fd, s, strlen (s)) ;
}

/*
 * serialDataAvail:
 *	Return the number of bytes of data avalable to be read in the serial port
 *********************************************************************************
 */

int serialDataAvail (const int fd)
{
	int result ;

	if (ioctl (fd, FIONREAD, &result) == -1)
		return -1 ;

	return result ;
}


/*
 * serialGetchar:
 *	Get a single character from the serial device.
 *	Note: Zero is a valid character and this function will time-out after
 *	10 seconds.
 *********************************************************************************
 */

int serialGetchar (const int fd)
{
	uint8_t x ;

	if (read (fd, &x, 1) != 1)
		return -1 ;

	return ((int)x) & 0xFF ;
}
int get_serial_data(int fd, char *data, int len)
{
	int ret = 0;
	//	printf("File: %s, LINE: %d\n",__FILE__,__LINE__);
	while(serialDataAvail(fd))
	{
		*data = serialGetchar(fd);
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
int get_serial_data_hex(int fd, char *data, int len)
{
	int ret = 0;
	while(serialDataAvail(fd))
	{
		sprintf(data,"%02x",serialGetchar(fd));
		data+=2;
		ret++;
		if(ret>=len)
		{
			printf("ret>=len, %s, %d\n",__FILE__,__LINE__);
			break;
		}
	}
	return ret;
}

int clcd_test(int fd, char *data)
{
	//////////////////////////////////////////////////////
	serialPutchar(fd,0xA2);
	serialPuts(fd,data);
	//////////////////////////////////////////////////////
}

int clcd_init(int fd)
{
	serialPutchar(fd,0xA0);
	usleep(500000);
}

int clcd_setcursor(int fd, int cur_x, int cur_y)
{
	serialPutchar(fd,0xA1);
	serialPutchar(fd,cur_x);
	serialPutchar(fd,cur_y);
	usleep(100000);
}

int clcd_write(int fd, char *data)
{
	serialPutchar(fd,0xA2);
	serialPuts(fd,data);
}

int clcd_clear(int fd)
{
	serialPutchar(fd,0xA3);
	serialPutchar(fd,0x01);
}
int clcd_backlight_on(int fd)
{
	serialPutchar(fd,0xA5);
	serialPutchar(fd,0x01);
}
int clcd_backlight_off(int fd)
{
	serialPutchar(fd,0xA5);
	serialPutchar(fd,0x02);
}

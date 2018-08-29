/*
 * read_serial.c
 *
 *  Created on: Aug 29, 2018
 *      Author: felipe
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>

#include "read_serial.h"

int read_serial() {
	/**
	 * The argument flags must include one of the following access modes:
	 * O_RDONLY, O_WRONLY, or O_RDWR. These request opening the file
	 * read-only, write-only, or read/write, respectively.
	 */
	int sfd = open("/dev/serial0", O_RDONLY | O_NOCTTY);
	if (sfd == -1) {
		printf("Error no is : %d\n", errno);
		printf("Error description is : %s\n", strerror(errno));
	} else {
		printf("Successfully opened port /dev/serial0\n");
	}

	struct termios options;
	tcgetattr(sfd, &options);

	cfsetspeed(&options, B9600);
	cfmakeraw(&options);

	options.c_cflag &= ~CSTOPB;
	options.c_cflag |= CLOCAL;
	options.c_cflag |= CREAD;
	options.c_cc[VTIME] = 1;
	options.c_cc[VMIN] = 100;
	tcsetattr(sfd, TCSANOW, &options);

	char buf2[100];
	int bytes;
	ioctl(sfd, FIONREAD, &bytes);
	if (bytes != 0) {
		int count = read(sfd, buf2, 100);
	}

	printf("%s\n\r", buf2);

	close(sfd);
	printf("Successfully closed port /dev/serial0\n");

	return EXIT_SUCCESS;
}

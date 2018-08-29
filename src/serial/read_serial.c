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
	struct termios options;

	/**
	 * The argument flags must include one of the following access modes:
	 * O_RDONLY, O_WRONLY, or O_RDWR. These request opening the file
	 * read-only, write-only, or read/write, respectively.
	 */
	int sfd = open("/dev/serial0", O_RDWR | O_NOCTTY);
	if (sfd == -1) {
		printf("Error no is : %d\n", errno);
		printf("Error description is : %s\n", strerror(errno));
		return EXIT_FAILURE;
	} else {
		printf("Successfully opened port /dev/serial0\n");
	}

	tcgetattr(sfd, &options);

	cfsetspeed(&options, B9600); // set the baud rate to 9600
	cfmakeraw(&options);

	// Set up Serial Configuration
	options.c_cflag &= ~CSTOPB;
	options.c_cflag |= CLOCAL;
	options.c_cflag |= CREAD;
	options.c_cc[VTIME] = 1;
	options.c_cc[VMIN] = 100;

	// Apply configuration
	tcsetattr(sfd, TCSANOW, &options);

	// Attempt to write data
	char buf[] = "hello world";
	printf("Sending: %s\n", buf);
	int wcount = write(sfd, buf, strlen(buf));
	usleep(100000);

	if (wcount < 0) {
		perror("Write");
		return EXIT_FAILURE;
	} else {
		printf("Sent %d characters\n", wcount);
	}

	// Attempt to read data
	char buf2[100];
	int bytes;
	ioctl(sfd, FIONREAD, &bytes);
	// if (bytes != 0) {
	int rcount = read(sfd, buf2, sizeof(buf2));
	if (rcount < 0) {
		perror("Read");
		return EXIT_FAILURE;
	} else {
		printf("Received %d characters\n", rcount);
	}
	// buf2[count] = '\0';
	printf("Received: %s\n\r", buf2);
	// }

	close(sfd);
	printf("Successfully closed port /dev/serial0\n");

	return EXIT_SUCCESS;
}

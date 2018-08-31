/*
 * ultrasonicBCM2835.c
 *
 *  Created on: Aug 31, 2018
 *      Author: felipe
 */

// # include <bcm2835.h>
# include <stdio.h>
# include <time.h>
# include <stdlib.h>

#include "ultrasonicBCM2835.h"

//# define ECHO RPI_V2_GPIO_P1_03
//# define TRIG RPI_V2_GPIO_P1_05

int runUltrasonicBCM2835() {
	if (!bcm2835_init())
		return 1;

//	bcm2835_gpio_fsel(ECHO, BCM2835_GPIO_FSEL_INPT);
//	bcm2835_gpio_fsel(TRIG, BCM2835_GPIO_FSEL_OUTP);
//
//	time_t clockstart = 0;
//	time_t clockstop = 0;
//
//	bcm2835_gpio_write(ECHO, LOW);
//	delay(2);
//
//	printf("trigger\n");
//
//	bcm2835_gpio_write(TRIG, HIGH);
//	usleep(10);
//	bcm2835_gpio_write(TRIG, LOW);
//
//	printf("measure\n");
//
//	while (bcm2835_gpio_lev(ECHO) == 0) {
//		clockstart = time(NULL);
//	}
//
//	printf("B: %i\n", (int) clockstart);
//
//	while (bcm2835_gpio_lev(ECHO) == 1) {
//		clockstop = time(NULL);
//	}
//
//	printf("E: %i\n", (int) clockstop);
//
//	time_t delta = clockstop - clockstart;
//
//	printf("D: %i\n", delta);
//
//	double distance = (delta * 340) / 2;
//
//	printf("DISTANCE: %i\n", distance);
//
//	bcm2835_close();
	return 0;
}

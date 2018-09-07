/*
 * readall.c
 *
 * gcc readall.c -lbcm2835 -o readall
 *
 *  Created on: Sep 7, 2018
 *      Author: felipe
 */

#include <bcm2835.h>
#include <stdio.h>

#include "readall.h"

// Input on RPi pin 15 - GPIO 22
#define PIN_15 RPI_BPLUS_GPIO_J8_15
// Input on RPi pin 13 - GPIO 27
#define PIN_13 RPI_BPLUS_GPIO_J8_13

int read_all_gpio() {
	// If you call this, it will not actually access the GPIO
	// Use for testing
//    bcm2835_set_debug(1);
	if (!bcm2835_init())
		return 1;
	// Set RPI pin P1-13 to be an input
	bcm2835_gpio_fsel(PIN_13, BCM2835_GPIO_FSEL_INPT);
	//  with a pullup
	bcm2835_gpio_set_pud(PIN_13, BCM2835_GPIO_PUD_UP);
	// Blink

	int count = 0;
	while (count < 10) {
		// Read some data
		uint8_t value = bcm2835_gpio_lev(PIN_13);
		printf("read from pin 13: %d\n", value);

		// wait a bit
		delay(500);
		count++;
	}

	printf("\n");
	bcm2835_gpio_fsel(PIN_15, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(PIN_15, BCM2835_GPIO_PUD_UP);
	count = 0;
	while (count < 10) {
		// Read some data
		uint8_t value = bcm2835_gpio_lev(PIN_15);
		printf("read from pin 15: %d\n", value);

		// wait a bit
		delay(500);
		count++;
	}

	bcm2835_close();
	return 0;
}

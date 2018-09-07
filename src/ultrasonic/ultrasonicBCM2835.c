/*
 * ultrasonicBCM2835.c
 *
 *  Created on: Aug 31, 2018
 *      Author: felipe
 */

#include <bcm2835.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

#include "ultrasonicBCM2835.h"
#include "../utils/metrics.h"

/*
 * The pins here are defined when we use the HC-SR04 sensor connected to a AlphaBot2 with Raspberry Pi Zero.
 * If you connect the HC-SR04 sensor directly to a Raspberry Pi with resistors the pins might change.
 */

#define trig RPI_V2_GPIO_P1_15
#define echo RPI_V2_GPIO_P1_13

#define __STDC_FORMAT_MACROS

int run_HC_SR04_BCM2835() {
	clock_t cpu_start;
	// struct timeval user_start;
	int count = 1;
	int max = 0;

	printf("How many iterations do you want to scan [int]: ");
	scanf("%d", &max);
	while (count <= max) {
		printf("Iteration[%d of %d]\n", count, max);

		// gettimeofday(&user_start, NULL);
		// get_cpu_and_user_time(cpu_start, user_start, "preciseDistanceInches");

		cpu_start = clock();
		// float preInt = preciseDistanceInches(trig, echo); // if we measure the time between inches and centimeter functions the metric gets wrong
		float preCent = preciseDistanceCentimeters(trig, echo);
		get_cpu_time(cpu_start, "preciseDistance");

		// printf("Inches[%f] - ", preInt);
		printf("Centimeters[%f]\n\n", preCent);
		count++;
		delay(1000);
	}
	return 0;
}

/*
 *  This is a local subroutine function used in each method to
 *  initiate pulses out of the sensor and return the pulse with
 *  of the returned ultrasonic signal.
 *  Trigger - The GPIO pin attached to the trigger pin on the
 *            sensor.
 *  Echo    - The GPIO pin attached to the echo pin on the
 *            sensor.
 */
static uint64_t cyclePulse(int trigger, int echo) {
	if (!bcm2835_init())
		return 1;

	// Set RPi pin echo to be an input pin
	bcm2835_gpio_fsel(echo, BCM2835_GPIO_FSEL_INPT);
	// Set RPi pin P1-11 to be an output pin
	bcm2835_gpio_fsel(trigger, BCM2835_GPIO_FSEL_OUTP);

	// Declare the unsigned int timer variables to measure pulses
	uint64_t width, begin, start, end;
	int max = 80, check;

	begin = bcm2835_st_read();

	// Emit pulse for 10 microseconds
	bcm2835_gpio_write(trigger, HIGH); // Set trigger state HIGH
	bcm2835_delayMicroseconds(10);  // Wait 10 microseconds
	bcm2835_gpio_write(trigger, LOW);  // Set trigger state LOW

	// Infinite loop until a pulse is received
	while (bcm2835_gpio_lev(echo) == LOW && check < max) {
		start = bcm2835_st_read();
		check = (int) begin - start;
	}

	// Loop and delay for one microsecond until falling edge detected
	while (bcm2835_gpio_lev(echo) == HIGH) {
		bcm2835_delayMicroseconds(1);
	}
	// Record the ending time of the pulse to get the pulse width
	end = bcm2835_st_read();

	// Get the final with of the pulse
	width = end - start;

	//Close the bcm2835 bridge
	bcm2835_close();

	// Return the total width of the returned pulse
	return width;
}

/*
 * Returns a 6 decimal place precise value of the
 * distance in inches from the distance sensor.
 *
 * Trigger - The GPIO pin attached to the trigger pin on the sensor.
 * Echo    - The GPIO pin attached to the echo pin on the sensor.
 */
float preciseDistanceInches(int trigger, int echo) {
	return (float) cyclePulse(trigger, echo) / 144;
}

/*
 * Returns a 6 decimal place precise value of the
 * distance in centimeters from the distance sensor.
 *
 * Trigger - The GPIO pin attached to the trigger pin on the sensor.
 * Echo    - The GPIO pin attached to the echo pin on the sensor.
 */
float preciseDistanceCentimeters(int trigger, int echo) {
	return (float) cyclePulse(trigger, echo) / 55.5;
}

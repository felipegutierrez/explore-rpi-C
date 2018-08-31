/*
 * ultrasonicClient.c
 *
 *  Created on: Aug 31, 2018
 *      Author: felipe
 */

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#include "ultrasonicClient.h"

#define TRUE 1

// HC-SR04 ultrasonic sensor with 1 KΩ resisto and 2 KΩ resisto
// #define TRIG 5
// #define ECHO 6

// HC-SR04 ultrasonic sensor on AlphaBot2 Pi Zero
#define TRIG 22
#define ECHO 27

void setupUltrasonic() {
	wiringPiSetup();
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);

	//TRIG pin must start LOW
	digitalWrite(TRIG, LOW);
	delay(30);
}

int getCM() {
	//Send trig pulse
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(20);
	digitalWrite(TRIG, LOW);

	//Wait for echo start
	while (digitalRead(ECHO) == LOW)
		;

	//Wait for echo end
	long startTime = micros();
	while (digitalRead(ECHO) == HIGH)
		;
	long travelTime = micros() - startTime;

	//Get distance in cm
	int distance = travelTime / 58;

	return distance;
}

int runUltrasonicClient() {
	setupUltrasonic();

	printf("Distance: %dcm\n", getCM());

	return 0;
}

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

static volatile long startTimeUsec;
static volatile long endTimeUsec;
double speedOfSoundMetersPerSecond = 340.29;

void recordPulseLength() {
	startTimeUsec = micros();
	while (digitalRead(ECHO) == HIGH)
		;
	endTimeUsec = micros();
}

void setupUltrasonic() {
	wiringPiSetup();
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);

	// TRIG pin must start LOW
	// Initialize the sensor's trigger pin to low. If we don't pause
	// after setting it to low, sometimes the sensor doesn't work right.
	digitalWrite(TRIG, LOW);
	delay(500); // .5 seconds
}

int getCM() {
	// Send trig pulse
	// Triggering the sensor for 10 microseconds will cause it to send out
	// 8 ultrasonic (40Khz) bursts and listen for the echos.
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG, LOW);

	int now = micros();
	// Wait for echo start
	// The sensor will raise the echo pin high for the length of time that it took
	// the ultrasonic bursts to travel round trip.
	while (digitalRead(ECHO) == LOW && micros() - now < 30000);
		recordPulseLength();

	long travelTimeUsec = endTimeUsec - startTimeUsec;
	double distanceMeters = 100 * ((travelTimeUsec / 1000000.0) * 340.29) / 2;

//	//Wait for echo end
//	long startTime = micros();
//	while (digitalRead(ECHO) == HIGH)
//		;
//	long travelTime = micros() - startTime;
//
//	//Get distance in cm
//	int distance = travelTime * 34000 / 2;

	return distanceMeters * 100;
}

int runUltrasonicClient() {
	int count = 0;
	setupUltrasonic();

	while (count < 60) {
		printf("Distance: %dcm\n", getCM());
		count++;
	}
	return 0;
}

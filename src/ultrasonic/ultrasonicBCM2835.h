/*
 * ultrasonicBCM2835.h
 *
 *  Created on: Aug 31, 2018
 *      Author: felipe
 */

#ifndef ULTRASONIC_ULTRASONICBCM2835_H_
#define ULTRASONIC_ULTRASONICBCM2835_H_

int run_HC_SR04_BCM2835();

/*
 * Returns a 6 decimal place precise value of the
 * distance in inches from the distance sensor.
 * Trigger - The GPIO pin attached to the
 *           trigger pin on the sensor.
 * Echo    - The GPIO pin attached to the
 *           echo pin on the sensor.
 */
float preciseDistanceInches(int trigger, int echo);

/*
 * Returns a 6 decimal place precise value of the
 * distance in centimeters from the distance
 * sensor.
 * Trigger - The GPIO pin attached to the
 *           trigger pin on the sensor.
 * Echo    - The GPIO pin attached to the
 *           echo pin on the sensor.
 */
float preciseDistanceCentimeters(int trigger, int echo);

#endif /* ULTRASONIC_ULTRASONICBCM2835_H_ */

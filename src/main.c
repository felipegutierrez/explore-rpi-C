/*
 * main.c
 *
 * Compiling on Debian
 * gcc main.c multithread/testMultiThread.c gps/gpsClient.c -Wall -Wcomment -lm -lgps -lpthread -o main
 *
 *  Created on: Aug 24, 2018
 *      Author: felipe
 */

#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "multithread/testMultiThread.h"
#include "gps/gpsClient.h"

int main(int argv, char** argc) {

	int choice = -1;

	while (choice != 0) {
		menu();
		scanf("%d", &choice);

		switch (choice) {
		case 0:
			printf("\n");
			printf("Exiting....\n");
			break;
		case 1:
			printf("\n");
			runMultiThread();
			choice = 0;
			break;
		case 2:
			printf("\n");
			runGpsStreamClient();
			choice = 0;
			break;
		default:
			printf("Option not valid. Please try again.\n");
		}
	}

	printf("Exit\n");
	exit(0);
	return 0;
}

void menu() {
	printf(" 0  - Exit\n");
	printf(" 1  - MultiThread test\n");
	printf(" 2  - Gps stream test\n");
	printf("Please choose your application: ");
}

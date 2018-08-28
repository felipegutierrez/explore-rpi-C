/*
 * metrics.c
 *
 *  Created on: Aug 27, 2018
 *      Author: felipe
 */

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <math.h>

#include "metrics.h"

void get_cpu_time(clock_t t, char* func) {
	t = clock() - t;
	double time_taken = ((double) t) / CLOCKS_PER_SEC; // in seconds
	printf("CPU  time [%s] %.10f seconds.\n", func, time_taken);
}

void get_user_time(struct timeval start, char* func) {
	struct timeval stop;
	gettimeofday(&stop, NULL);
	double sec = stop.tv_sec - start.tv_sec;
	double micros = (((sec * 1000000) + stop.tv_usec) - (start.tv_usec))
			/ 1000000;
	// printf("User time [%s] %.10d seconds.\n", func, sec);
	printf("User time [%s] %.10f seconds.\n", func, micros);
}

void print_current_time() {
	char buffer[100];
	int millisec;
	struct tm* tm_info;
	struct timeval tv;

	gettimeofday(&tv, NULL);

	millisec = lrint(tv.tv_usec / 1000.0); // Round to nearest millisec
	if (millisec >= 1000) { // Allow for rounding up to nearest second
		millisec -= 1000;
		tv.tv_sec++;
	}

	tm_info = localtime(&tv.tv_sec);

	strftime(buffer, 100, "  Current time %Y-%m-%d %H:%M:%S", tm_info);
	printf("%s.%03d \n", buffer, millisec);
}

void print_time(time_t seconds) {
	char buffer[100];
	int millisec = (seconds - floor(seconds)) / 1000.0;
	if (millisec >= 1000) { // Allow for rounding up to nearest second
		millisec -= 1000;
	}
	strftime(buffer, 100, "  GPS time     %Y-%m-%d %H:%M:%S",
			localtime(&seconds));
	printf("%s.%03d \n", buffer, millisec);
}

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

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

void get_cpu_and_user_time(clock_t start_cpu, struct timeval start_user,
		char* func_name) {
	get_cpu_time(start_cpu, func_name);
	get_user_time(start_user, func_name);
}

void get_cpu_time(clock_t start_cpu, char* func_name) {
	clock_t t = clock() - start_cpu;
	double time_taken = (((double) t) / CLOCKS_PER_SEC) * 1000; // milliseconds
	printf("CPU  time [%s] %.10f milliseconds.\n", func_name, time_taken);
}

void get_user_time(struct timeval start_user, char* func_name) {
	struct timeval stop;
	gettimeofday(&stop, NULL);
	double start_ms = (double) start_user.tv_sec * 1000000
			+ (double) start_user.tv_usec;
	double stop_ms = (double) stop.tv_sec * 1000000 + (double) stop.tv_usec;
	double millisec = ((double) stop_ms - (double) start_ms) / 1000;
	printf("User time [%s] %.10f milliseconds.\n", func_name, millisec);
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

	long ms; // Milliseconds
	struct timespec spec;

	clock_gettime(CLOCK_REALTIME, &spec);
	ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
	if (ms > 999) {
		ms = 0;
	}

	strftime(buffer, 100, "  GPS time     %Y-%m-%d %H:%M:%S",
			localtime(&seconds));
	printf("%s.%03ld \n", buffer, ms);
}

/*
 * metrics.c
 *
 *  Created on: Aug 27, 2018
 *      Author: felipe
 */

#include <stdio.h>
#include <time.h>

#include "metrics.h"

void get_metric(clock_t t, char* func) {
	t = clock() - t;
	double time_taken = ((double) t) / CLOCKS_PER_SEC; // in seconds
	printf("[%s] %f seconds.\n", func, time_taken);
}


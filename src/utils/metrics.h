/*
 * metrics.h
 *
 *  Created on: Aug 27, 2018
 *      Author: felipe
 */

#ifndef UTILS_METRICS_H_
#define UTILS_METRICS_H_

void get_cpu_time(clock_t t, char* func);
void get_user_time(struct timeval start, char* func);
void print_current_time();
void print_time(time_t seconds);

#endif /* UTILS_METRICS_H_ */

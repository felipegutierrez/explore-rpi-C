/*
 * metrics.h
 *
 *  Created on: Aug 27, 2018
 *      Author: felipe
 */

#ifndef UTILS_METRICS_H_
#define UTILS_METRICS_H_

void get_cpu_time(clock_t start_cpu, char* func_name);
void get_user_time(struct timeval start_user, char* func_name);
void get_cpu_and_user_time(clock_t start_cpu, struct timeval start_user,
		char* func_name);
void print_current_time();
void print_time(time_t seconds);

#endif /* UTILS_METRICS_H_ */

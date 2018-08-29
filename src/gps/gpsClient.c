/*
 * gpsClient.c
 *
 * command line to compile the source code
 * # gcc -o gpsClient gpsClient.cpp -lm -lgps
 *
 *  Created on: Aug 22, 2018
 *      Author: felipe
 */

#include <gps.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>

#include "gpsClient.h"
#include "../utils/metrics.h"

int runGpsStreamClient() {
	int rc;
	int count = 0;
	clock_t cpu_start;
	struct timeval user_start;
	struct gps_data_t gps_data;

	gettimeofday(&user_start, NULL);
	cpu_start = clock();
	if ((rc = gps_open("localhost", "2947", &gps_data)) == -1) {
		printf("code: %d, reason: %s\n", rc, gps_errstr(rc));
		return EXIT_FAILURE;
	}
	get_cpu_and_user_time(cpu_start, user_start, "gps_open");

	gettimeofday(&user_start, NULL);
	cpu_start = clock();
	gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);
	get_cpu_and_user_time(cpu_start, user_start, "gps_stream");

	while (count < 60) {

		gettimeofday(&user_start, NULL);
		cpu_start = clock();
		/* wait for 2 second to receive data */
		if (gps_waiting(&gps_data, 20000000)) {
			get_cpu_and_user_time(cpu_start, user_start, "gps_waiting");

			gettimeofday(&user_start, NULL);
			cpu_start = clock();
			int rc = gps_read(&gps_data);
			get_cpu_and_user_time(cpu_start, user_start, "gps_read");

			/* read data */
			if (rc == -1) {
				printf(
						"error occurred reading gps data. code: %d, reason: %s\n",
						rc, gps_errstr(rc));
			} else {

				/* Display data from the GPS receiver. */
				double lat = gps_data.fix.latitude;
				double lon = gps_data.fix.longitude;
				double alt = gps_data.fix.altitude;
				double speed = gps_data.fix.speed;
				double climb = gps_data.fix.climb;
				int status = gps_data.status;
				int mode = gps_data.fix.mode;
				time_t seconds = (time_t) gps_data.fix.time;

				/**
				 * MODE_NOT_SEEN	0	mode update not seen yet
				 * MODE_NO_FIX		1	none
				 * MODE_2D  		2	good for latitude/longitude
				 * MODE_3D  		3	good for altitude/climb too
				 */
				if ((status == STATUS_FIX)
						&& (mode == MODE_2D || mode == MODE_3D)
						&& !isnan(lat) && !isnan(lon)) {
					printf("GPS data OK - ");
					printf("status[%d], ", status);
					printf("mode[%d], ", mode);
					printf("latitude[%f], ", lat);
					printf("longitude[%f], ", lon);
					printf("altitude[%f], ", alt);
					printf("speed[%f], ", speed);
					printf("v speed[%f]\n", climb);
					print_time(seconds);
					print_current_time();
					printf("\n");
				} else {
					printf("GPS data NOK.\n");
				}
			}
		} else {
			get_cpu_and_user_time(cpu_start, user_start, "gps_waiting");
			printf(
					"counter[%d]. Timeout to retrieve data from gpsd. Maybe increase gps_waiting.\n",
					count);
		}
		count++;
		// sleep(1);
	}

	/* When you are done... */
	gps_stream(&gps_data, WATCH_DISABLE, NULL);
	gps_close(&gps_data);

	return EXIT_SUCCESS;
}


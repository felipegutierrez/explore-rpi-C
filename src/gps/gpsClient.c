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
	clock_t cpu_t;
	struct timeval user_t;
	struct gps_data_t gps_data;

	gettimeofday(&user_t, NULL);
	cpu_t = clock();
	if ((rc = gps_open("localhost", "2947", &gps_data)) == -1) {
		printf("code: %d, reason: %s\n", rc, gps_errstr(rc));
		return EXIT_FAILURE;
	}
	get_cpu_time(cpu_t, "gps_open");
	get_user_time(user_t, "gps_open");

	gettimeofday(&user_t, NULL);
	cpu_t = clock();
	gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);
	get_cpu_time(cpu_t, "gps_stream");
	get_user_time(user_t, "gps_stream");

	while (count < 60) {
		/* wait for 0.1 second to receive data */
		if (gps_waiting(&gps_data, 100000)) {

			gettimeofday(&user_t, NULL);
			cpu_t = clock();
			int rc = gps_read(&gps_data);
			get_cpu_time(cpu_t, "gps_read");
			get_user_time(user_t, "gps_read");

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
				time_t seconds = (time_t) gps_data.fix.time;
				int status = gps_data.status;
				int mode = gps_data.fix.mode;

				/**
				 * MODE_NOT_SEEN	0	mode update not seen yet
				 * MODE_NO_FIX		1	none
				 * MODE_2D  		2	good for latitude/longitude
				 * MODE_3D  		3	good for altitude/climb too
				 */
				printf("status[%d], ", status);
				printf("mode[%d], ", mode);
				printf("latitude[%f], ", lat);
				printf("longitude[%f], ", lon);
				printf("altitude[%f], ", alt);
				printf("speed[%f], ", speed);
				printf("v speed[%f], ", climb);
				printf("Time[%s].", ctime(&seconds));

				if ((status == STATUS_FIX)
						&& (mode == MODE_2D || mode == MODE_3D)
						&& !isnan(lat) && !isnan(lon)) {
					printf(" GPS data OK.\n");
				} else {
					printf(" GPS data NOK.\n");
				}
			}
		} else {
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


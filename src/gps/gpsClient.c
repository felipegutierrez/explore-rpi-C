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

#include "gpsClient.h"

int runGpsStreamClient() {
	int rc;
	int count = 0;
	clock_t t;

	struct gps_data_t gps_data;
	t = clock();
	if ((rc = gps_open("localhost", "2947", &gps_data)) == -1) {
		printf("code: %d, reason: %s\n", rc, gps_errstr(rc));
		return EXIT_FAILURE;
	}
	t = clock() - t;
	double time_taken = ((double) t) / CLOCKS_PER_SEC; // in seconds
	printf("gps_open() took %f seconds to execute \n", time_taken);

	t = clock();
	gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);
	t = clock() - t;
	time_taken = ((double) t) / CLOCKS_PER_SEC; // in seconds
	printf("gps_stream() took %f seconds to execute \n", time_taken);

	while (count < 60) {
		/* wait for 1 second to receive data */
		if (gps_waiting(&gps_data, 1000000)) {
			/* read data */
			if ((rc = gps_read(&gps_data)) == -1) {
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
				double t = gps_data.fix.time; // EDIT: Replaced tv.tv_sec with gps_data.fix.time
				int status = gps_data.status;
				int mode = gps_data.fix.mode;

				/**
				 * MODE_NOT_SEEN	0	mode update not seen yet
				 * MODE_NO_FIX		1	none
				 * MODE_2D  		2	good for latitude/longitude
				 * MODE_3D  		3	good for altitude/climb too
				 */
				printf("status: %d - ", status);
				printf("mode: %d - ", mode);
				printf("latitude: %f - ", lat);
				printf("longitude: %f - ", lon);
				printf("altitude: %f - ", alt);
				printf("speed: %f - ", speed);
				printf("vertical speed: %f - ", climb);
				printf("timestamp: %f - ", t);
				printf("%d:%d:%d", (int) (t / 3600), (int) (t / 60), (int) t);

				if ((status == STATUS_FIX)
						&& (mode == MODE_2D || mode == MODE_3D)
						&& !isnan(lat) && !isnan(lon)) {
					//gettimeofday(&tv, NULL); EDIT: tv.tv_sec isn't actually the timestamp!
					printf(" =) GPS data correctly received\n");
				} else {
					printf(" =( NO GPS data received\n");
				}
			}
		} else {
			printf("Timeout to retrieve data from gpsd.");
		}
		count++;
		sleep(1);
	}

	/* When you are done... */
	gps_stream(&gps_data, WATCH_DISABLE, NULL);
	gps_close(&gps_data);

	return EXIT_SUCCESS;
}

int runGpsCommanClient() {
	int rc;
	int count = 0;
//	char *fmsg = "?WATCH={\"nmea\":true,\"pps\":true}\r\n";
//	char *fmsg = "?WATCH={\"raw\":2,\"pps\":true}\r\n";
//	char *fmsg = "?WATCH={\"nmea\":true,\"pps\":true,\"device\":\"/dev/serial0\"}\r\n";
	char *fmsg = "?WATCH={\"raw\":2,\"pps\":true,\"device\":\"/dev/serial0\"}\r\n";
	struct gps_data_t gps_data;

	if ((rc = gps_open("localhost", "2947", &gps_data)) == -1) {
		printf("code: %d, reason: %s\n", rc, gps_errstr(rc));
		return EXIT_FAILURE;
	}

	while (count < 60) {
		printf("command GPS sensor: %s\n", fmsg);
		if (gps_send(&gps_data, fmsg) == -1) {
			(void) fprintf(stderr, "test_libgps: gps send error: %d, %s\n",
			errno, gps_errstr(errno));
		}
		/* wait for 1 second to receive data */
		if (gps_waiting(&gps_data, 1000000)) {
			/* read data */
			if ((rc = gps_read(&gps_data)) == -1) {
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
				double t = gps_data.fix.time; // EDIT: Replaced tv.tv_sec with gps_data.fix.time
				int status = gps_data.status;
				int mode = gps_data.fix.mode;

				printf("status: %d - ", status);
				printf("mode: %d - ", mode);
				printf("latitude: %f - ", lat);
				printf("longitude: %f - ", lon);
				printf("altitude: %f - ", alt);
				printf("speed: %f - ", speed);
				printf("vertical speed: %f - ", climb);
				printf("timestamp: %f - ", t);
				printf("%d:%d:%d", (int) (t / 3600), (int) (t / 60), (int) t);

				if ((status == STATUS_FIX)
						&& (mode == MODE_2D || mode == MODE_3D)
						&& !isnan(lat) && !isnan(lon)) {
					//gettimeofday(&tv, NULL); EDIT: tv.tv_sec isn't actually the timestamp!
					printf(" =) GPS data correctly received\n");
				} else {
					printf(" =( NO GPS data received\n");
				}
			}
		} else {
			printf("Timeout to retrieve data from gpsd.");
		}
		count++;
		sleep(1);
	}

	/* When you are done... */
	gps_close(&gps_data);

	return EXIT_SUCCESS;
}

/*
 * gpsClient.cpp
 *
 * command line to compile the source code
 * # gcc -o gpsClient gpsClient.cpp -lm -lgps
 *
 *  Created on: Aug 22, 2018
 *      Author: felipe
 */

#include <gps.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main(int argv, char** argc) {
	int rc;
	struct timeval tv;

	struct gps_data_t gps_data;
	if ((rc = gps_open("localhost", "2947", &gps_data)) == -1) {
		printf("code: %d, reason: %s\n", rc, gps_errstr(rc));
		return EXIT_FAILURE;
	}
	gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);

	while (true) {
		/* wait for 2 seconds to receive data */
		if (gps_waiting(&gps_data, 2000000)) {
			/* read data */
			if ((rc = gps_read(&gps_data)) == -1) {
				printf("error occured reading gps data. code: %d, reason: %s\n",
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
				 * MODE_NOT_SEEN	0	/* mode update not seen yet
				 * MODE_NO_FIX		1	/* none
				 * MODE_2D  		2	/* good for latitude/longitude
				 * MODE_3D  		3	/* good for altitude/climb too
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
		}
		sleep(3);
	}

	/* When you are done... */
	gps_stream(&gps_data, WATCH_DISABLE, NULL);
	gps_close(&gps_data);

	return EXIT_SUCCESS;
}


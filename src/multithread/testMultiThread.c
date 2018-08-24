/*
 * testMultiThread.c
 *
 *  Created on: Aug 22, 2018
 *      Author: felipe
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#include "testMultiThread.h"

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void *threadTask(void *vargp) {
	clock_t t = clock();
	for (int i = 0; i < 100000; i++) {
		pthread_mutex_lock(&mutex1);
		counter++;
		sleep(1 / 1000000000); // dividing by 1,000,000,000 to use nanosecond
		pthread_mutex_unlock(&mutex1);
	}
	t = clock() - t;
	double time_taken = ((double) t) / CLOCKS_PER_SEC; // in seconds
	printf(
			"Counter value: %d from process ID: %d took %f seconds to execute.\n",
			counter, (int) getpid(), time_taken);
	return EXIT_SUCCESS;
}

int runMultiThread() {
	int rc1, rc2, rc3;
	pthread_t thread1, thread2, thread3;

	// create independent threads each of which will execute the function threadTask
	if ((rc1 = pthread_create(&thread1, NULL, &threadTask, NULL))) {
		printf("Thread creation failed: %d\n", rc1);
	}
	if ((rc2 = pthread_create(&thread2, NULL, &threadTask, NULL))) {
		printf("Thread creation failed: %d\n", rc2);
	}
	if ((rc3 = pthread_create(&thread3, NULL, &threadTask, NULL))) {
		printf("Thread creation failed: %d\n", rc3);
	}
	printf("From main process ID: %d\n", (int) getpid());

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	printf("From main process ID: %d\n", (int) getpid());
	return EXIT_SUCCESS;
}

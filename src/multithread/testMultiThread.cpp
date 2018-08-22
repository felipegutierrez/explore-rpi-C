/*
 * testMultiThread.cpp
 *
 *  Created on: Aug 22, 2018
 *      Author: felipe
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void *aThread(void*) {
	for (int i = 0; i < 10000000; i++) {
		pthread_mutex_lock(&mutex1);
		counter++;
		pthread_mutex_unlock(&mutex1);
	}
	printf("Counter value: %d from process ID: %d\n", counter, (int) getpid());
	return 0;
}

int main(int argv, char** argc) {
	std::cout << "Hello World!" << std::endl;
	int rc1, rc2, rc3;
	pthread_t thread1, thread2, thread3;

	// create independent threads each of which will execute the function aThread
	if ((rc1 = pthread_create(&thread1, NULL, &aThread, NULL))) {
		printf("Thread creation failed: %d\n", rc1);
	}
	if ((rc2 = pthread_create(&thread2, NULL, &aThread, NULL))) {
		printf("Thread creation failed: %d\n", rc2);
	}
	if ((rc3 = pthread_create(&thread3, NULL, &aThread, NULL))) {
		printf("Thread creation failed: %d\n", rc3);
	}
	printf("From main process ID: %d\n", (int) getpid());

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	printf("From main process ID: %d\n", (int) getpid());
	exit(EXIT_SUCCESS);
	return 0;
}

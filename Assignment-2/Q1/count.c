#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define INT_MAX 2147483647
#define BILLION 1000000000L;


void *countFIFO(void *arg) {
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();
	int *priority = (int *) arg;

	struct sched_param param;
	param.sched_priority = *priority;
	pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
	for (int i = 0; i < INT_MAX; i++) {
	}
	for (int i = 0; i < INT_MAX; i++) {
	}

	end_t = clock();
	total_t = (double) (end_t - start_t) / CLOCKS_PER_SEC;
	printf("FIFO (priority=%d): %lfs\n", *priority, total_t);

	return NULL;
}

void *countRR(void *arg) {
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();
	int *priority = (int *) arg;
	struct sched_param param;
	param.sched_priority = *priority;
	pthread_setschedparam(pthread_self(), SCHED_RR, &param);
	for (int i = 0; i < INT_MAX; i++) {
	}
	for (int i = 0; i < INT_MAX; i++) {
	}

	end_t = clock();
	total_t = (double) (end_t - start_t) / CLOCKS_PER_SEC;
	printf("RR (priority=%d): %lfs\n", *priority, total_t);

	return NULL;
}

void *countOTHER(void *arg) {
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

	struct sched_param param;
	pthread_setschedparam(pthread_self(), SCHED_OTHER, &param);
	for (int i = 0; i < INT_MAX; i++) {
	}
	for (int i = 0; i < INT_MAX; i++) {
	}

	end_t = clock();
	total_t = (double) (end_t - start_t) / CLOCKS_PER_SEC;
	printf("OTHER: %lfs\n", total_t);

	return NULL;
}

int main() {
	pthread_t ThrA;
	pthread_t ThrB;
	pthread_t ThrC;

	int a = 0, b = 49, c = 99;

	pthread_create(&ThrA, NULL, &countOTHER, NULL);
	pthread_join(ThrA, NULL);
	pthread_create(&ThrB, NULL, &countRR, (void *) &a);
	pthread_join(ThrB, NULL);
	pthread_create(&ThrB, NULL, &countRR, (void *) &b);
	pthread_join(ThrB, NULL);
	pthread_create(&ThrB, NULL, &countRR, (void *) &c);
	pthread_join(ThrB, NULL);
	pthread_create(&ThrC, NULL, &countFIFO, (void *) &a);
	pthread_join(ThrC, NULL);
	pthread_create(&ThrC, NULL, &countFIFO, (void *) &b);
	pthread_join(ThrC, NULL);
	pthread_create(&ThrC, NULL, &countFIFO, (void *) &c);
	pthread_join(ThrC, NULL);

	printf("Exiting the program...\n");
	return 0;
}

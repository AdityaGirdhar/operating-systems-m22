#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define INT_MAX 2147483647
#define BILLION 1000000000L;

void *countFIFO(void *arg) {
	struct timespec start, stop;
	double accum;
	clock_gettime(CLOCK_REALTIME, &start);
	int *priority = (int *) arg;

	struct sched_param param;
	param.sched_priority = *priority;
	pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
	for (int i = 0; i < INT_MAX; i++) {
	}
	for (int i = 0; i < INT_MAX; i++) {
	}

	clock_gettime(CLOCK_REALTIME, &stop);
	accum = (stop.tv_sec - start.tv_sec) + (double) (stop.tv_nsec - start.tv_nsec)/BILLION;
	printf("FIFO (priority=%d): %lfs\n", *priority, accum);

	return NULL;
}

void *countRR(void *arg) {
	struct timespec start, stop;
	double accum;
	clock_gettime(CLOCK_REALTIME, &start);
	int *priority = (int *) arg;

	struct sched_param param;
	param.sched_priority = *priority;
	pthread_setschedparam(pthread_self(), SCHED_RR, &param);
	for (int i = 0; i < INT_MAX; i++) {
	}
	for (int i = 0; i < INT_MAX; i++) {
	}

	clock_gettime(CLOCK_REALTIME, &stop);
	accum = (stop.tv_sec - start.tv_sec) + (double) (stop.tv_nsec - start.tv_nsec)/BILLION;
	printf("RR (priority=%d): %lfs\n", *priority, accum);

	return NULL;
}

void *countOTHER(void *arg) {
	struct timespec start, stop;
	double accum;
	clock_gettime(CLOCK_REALTIME, &start);

	struct sched_param param;
	pthread_setschedparam(pthread_self(), SCHED_OTHER, &param);
	for (int i = 0; i < INT_MAX; i++) {
	}
	for (int i = 0; i < INT_MAX; i++) {
	}

	clock_gettime(CLOCK_REALTIME, &stop);
	accum = (stop.tv_sec - start.tv_sec) + (double) (stop.tv_nsec - start.tv_nsec)/BILLION;
	printf("OTHER: %lfs\n", accum);

	return NULL;
}

int main() {
	pthread_t ThrA;
	pthread_t ThrB1; pthread_t ThrB2; pthread_t ThrB3;
	pthread_t ThrC1; pthread_t ThrC2; pthread_t ThrC3;

	int a = 0, b = 49, c = 99;

	pthread_create(&ThrA, NULL, &countOTHER, NULL);
	pthread_create(&ThrB1, NULL, &countRR, (void *) &a);
	pthread_create(&ThrB2, NULL, &countRR, (void *) &b);
	pthread_create(&ThrB3, NULL, &countRR, (void *) &c);
	pthread_create(&ThrC1, NULL, &countFIFO, (void *) &a);
	pthread_create(&ThrC2, NULL, &countFIFO, (void *) &b);
	pthread_create(&ThrC3, NULL, &countFIFO, (void *) &c);
	
	pthread_join(ThrA, NULL);
	pthread_join(ThrB1, NULL);
	pthread_join(ThrB2, NULL);
	pthread_join(ThrB3, NULL);
	pthread_join(ThrC1, NULL);
	pthread_join(ThrC2, NULL);	
	pthread_join(ThrC3, NULL);

	printf("Exiting the program...\n");
	return 0;
}

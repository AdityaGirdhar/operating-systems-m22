#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sched.h>

#define BILLION 1000000000L;

void callFIFO() {
	struct timespec start, stop;
	double time;
	struct sched_param param;

	int rc = fork();
	if (!rc) {
		param.sched_priority = 49;
		sched_setscheduler(getpid(), SCHED_FIFO, &param);
		execl("./test.sh", "./test.sh", NULL);
	}
	clock_gettime(CLOCK_REALTIME, &start);
	wait(NULL);
	clock_gettime(CLOCK_REALTIME, &stop);
	time = (stop.tv_sec - start.tv_sec) + (double) (stop.tv_nsec - start.tv_nsec) / BILLION;
	printf("FIFO time: %lf\n", time);
}

void callRR() {
	struct timespec start, stop;
	double time;
	struct sched_param param;

	int rc = fork();
	if (!rc) {
		param.sched_priority = 49;
		sched_setscheduler(getpid(), SCHED_RR, &param);
		execl("./test.sh", "./test.sh", NULL);
	}
	clock_gettime(CLOCK_REALTIME, &start);
	wait(NULL);
	clock_gettime(CLOCK_REALTIME, &stop);
	time = (stop.tv_sec - start.tv_sec) + (double) (stop.tv_nsec - start.tv_nsec) / BILLION;
	printf("RR time: %lf\n", time);
}

void callOTHER() {
	struct timespec start, stop;
	double time;
	struct sched_param param;

	int rc = fork();
	if (!rc) {
		param.sched_priority = 0;
		sched_setscheduler(getpid(), SCHED_OTHER, &param);
		execl("./test.sh", "./test.sh", NULL);
	}
	clock_gettime(CLOCK_REALTIME, &start);
	wait(NULL);
	clock_gettime(CLOCK_REALTIME, &stop);
	time = (stop.tv_sec - start.tv_sec) + (double) (stop.tv_nsec - start.tv_nsec) / BILLION;
	printf("OTHER time: %lf\n", time);
}

int main() {
	int pid1, pid2, pid3;
	pid1 = fork();

	if (!pid1) {
		callRR();
	} else {
		pid2 = fork();
		if (!pid2) {
			callFIFO();
		} else {
			pid3 = fork();
			if (!pid3) {
				callOTHER();
			}
		}
	}
	wait(NULL);
	wait(NULL);
	wait(NULL);
}



#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define INT_MAX 2147483647
#define BILLION 1000000000L;


int main() {
	int id1, id2, id3;
	clock_t start_t, end_t;
	double total_t;
	
	id1 = fork();
	if (id1 == 0) {
		// first child runs here
	}
	else {
		start_t = clock();
		wait();
		
		id2 = fork();
		if (id2 == 0) {
			// second child
		}
		else {
			id3 = fork();
			if (id3 == 0) {
				// third child
			}
			else {
				
			}
		}
	}
	
	return 0;
}

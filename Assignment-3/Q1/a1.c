#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void thinking(int p) {
	printf("Philosopher %d is thinking\n", p);
}
void goingToPickNextFork(int p) {
	printf("Philosopher %d is going to pick up the fork at their next index\n", p);
}
void pickedUpNextFork(int p) {
	printf("Philosopher %d has picked up the fork at their next index\n", p);
}
void goingToPickCurrentFork(int p) {
	printf("Philosopher %d is going to pick up the fork at their current index\n", p);
}
void pickedUpCurrentFork(int p) {
	printf("Philosopher %d has picked up the fork at their current index\n", p);
}
void eating(int p) {
	printf("Philosopher %d is eating\n", p);
}
void doneEating(int p) {
	printf("Philosopher %d is done eating\n", p);
}
void goingToPutDownNextFork(int p) {
	printf("Philosopher %d is going to put down the fork at their next index\n", p);
}
void putDownNextFork(int p) {
	printf("Philosopher %d has put down the fork at their next index\n", p);
}
void goingToPutDownCurrentFork(int p) {
	printf("Philosopher %d is going to put down the fork at their current index\n", p);
}
void putDownCurrentFork(int p) {
	printf("Philosopher %d has put down the fork at their current index\n", p);
}

void *work(void *num) {
	int p = (int) num;
	if (p%2) {
		thinking(p);
		goingToPickNextFork(p);
		pickedUpNextFork(p);
		goingToPickCurrentFork(p);
		pickedUpCurrentFork(p);
		eating(p);
		doneEating(p);
		goingToPutDownNextFork(p);
		putDownNextFork(p);
		goingToPutDownCurrentFork(p);
		putDownCurrentFork(p);
	} else {
		thinking(p);
		goingToPickCurrentFork(p);
		pickedUpCurrentFork(p);
		goingToPickNextFork(p);
		pickedUpNextFork(p);
		eating(p);
		doneEating(p);
		goingToPutDownCurrentFork(p);
		putDownCurrentFork(p);
		goingToPutDownNextFork(p);
		putDownNextFork(p);
	}
}

int main() {
	pthread_t threads[5];

	while (1) {
		// Strict ordering
		for (int i = 0; i < 5; i++) {
			pthread_create(&threads[i], NULL, work, (void *) i);
			pthread_join(threads[i], NULL);
		}
	} 
}

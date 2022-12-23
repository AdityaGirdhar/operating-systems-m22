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
void goingToPickUpSauceBowl(int p) {
	printf("Philosopher %d is going to pick up a sauce bowl\n", p);
}
void pickedUpSauceBowl(int p) {
	printf("Philosopher %d has picked up a sauce bowl\n", p);
}
void goingToPutDownSauceBowl(int p) {
	printf("Philosopher %d is going to put down their sauce bowl\n", p);
}
void putDownSauceBowl(int p) {
	printf("Philosopher %d has put down their sauce bowl\n", p);
}

void *work(void *num) {
	int p = (int) num;
		if (p%2) {
			thinking(p);
			goingToPickNextFork(p);
			pickedUpNextFork(p);
			goingToPickCurrentFork(p);
			pickedUpCurrentFork(p);
			goingToPickUpSauceBowl(p);
			pickedUpSauceBowl(p);
			eating(p);
			doneEating(p);
			goingToPutDownNextFork(p);
			putDownNextFork(p);
			goingToPutDownCurrentFork(p);
			putDownCurrentFork(p);
			goingToPutDownSauceBowl(p);
			putDownSauceBowl(p);
		} else {
			thinking(p);
			goingToPickCurrentFork(p);
			pickedUpCurrentFork(p);
			goingToPickNextFork(p);
			pickedUpNextFork(p);
			goingToPickUpSauceBowl(p);
			pickedUpSauceBowl(p);
			eating(p);
			doneEating(p);
			goingToPutDownCurrentFork(p);
			putDownCurrentFork(p);
			goingToPutDownNextFork(p);
			putDownNextFork(p);
			goingToPutDownSauceBowl(p);
			putDownSauceBowl(p);
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

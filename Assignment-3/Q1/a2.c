#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t globalSemArray[5];

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
	while (1) {
		if (p%2) {
			thinking(p);
			goingToPickNextFork(p);
			sem_wait(&globalSemArray[(p+1)%5]);
			pickedUpNextFork(p);
			goingToPickCurrentFork(p);
			sem_wait(&globalSemArray[p]);
			pickedUpCurrentFork(p);
			eating(p);
			doneEating(p);
			goingToPutDownNextFork(p);
			sem_post(&globalSemArray[(p+1)%5]);
			putDownNextFork(p);
			goingToPutDownCurrentFork(p);
			sem_post(&globalSemArray[p%5]);
			putDownCurrentFork(p);
		} else {
			thinking(p);
			goingToPickCurrentFork(p);
			sem_wait(&globalSemArray[p]);
			pickedUpCurrentFork(p);
			goingToPickNextFork(p);
			sem_wait(&globalSemArray[(p+1)%5]);
			pickedUpNextFork(p);
			eating(p);
			doneEating(p);
			goingToPutDownCurrentFork(p);
			sem_post(&globalSemArray[p%5]);
			putDownCurrentFork(p);
			goingToPutDownNextFork(p);
			sem_post(&globalSemArray[(p+1)%5]);
			putDownNextFork(p);
		}
	}
}

int main() {
	pthread_t threads[5];
	
	for (int i = 0; i < 5; i++) sem_init(&globalSemArray[i], 0, 1);
	for (int i = 0; i < 5; i++) pthread_create(&threads[i], NULL, work, (void *) i);
	for (int i = 0; i < 5; i++) pthread_join(threads[i], NULL);
}

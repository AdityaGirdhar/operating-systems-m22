#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]) {
	time_t n;
	time(&n);

	if (argc >= 3 && !strcmp(argv[1], "-d")) {
		if (!strcmp(argv[2], "today")) {
			printf("%s", ctime(&n));
		} else if (!strcmp(argv[2], "now")) {
			printf("%s", ctime(&n));
		}
		else if (!strcmp(argv[2], "tomorrow")) {
			n += 86400;
			printf("%s", ctime(&n));
		} else if (!strcmp(argv[2], "yesterday")) {
			n -= 86400;
			printf("%s", ctime(&n));
		} else {
			printf("date: invalid identifier '%s'\n", argv[2]);
		}
	} else if (argc >= 2 && !strcmp(argv[1], "-u")) {
		n -= 19800;
		printf("UTC: ");
		printf("%s", ctime(&n));
	} else if (argc >= 2) {
		printf("date: invalid flags/syntax\n");
	} else {
		printf("%s", ctime(&n));
	}
}

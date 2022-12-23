#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *ptr = fopen(argv[1], "r");
	char c;
	int e = 0;
	int n = 0;

	if (argc == 3 && !strcmp(argv[2], "-E")) {
		e = 1;
	}
	if (argc == 3 && !strcmp(argv[2], "-n")) {
		n = 1;
	}
	if (ptr == NULL) {
		printf("cat: %s: No such file or directory, or invalid arguments\n", argv[1]);
		return -1;
	}
	int i = 2;
	if (n) {
		printf("  1  ");
	}
	while (!feof(ptr)) {
		c = fgetc(ptr);
		if (e && c =='\n') {
			printf("$");
		}
		if (!feof(ptr)) {
			printf("%c", c);
		}
		if (n && c == '\n') {
			printf("  %d  ", i);
			i++;
		}
	}
	if (n) {
		printf("\n");
	}
	fclose(ptr);
	return 0;
}

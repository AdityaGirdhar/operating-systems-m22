#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int i = 1;
	int v = 0;
	int mode = 777;
	if (!strcmp(argv[1], "-v")) {
		v = 1;
		i++;
	} else if (!strcmp(argv[1], "-m")) {
		mode = atoi(argv[2]);
		if (mode) {
			i += 2;
		} else {
			printf("mkdir: invalid mode entered\n");
			return 0;
		}
	}
	if (mkdir(argv[i], mode) != 0) {
		printf("mkdir: error, check arguments again\n");
	} else if (v) {
		printf("mkdir: created directory '%s'\n", argv[i]);
	}
}

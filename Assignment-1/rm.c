#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("rm: Too few arguments\n");
		return 0;
	}
	int v = 0;
	int i = 1;
	int prompt = 0;
	if (!strcmp(argv[1], "-v")) {
		v = 1;
		i++;
	}
	if (!strcmp(argv[1], "-i")) {
		prompt = 1;
		i++;
	}

	int f = 0;
	while (i < argc) {
		f = 1;
		if (prompt) {
			printf("rm: remove regular file %s? (y/n) ", argv[i]);
			char in;
			scanf("%c", &in);
			if (in == 'n' || in == 'N') {
				i++;
				continue;
			}
		}
		if (remove(argv[i]) != 0) {
			printf("rm: %s: file not found/file could not be deleted\n", argv[i]);
		} else if (v) {
			printf("rm: %s: successfully removed\n", argv[i]);
		}
		i++;
	}
	if (!f) {
		printf("rm: Too few arguments\n");
	}
}

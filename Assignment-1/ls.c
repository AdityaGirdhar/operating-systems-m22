#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char dName[100];
	DIR *ptr;
	struct dirent *d;
	int all = 0;
	int almostAll = 0;
	ptr = opendir(argv[1]);
	if (argc == 3 && !strcmp(argv[2], "-a")) {
		all = 1;
	}
	if (argc == 3 && !strcmp(argv[2], "-A")) {
		all = 1;
		almostAll = 1;
	}
	if (ptr == NULL) {
		printf("ls: %s: no such file or directory\n", argv[1]);
		return -1;
	}
	while (d = readdir(ptr)) {
		if (!strcmp(d->d_name, ".") || !strcmp(d->d_name, "..")) {
			if (!all || almostAll) {
				continue;
			}
		}
		if (!all && d->d_name[0] == '.') {
			continue;
		}
		printf("%s	", d->d_name);
	}
	printf("\n");
	return 0;
}

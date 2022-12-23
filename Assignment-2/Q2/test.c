#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

#define SYS_kernel_2d_memcpy 451

int main() {
	int row = 2;
	int col = 2;

	float src[row][col];
	float dest[row][col];

	src[0][0] = 1.1;
	src[0][1] = 1.2;
	src[1][0] = 2.1;
	src[1][1] = 2.2;

	printf("Source matrix: \n");
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%f	", src[i][j]);
		}
		printf("\n\n");
	}

	printf("\n");
	
	int ret = syscall(SYS_kernel_2d_memcpy, src, dest, row, col);
	printf("Destination matrix: \n");
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%f	", dest[i][j]);
		}
		printf("\n\n");
	}
}

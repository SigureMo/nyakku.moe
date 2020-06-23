#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int i;
	double sum = 0, cnt = 0;
	for (i = 1; i < argc; i++) {
		sum += atof(argv[i]);
		cnt++;
	}
	printf("Average is %g\n", sum/cnt);
	return 0;
}

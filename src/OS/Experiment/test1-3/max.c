#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int i;
	double max = atof(argv[1]);
	for (i = 2; i < argc; i++) {
		double t = atof(argv[i]);
		if (t > max) {
			max = t;
		}
	}
	printf("Max num is %g\n", max);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int i;
	double min = atof(argv[1]);
	for (i = 2; i < argc; i++) {
		double t = atof(argv[i]);
		if (t < min) {
			min = t;
		}
	}
	printf("Min num is %g\n", min);
	return 0;
}

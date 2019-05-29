#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	pid_t pid1, pid2;
	pid1 = fork();
	if (pid1 == 0) {
		pid2 = fork();
		if (pid2 == 0) {
			printf("pid is %d\n", getpid());
		}
		else {
			wait(NULL);
			printf("pid is %d, subprocess pid is %d\n", getpid(), pid2);
		}
	}
	else {
		wait(NULL);
		printf("pid is %d, subprocess pid is %d\n", getpid(), pid1);
	}
	return 0;
}

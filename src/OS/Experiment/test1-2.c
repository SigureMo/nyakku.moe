#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	pid_t pid1, pid2;
	pid1 = fork();
	if (pid1 == 0) {
		printf("pid is %d\n", getpid());
	}
	else {
		pid2 = fork();
		if (pid2 == 0) {
			printf("pid is %d\n", getpid());
		}
		else {
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
			printf("pid is %d, subprocesses pid are %d and %d\n", getpid(), pid1, pid2);
		}
	}
	return 0;
}

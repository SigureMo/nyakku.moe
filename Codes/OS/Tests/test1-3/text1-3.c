#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(){
	if (fork() == 0) {
		char* const argv[] = {"ls", "-l", NULL};
		if (access("./max.out", F_OK) == -1) {
			if (fork() == 0) {
			    execl("/usr/bin/gcc", "gcc", "max.c", "-o", "max.out", NULL);
			}
			else {
				wait(NULL);
			}
		}
		execl("./max.out", "1", "2", NULL);
	}
	else {
		wait(NULL);
	}
	return 0;
}

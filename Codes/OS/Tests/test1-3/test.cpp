#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string>

using namespace std;

int main(int argc, char* argv[]){
	if (argc < 2) {
		cout << "number of arguments < 2!" << endl;
		return -1;
	}
	string action = argv[1];
	char** nums = new char*[argc];
	nums = argv + 1;
	if (!(action == "max" or action == "min" or action == "average")) {
		cout << "command " << action << " is not defined!" << endl;
		return -1;
	}
	if (fork() == 0) {
		string out_path = "./" + action + ".out";
		string src_path = action + ".c";
		const char* out_p = out_path.data();
		const char* src_p = src_path.data();
		if (access(out_p, F_OK) == -1) {
			cout << "program " << action << " is not exist, trying to compile..." << endl;
			if (fork() == 0) {
			    execl("/usr/bin/gcc", "gcc", src_p, "-o", out_p, NULL);
			}
			else {
				wait(NULL);
				cout << "successful" << endl;
			}
		}
		execve(out_p, nums, NULL);
	}
	else {
		wait(NULL);
	}
	return 0;
}

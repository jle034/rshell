#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

int main(int argc, char** argv) {
	
	int fd[2];
	if(pipe[fd] == -1) {
		perror("pipe");
	}
	cerr << "fd[0]" << fd[0] << endl;
	cerr << "fd[1]" << fd[1] << endl;



#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "%s: missing file operand", argv[0]);
		exit(1);
	}
	struct stat first;
	if (-1 == stat(argv[1], &first)) {
		perror("error in argv[1]");
		exit(1);
	}
	struct stat fdest;
	if (-1 == stat(argv[2], &fdest)) {
		link(argv[1],argv[2]);
		unlink(argv[1]);
		//if(-1 == rename(argv[1], argv[2])) {
		//	perror("rename");
		//}
	}
	else { // argv[2] exists
		if(S_ISDIR(fdest.st_mode)) {
			char* sub = new char[strlen(argv[2]) + strlen(argv[1]) + 2];
			strcpy(sub, argv[2]);
			strcat(sub, "/");
			strcat(sub, argv[1]);
			struct stat fdirdest;
			if (-1 == stat(sub, &fdirdest)) { 
				if(-1 == rename(argv[1], sub)) {
					perror("rename");
				}
			}
			else { 
				fprintf(stderr, "ERROR: %s already exists\n", sub);
			}
		}
		else { 
			fprintf(stderr, "ERROR: %s already exists\n", argv[2]);
		}
	}	
	return 0;
	perror("error in stat call 1");
	perror("error in stat call 2");
}


//#include <sys/types.h>
//#include <dirent.h>
//#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <stdio.h>
#include <algorithm>

using namespace std;

void print(vector<string> fdVec, int aFlag, int lFlag, int RFlag);

int main(int argc, char* argv[]) {
	
	// initialize flags to zero
	// if flag is still zero after checking, 
	// then flag is not found in user input
	int aFlag = 0;
	int lFlag = 0;
	int RFlag = 0;
	vector<string> fdVec;

	// for loop checks for flags and stores files/directories
	// begin at 1, so search doesn't include initial bin/ls argument
	// if flag is found, set appropriate flag to 1
	// if a file/directory is found, push back onto fdVec
	for(int i = 1; i < argc; i++) {
		
		string currArg(argv[i]);

		// if currArg begins with '-', it is considered a flag
		// do the following
		if(currArg.at(0) == '-') {
			
			if(currArg.length() == 1) {
				cout << "Error: One or more of these flags is invalid." << endl;
				exit(1);
			}
			
			for(unsigned j = 1; j < currArg.length();  j++) {
				
				if(currArg.at(j) == 'a') {
					aFlag = 1;
				}
				else if(currArg.at(j) == 'l') {
					lFlag = 1;
				}
				else if(currArg.at(j) == 'R') {
					RFlag = 1;
				}
				// if user inputs a flag that is not a, l, or R
				// output error and exit(1)
				else {
					cout << "Error: One or more of these flags cannot be handled." << endl;
					exit(1);
				}
			}
		}
		
		// else currArg does not begin with '-', it is considered a file/directory name
		// do the following
		else {
			
			fdVec.push_back(currArg);
		}
	}
	
	// if user does not specify any files/directories, assume current directory
	// push back "." to indicate current directory
	if(fdVec.size() == 0) {
		fdVec.push_back(".");
	}

	sort (fdVec.begin(), fdVec.end(), locale("en_US.UTF-8"));

	cout << "aFlag: " << aFlag << endl;
	cout << "lFlag: " << lFlag << endl;
	cout << "RFlag: " << RFlag << endl;

	cout << "fdVec: ";

	for(unsigned i = 0; i < fdVec.size(); i++) {
		cout << '<' << fdVec.at(i) << "> ";
	}
	cout << endl;

	for(unsigned i = 0; i < fdVec.size(); i++) {
		print(fdVec, aFlag, lFlag, RFlag);
	}
	
	return 0;
}

void print(vector<string> fdVec, int aFlag, int lFlag, int RFlag) {
	struct stat s;

	// if error with stat
	// perror("stat")
	if(lstat((fdVec.at(0)).c_str(), &s) == -1) {
		perror("stat");
	}
	
	// if regular file
	// do the following
	if(S_ISREG(s.st_mode)) {

	}
	
}



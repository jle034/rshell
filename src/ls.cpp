//#include <sys/types.h>
//#include <dirent.h>
//#include <stdio.h>
//#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;


int main(int argc, char* argv[]) {
	
	// initialize flags to zero
	// if flag is still zero after checking, 
	// then flag is not found in user input
	int aFlag = 0;
	int lFlag = 0;
	int RFlag = 0;
	vector<string> dirVec;

	// for loop checks for flags and stores files and directories
	// begin at 1, so search doesn't include initial bin/ls argument
	// if flag is found, set appropriate flag to 1
	// if file or directory is found, push back onto dirVec
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
			
			dirVec.push_back(currArg);
		}
	}
	
	// if user does not specify any directories, assume current directory
	// push back "." to indicate current directory
	if(dirVec.size() == 0) {
		dirVec.push_back(".");
	}

	cout << "aFlag: " << aFlag << endl;
	cout << "lFlag: " << lFlag << endl;
	cout << "RFlag: " << RFlag << endl;

	cout << "dirVec: ";
	for(unsigned i = 0; i < dirVec.size(); i++) {
		cout << '<' << dirVec.at(i) << "> ";
	}
	cout << endl;
	
	return 0;


















}

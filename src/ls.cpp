//#include <sys/types.h>
//#include <dirent.h>
//#include <stdio.h>
//#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


int main(int argc, char* argv[]) {
	
	// single flags
	string a = "-a";
	string l = "-l";
	string R = "-R";
	
	// flags starting with a
	string al = "-al";
	string aR = "-aR";
	string alR = "-alR";
	string aRl = "-aRl";

	// flags starting with l
	string la = "-la";
	string lR = "-lR";
	string laR = "-laR";
	string lRa = "-lRa";

	// flags starting with R
	string Ra = "-Ra";
	string Rl = "-Rl";
	string Ral = "-Ral";
	string Rla = "-Rla";

	// initialize flags to zero
	// if flag is still zero after checking, 
	// then flag is not found in user input
	int aFlag = 0;
	int lFlag = 0;
	int RFlag = 0;

	// for loop checks for flags
	for(int i = 0; i < argc; i++) {
		if(argv[i][0] == '-') {
			
			string temp(argv[i]);

			if(temp.size() == 1) {
				cout << "Error: Invalid flag." << endl;
				exit(1);
			}
			
			for(unsigned j = 1; j < temp.length();  j++) {
				
				if(temp.at(j) == 'a') {
					aFlag = 1;
				}
				else if(temp.at(j) == 'l') {
					lFlag = 1;
				}
				else if(temp.at(j) == 'R') {
					RFlag = 1;
				}
				// if user inputs a flag that is not a, l, or R
				// output error and exit(1)
				else {
					cout << "Error: Flag(s) cannot be handled." << endl;
					exit(1);
				}
			}
		}
	}

	cout << "aFlag: " << aFlag << endl;
	cout << "lFlag: " << lFlag << endl;
	cout << "RFlag: " << RFlag << endl;
	
	return 0;


















}

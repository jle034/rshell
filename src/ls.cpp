//#include <sys/types.h>
//#include <dirent.h>
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
		if(argv[i] == a) {
			aFlag = 1;
		}
		else if(argv[i] == l) {
			lFlag = 1;
		}
		else if(argv[i] == R) {
			RFlag = 1;
		}
		else if((argv[i] == al) || (argv[i] == la)) {
			aFlag = 1;
			lFlag = 1;
		}
		else if((argv[i] == lR) || (argv[i] == Rl)) {
			lFlag = 1;
			RFlag = 1;
		}
		else if((argv[i] == aR) || (argv[i] == Ra)) {
			aFlag = 1;
			RFlag = 1;
		}
		else if((argv[i] == alR) || (argv[i] == aRl) ||
			(argv[i] == laR) || (argv[i] == lRa) ||
			(argv[i] == Ral) || (argv[i] == Rla)) {

			aFlag = 1;
			lFlag = 1;
			RFlag = 1;
		}
	}
	
	return 0;


















}

//#include <sys/types.h>
//#include <dirent.h>
//#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <sys/stat.h>
//#include <sys/types.h>
#include <stdio.h>
#include <algorithm>
//#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <string.h>

using namespace std;


// helper functions :]
void printSingleFile(struct stat s);
void printEverything(vector<string> fdVec, int aFlag, int lFlag, int RFlag, int fdOriginalSize);
void printl(struct stat s, vector<string>fdVec);

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

	int fdOriginalSize = fdVec.size();

	for(unsigned i = 0; i < fdVec.size(); i++) {
		cout << '<' << fdVec.at(i) << "> ";
	}
	cout << endl;

	while(fdVec.size()) {
		printEverything(fdVec, aFlag, lFlag, RFlag, fdOriginalSize);
		fdVec.erase(fdVec.begin());
	}	

	cout << endl;

	return 0;
}

void printSingleFile(struct stat s) {

}

void printl(struct stat s, string fdName) {
	
	string normal = "\033[0;00m";
	string blueOnGray = "\033[1;100;36m";
	
	// if link
	// print 'l'
	if(S_ISLNK(s.st_mode)) {
		cout << 'l';
	}
	// else if directory
	// print 'd'
	else if(S_ISDIR(s.st_mode)) {
		cout << 'd';
	}
	// else, neither link nor directory
	// print '-'
	else {
		cout << '-';
	}

	// if user has read permission, print 'r'
	// else print '-' indicating no read permission
	//cout << (s.st_mode & S_IRUSR)?"r":"-"
	if(s.st_mode & S_IRUSR) {
		cout << 'r';
	}
	else {
		cout << '-';
	}
	// if user has write permission, print 'w'
	// else print '-' indicating no write permission
	if(s.st_mode & S_IWUSR) {
		cout << 'w';
	}
	else {
		cout << '-';
	}
	// if user has execute permission, print 'x'
	// else print '-' indicating no execute permission
	if(s.st_mode & S_IXUSR) {
		cout << 'x';
	}
	else {
		cout << '-';
	}

	//----------------------------------------
	// if group has read permission, print 'r'
	// else print '-' indicating no read permission
	if(s.st_mode & S_IRGRP) {
		cout << 'r';
	}
	else {
		cout << '-';
	}
	// if group has write permission, print 'w'
	// else print '-' indicating no write permission
	if(s.st_mode & S_IWGRP) {
		cout << 'w';
	}
	else {
		cout << '-';
	}
	// if group has execute permission, print 'x'
	// else print '-' indicating no execute permission
	if(s.st_mode & S_IXGRP) {
		cout << 'x';
	}
	else {
		cout << '-';
	}

	//----------------------------
	// if others has read permission, print 'r'
	// else print '-' indicating no read permission
	if(s.st_mode & S_IROTH) {
		cout << 'r';
	}
	else {
		cout << '-';
	}
	// if others has write permission, print 'w'
	// else print '-' indicating no write permission
	if(s.st_mode & S_IWOTH) {
		cout << 'w';
	}
	else {
		cout << '-';
	}
	// if others has execute permission, print 'x'
	// else print '-' indicating no execute permission
	if(s.st_mode & S_IXOTH) {
		cout << 'x';
	}
	else {
		cout << '-';
	}
	
	cout << ' ';

	// print number of hard links
	cout << s.st_nlink;

	cout << ' ';

	// print username
	struct passwd *userid = getpwuid(s.st_uid);
	if(userid == NULL) {
		perror("getpwuid");
		exit(1);
	}
	else {
		cout << userid->pw_name;
	}
	
	cout << ' ';
	
	// print groupname
	struct group *groupid = getgrgid(s.st_gid);
	if(groupid == NULL) {
		perror("getgrgid");
		exit(1);
	}
	else {
		cout << groupid->gr_name;
	}
	
	cout << ' ';

	cout << s.st_size;

	cout << ' ';

	time_t time = s.st_mtime;
	struct tm *thisTime = localtime(&time);
	char printTime[100];
	strftime(printTime, 100, "%b %e %H:%M", thisTime);
	cout << printTime;

	cout << ' ';

	cout << fdName << endl;


}

void printEverything(vector<string> fdVec, int aFlag, int lFlag, int RFlag, int fdOriginalSize) {
	struct stat s;

	cout << "HERE" << endl;

	// if error with stat
	// perror("stat")
	if(lstat((fdVec.at(0)).c_str(), &s) == -1) {
		perror("stat");
	}
	
	// if regular file
	// do the following
	if(S_ISREG(s.st_mode)) {
		
		cout << "IS REGULAR FILE" << endl;

		// if lFlag is included
		// do the following
		if(lFlag) {
			printl(s, fdVec.at(0));
		}
		
	}
	else if(S_ISDIR(s.st_mode)) {

		int total = 0;
		vector<string> newDirEntVec;
		
		cout << "IS DIRECTORY" << endl;
	
		DIR *currDir = opendir((fdVec.at(0)).c_str());
		if(currDir == NULL) {
			perror("opendir");
			exit(1);
		}
		
		if(fdOriginalSize >1) {
			cout << fdVec.at(0) << ":" << endl;
		}
		
		dirent* currDirEnt;

	/*
		while((currDirEnt = readdir(currDir))) {
			if(currDirEnt == NULL) {
				perror("readdir");
				exit(1);
			}
			char temp[512];
			strcpy(temp, (fdVec.at(0)).c_str());
			strcat(temp, "/");
			strcat(temp, currDirEnt->d_name);

			if(lstat(temp, &s) == -1) {
				perror("stat");
				exit(1);	
			}

			// if lFlag
			// do the following
			if(lFlag) {
				// if aFlag
				// printl like normal	
				if(aFlag) {
					printl(s, currDirEnt->d_name);
				}	
				// else no aFlag
				// check for hidden files
				// only print l on files nonhidden files
				else if((currDirEnt->d_name[0] != '.')) {
					printl(s, currDirEnt->d_name);
				}
			}	
		}
	*/
		while((currDirEnt = readdir(currDir))) {
			if(currDirEnt == NULL) {
				perror("readdir");
				exit(1);
			}
			char temp[512];
			strcpy(temp, (fdVec.at(0)).c_str());
			strcat(temp, "/");
			strcat(temp, currDirEnt->d_name);

			if(lstat(temp, &s) == -1) {
				perror("stat");
				exit(1);
			}
			
			if(lFlag) {
				if(aFlag) {
					total += s.st_blocks;
					newDirEntVec.push_back(temp);
				}
				else if((currDirEnt->d_name[0] != '.')) {
					total += s.st_blocks;
					newDirEntVec.push_back(temp);
				}
			}
		}

		sort (newDirEntVec.begin(), newDirEntVec.end(), locale("en_US.UTF-8"));

		if(lFlag) {
			cout << "total " << total/2 << endl;
			for(unsigned i = 0; i < newDirEntVec.size(); i++) {
				if(lstat(newDirEntVec.at(i).c_str(), &s) == -1) {
					perror("lstat");
				}
				string temp;
				printl(s, newDirEntVec.at(i));
			}
		}
	}	
}



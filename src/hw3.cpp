#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <fcntl.h>
#include <signal.h>

using namespace std;

//void interruptHandle(int signum, siginfo_t* info, void *ptr);
void cdPath (vector<char*> command);
void prompt();
void removeComments(string& s);
int findThis(vector<char*> v, string s);
int findFirst(vector<char*> v, string s);
string vecCharToString(vector<char*> v, unsigned start, unsigned end);
vector<char*> splitSemicolon(string userInput);
vector<char*> splitSpace(string userInput);
vector<char*> getCommands(char* charBlurb);
vector<string> getConnectors(char* blurb);
bool executeCommand(vector<char*> command);
void executecd(vector<char*> parsedCommand); 
void executeBlurb(vector<char*> commands, vector<string> connectors);

//struct sigaction interrupt;
//int interruptFlag = 0;
char* pwd;
char* home;

int main(int argc, char* argv[]) {

	pwd = getenv("PWD");
	home = getenv("HOME");

	string strpwd = string(pwd);
	string strhome = string(home);

	if(strpwd.find(strhome) != string::npos) {
		strpwd.replace(0, strhome.length(), "~");
	}
	pwd = &strpwd.at(0);

	cout << "PWD: " << pwd << endl;
	cout << "HOME: " << home << endl;

/*
	string temp = string(pwd);
	temp.replace(0, string(home).size(), "~");
	pwd = &temp.at(0);

	cout << "PWD: " << pwd << endl;
	cout << "HOME: " << home << endl;
*/

	if(strcmp(pwd, home)) {
		cout << "YAY" << endl;
	}


/*
	interrupt.sa_sigaction = interruptHandle;
	interrupt.sa_flags = SA_SIGINFO;

	if(sigaction(SIGINT, &interrupt, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}
*/

	while(1) {
		
/*
		if(interruptFlag) {
			cout << endl << "C";	
			interruptFlag = 0;
			sleep(1);
		}
*/

		// outputs the prompt
		prompt();

		// gets input and stores in userInput
		string userInput;
		getline(cin, userInput);

		// remove comments from userInput (found after "#")
		removeComments(userInput);
	
		// parse userInput by semicolons
		// store each blurb in scVec
		vector<char*> scVec  = splitSemicolon(userInput);

		// get the commands and connectors of each blurb
		// execute each blurb
		for(unsigned j = 0; j < scVec.size(); j++) {
			vector<string> connectorVec = getConnectors(scVec.at(j));
			vector<char*> commandVec = getCommands(scVec.at(j));
			executeBlurb(commandVec, connectorVec);
		}
	}
	return 0;
}

// vector command should already be checked for "cd" at command.at(0)
// function changes working directory to the appropriate directory
// cd <PATH> uses the first directory if multiple are found
void cdPath (vector<char*> command) {
	char* path = command.at(1);
	string strPath = string(path);
	string strHome = string(home);

	cout << "HERE" << endl;

	if(strPath.at(0) == '~') {
		strPath.replace(0, 1, home);
	}
	if(chdir(path) != 0) {
		perror("chdir");
		exit(1);
	}
	else {
		if(strPath.find(strHome) != string::npos) {
			strPath.replace(0, strHome.length(), "~");
		}
		if(strPath.find(string(pwd)) == string::npos) {
			strPath.insert(0, string(pwd) + "/");
		}
		cout << "strPath: " << strPath << endl;
		path = &strPath.at(0);
		pwd = path;
	}
	/*
	if((strPath.at(0) == '~') || strcmp(path, home)) {
		chdir(path);
		pwd = path;
	}	
	*/	
}

/*
void interruptHandle(int signum, siginfo_t* info, void *ptr) {
	interruptFlag = 1;
}
*/

// function prints the prompt to look like this:
// [userName]@[hostName] $
// returns nothing
void prompt() {
	char* userName = getlogin();
	if(userName == NULL) {
		perror("getlogin");
	}
	char hostName[64];
	int checkHostName = gethostname(hostName, sizeof(hostName));		
	if(checkHostName == -1) {
		perror("gethostname");
	}
	cout << userName << "@" << hostName << ":" << pwd << " $ ";
}

// function removes comments in string& s
// comments are denoted by a "#"
// returns nothing
void removeComments(string& s) {
	size_t start = s.find_first_of("#");
	if (start != string::npos) {
		s.erase(start);
	}
}

// function searches through vector<char*> v
// returns location of string s if found in v
// returns -1 if string s is not found in v
// returns -2 if string s is found more than once
int findThis(vector<char*> v, string s) {
	vector<string> temp, hold;
	for(unsigned j = 0; j < v.size(); j++) {
		string something = string(v.at(j));
		temp.push_back(something);
		hold.push_back(something);
	}
	int loc = -1;
	for(unsigned i = 0; i < temp.size(); i++) {
		if(temp.at(i) == s) {
			if(loc >= 0) {
				loc = -2;
			}
			else if(loc == -1) {
				loc = i;
			}
		}
	}
	for(unsigned k = 0; k < temp.size(); k++) {
		v.at(k) = &(hold.at(k).at(0));
	}
	return loc;
}

// function searches through vector<char*> v
// returns first location where string s is found
// returns -1 if string s is not found in v
int findFirst(vector<char*> v, string s) {
	vector<string> temp, hold;
	for(unsigned j = 0; j < v.size(); j++) {
		string something = string(v.at(j));
		temp.push_back(something);
		hold.push_back(something);
	}
	int loc = -1;
	for(unsigned i = 0; i < temp.size(); i++) {
		if(temp.at(i) == s) {
			if(loc == -1) {
				loc = i;
			}
		}
	}
	for(unsigned k = 0; k < temp.size(); k++) {
		v.at(k) = &(hold.at(k).at(0));
	}
	return loc;

}

// function returns a string of all the char* in v from start to end (inclusive)
string vecCharToString(vector<char*> v, unsigned start, unsigned end) {
	cout << "v: ";
	for(unsigned i = 0; i < v.size(); i++) {
		string first = string(v.at(i));
		string hold = first;
		cout << "<" << first << "> ";
		v.at(i) = &hold.at(0);
	}
	cout << endl;
	string returnThis;
	for(unsigned i = start; i <= end; i++) {
			string temp = string(v.at(i));
			string hold = temp;
			cout << "HERE: " << temp << endl;
			returnThis.append(temp);
			v.at(i) = &hold.at(0);
	}
	return returnThis;
}

// function parses string userInput by ";"
// returns these as a vector<char*> 
vector<char*> splitSemicolon(string userInput) {
	//char* charInput = &userInput.at(0);
	string s = userInput;
	char* charInput = (char*)s.c_str();
	vector<char*> wordVec;

	char* currToken;
	currToken = strtok(charInput, ";");

	while(currToken != NULL) {
		wordVec.push_back(currToken);
		currToken = strtok(NULL, ";");
	}
	return wordVec;
}

// function parses string userInput by " "
// returns these as a vector<char*>
vector<char*> splitSpace(string userInput) {
	//char* charInput = &userInput.at(0);
	string s = userInput;
	char* charInput = (char*)s.c_str();
	vector<char*> wordVec;

	char* currToken;
	currToken = strtok(charInput, " \t");

	while(currToken != NULL) {
		wordVec.push_back(currToken);
		currToken = strtok(NULL, " \t");
	}
	return wordVec;
}

// function uses strtok() to parse string blurb by connectors && and ||
// returns vector<char*> of all commands in the char* charBlurb
vector<char*> getCommands(char* charBlurb) {
	char* temp = charBlurb;	
	string stringTemp(temp);
	string blurb = stringTemp;
	string hold = blurb;

	// replace connectors with these strings
	// takes care of cases where there are no spaces between connectors and commands
	string repAnd = " * ";
	string repOr = " ! ";	
	string repPipe = " | ";
	string repOut = " > ";
	string repOutOut = " >> ";
	string repIn = " < ";
	string repInInIn = " <<< ";
	vector<char*> semicolonVec;

	// if blurb is empty
	// return empty vector
	if(blurb.size() == 0) {
		return semicolonVec;
	}

	// replaces all instances of "||" with "!"
	// replaces all instances of "&&" with "*"
	for(unsigned i = 0; i < blurb.size() - 1; i++) {
		if(blurb.at(i) == '|') {
			if(blurb.at(i + 1) == '|') {
				blurb.replace(i, 2, repOr);
				i += 2;
			}
			else if(blurb.at(i + 1) != '|') {
				blurb.replace(i, 1, repPipe);
				i += 2;
			}
		}
		else if(blurb.at(i) == '&') {
			if(blurb.at(i + 1) == '&') {
				blurb.replace(i, 2, repAnd);
				i += 2;
			}
		}
		else if((blurb.at(i) == '>')) {
			if(blurb.at(i + 1) == '>') {
				blurb.replace(i, 2, repOutOut);
				i += 3;
			}
			else if(blurb.at(i + 1) != '>') {
				blurb.replace(i, 1, repOut);
				i += 2;
			}
		}
		else if(blurb.at(i) == '<') {
			if(blurb.at(i + 1) != '<') {
				blurb.replace(i, 1, repIn);
				i += 2;
			}
			else {
				if(((i + 2) < blurb.length()) && (blurb.at(i + 2)) == '<') {
					blurb.replace(i, 3, repInInIn);
					i += 4;
				}
			}
		}
	}

	char* charTemp = &blurb.at(0); 
	char* token;
	token = strtok(charTemp, "!*");

	while(token != NULL) {
		string str = string(token);
		semicolonVec.push_back(token);
		token = strtok(NULL, "!*");
	}
	charBlurb = &hold.at(0);
	return semicolonVec;
}

// function parses string blurb
// returns vector of ANDs and ORs in order of appearance
vector<string> getConnectors(char* blurb) {
	char* temp = blurb;

	string str(temp);
	string hold = str;
	vector<string> v;
	for(unsigned i = 0; i < str.size() - 1; i++) {
		if((str.at(i) == '&') && (str.at(i + 1) == '&')) {
			i++;
			v.push_back("&&");
		}
		else if((str.at(i) == '|') && (str.at(i + 1) == '|')) {
			i++;
			v.push_back("||");
		}
	}
	blurb = &hold.at(0);
	return v;
}

// function takes in a single command (already parsed by spaces)
// and executes the command using execvp
// returns true if command executes
// returns false if command is invalid or does not execute
bool executeCommand(vector<char*> command) {

	bool success = true;

	if(command.size() == 1) {
		string something = string(command.at(0));
		string hold = something;
		if(something == "exit") {
			exit(1);
		}
		command.at(0) = &hold.at(0);
	}

	int foundPipe = findThis(command, "|");
	int pipeLoc = findFirst(command, "|");
	int fd[2];
	if(foundPipe != -1) {
		if(pipe(fd) == -1) {
			perror("pipe");
			exit(1);	
		}
	}	

	vector<char*> newCommand;

	int pid = fork();

	// if fork produces an error
	if(pid == -1) {
		perror("fork");
		exit(1);
	}
	
	// if child
	else if(pid == 0) {

		string inFile;
		string outFile;

		// takes care of commands that have ">" 
		int foundOut = findThis(command, ">");
		if(foundOut == -2) {
			cerr << "Error: Cannot have more than one output redirection" << endl;
			exit(1);	
		}	
		else if(foundOut >= 0) {

			// if ">" is not found at the second to last location
			// the file name is invalid
			// either not given or has spaces in it
			if(foundOut != (int(command.size() - 2))) {
				cerr << "Error: Invalid file name" << endl;
				exit(1);
			}

			newCommand.clear();
			for(unsigned i = 0; i < (unsigned)foundOut; i++) {
				newCommand.push_back(command.at(i));
			}	
			outFile = string(command.at(command.size()-1));
			string hold = outFile;
			int fdo = open(outFile.c_str(), O_WRONLY|O_TRUNC);

			// if fdo == -1, outFile doesn't exist
			// create outFile
			if(fdo == -1) {
				fdo = creat(outFile.c_str(), S_IRUSR|S_IWUSR);
			}
			if(fdo == -1) {
				perror("creat");
				exit(1);
			}
			if(close(1)) {
				perror("close");
				exit(1);
			}
			if(dup(fdo) == -1) {
				perror("dup");
				exit(1);
			}
		}

		// takes care of commands that have ">>"
		int foundOutOut = findThis(command, ">>");
		if(foundOutOut == -2) {
			cerr << "Error: Cannot have more than one output redirection" << endl;
			exit(1);
		}
		else if(foundOutOut >= 0) {
		
			// if ">>" is not found at the second to last location
			// the file name is invalid
			// either not given or has spaces in it
			if(foundOutOut != (int(command.size() - 2))) {
				cerr << "Error: Invalid file name" << endl;
				exit(1);
			}

			newCommand.clear();
			for(unsigned i = 0; i < (unsigned)foundOutOut; i++) {
				newCommand.push_back(command.at(i));
			}	
			outFile = string(command.at(command.size()-1));
			string hold = outFile;
			int fdo = open(outFile.c_str(), O_WRONLY|O_APPEND);

			// if fdo == -1, outFile doesn't exist
			// create outFile
			if(fdo == -1) {
				fdo = creat(outFile.c_str(), S_IRUSR|S_IWUSR);
			}
			if(fdo == -1) {
				perror("creat");
				exit(1);
			}
			if(close(1)) {
				perror("close");
				exit(1);
			}
			if(dup(fdo) == -1) {
				perror("dup");
				exit(1);
			}
		}		

		// takes care of commands that have "<" 
		int foundIn = findThis(command, "<");
		if(foundIn == -2) {
			cerr << "Error: Cannot have more than one input redirecton" << endl;
			exit(1);
		}
		else if(foundIn >= 0) {

			// if "<" is not found at the second to last location
			// the file name is invalid
			// either not given or has spaces in it
			if(foundIn != (int(command.size() - 2))) {
				cerr << "Error: Invalid file name" << endl;
				exit(1);
			}
			newCommand.clear();
			for(unsigned i = 0; i < (unsigned)foundIn; i++) {
				newCommand.push_back(command.at(i));
			}	
			inFile = string(command.at(command.size()-1));
			string hold = inFile;
			int fdi = open(inFile.c_str(), O_RDONLY);

			// if fdi == -1, inFile doesn't exist
			if(fdi == -1) {
				perror("open");
				exit(1);
			}
			if(close(0)) {
				perror("close");
				exit(1);
			}
			if(dup(fdi) == -1) {
				perror("dup");
				exit(1);
			}
		}

		// takes care of commands that have "<<<" 
		int foundInInIn = findThis(command, "<<<");
		if(foundInInIn == -2) {
			cerr << "Error: Cannot have more than one input redirecton" << endl;
			exit(1);
		}
		else if(foundInInIn >= 0) {
			//cout << "FOUND ONE <<<" << endl;
			int inInInLoc = findFirst(command, "<<<");
			for(unsigned i = (unsigned)(inInInLoc + 1); i < command.size(); i++) {
				string temp(command.at(i));
				string hold = temp;
				cout << temp;
				command.at(i) = &hold.at(0);
			}
			cout << endl;
			exit(0);
		}

		if(findThis(command, "|") != -1) {
			if(dup2(fd[1], 1) == -1) {
				perror("dup2");
				exit(1);
			}
			if(close(fd[0]) == -1) {
				perror("close");
				exit(1);
			}

			newCommand.clear();
			for(unsigned i = 0; i < (unsigned)pipeLoc; i++) {
				newCommand.push_back(command.at(i));
			}
		}
			
		if((foundOut == -1) && (foundOutOut == -1) && (foundIn == -1) && (foundPipe == -1)) {
			newCommand = command;
		}

		char* argv[sizeof(newCommand) + 1];

		unsigned i = 0;
		for(i = 0; i < newCommand.size(); i++) {
			argv[i] = newCommand[i];
		}
		argv[i] = 0;

		if(execvp(*argv, argv) == -1) {
			perror("execvp");
			exit(1);
		}
		
		// gets rid of zombie processes
		exit(1);
	}

	// else parent
	else {
		int status;

		if(waitpid(pid, &status, 0) == -1) {
			perror("waitpid");
			exit(1);
		}

		// if status is 0
		// then child process successfully executed
		// store a true in bool success for return
		if(status == 0) {
			success = true;
		}

		// if status is not a 0
		// then child process did not successfully execute
		// store a false in bool success for return
		else {
			success = false;
		}
	}

	int temp;
	if(foundPipe != -1) {
		temp = dup(0);
		if(temp == -1) {
			perror("dup");
			exit(1);		
		}
		if(dup2(fd[0], 0) == -1) {
			perror("dup2");
			exit(1);	
		}
		if(close(fd[1]) == -1) {
			perror("close");
			exit(1);	
		}

		for(unsigned i = 0; i < (unsigned)pipeLoc; i++) {
			command.erase(command.begin());
		}
		command.erase(command.begin());

		executeCommand(command);
	}

	if(foundPipe != -1) {
		if(dup2(fd[0], 0) == -1) {
			perror("dup2");
			exit(1);
		}
		if(dup2(temp, 0) == -1) {
			perror("dup2");
			exit(1);
		}
	}

	return success;
	
}

// already confirmed that parsedCommand.at(0) == "cd"
void executecd(vector<char*> parsedCommand) {
	if(parsedCommand.size() == 1) {
		chdir(home);
		pwd = home;
	}
	else {
		cdPath(parsedCommand);
	}
}

// function executes a single blurb (blurbs are separated by semicolons)
// vector<char*> commands is the vector of commands (already parsed by && and ||)
// vector<string> connectors is the vector of  &&'s and ||'s in the order they are found in the blurb
void executeBlurb(vector<char*> commands, vector<string> connectors) {

	// if blurb only has a single command
	// execute the command
	if(commands.size() == 1) {
		string temp = string(commands.at(0));
		string hold = temp;
		cout << "blurb: " << hold << endl;
		vector<char*> parsedCommand = splitSpace(temp);
		if(string(parsedCommand.at(0)) == "cd") {
			cout << "EVEN BETTER" << endl;
			executecd(parsedCommand);
		}
		else {
			executeCommand(parsedCommand);
		}
		commands.at(0) = &hold.at(0);
	}	

	// if blurb has more than one command
	// check && or || logic before executing the commands
	else if(commands.size() > 1) {
		
		bool previous;
		int count = 0;
		string temp = string(commands.at(0));
		string hold = temp;
		vector<char*> parsedCommand = splitSpace(temp);
		commands.at(0) = &hold.at(0);
		previous = executeCommand(parsedCommand);		


		for(unsigned i = 1; i < commands.size(); i++) {
			// if there is an &&, 
			// execute the current command only if prev returns true
			if(connectors.at(count) == "&&") {
				if(previous) {
					string temp = string(commands.at(i));
					string hold = temp;
					vector<char*> parsedCommand = splitSpace(temp);
					commands.at(i) = &hold.at(0);
					previous = executeCommand(parsedCommand);		
				}	
			}
			// if there is an ||
			// execute the current command only if prev returns false
			else if(connectors.at(count) == "||") {
				if(!previous) {
					string temp = string(commands.at(i));
					string hold = temp;
					vector<char*> parsedCommand = splitSpace(temp);
					commands.at(i) = &hold.at(0);
					previous = executeCommand(parsedCommand);					
				}
			}	
			count++;
		}
	}
}


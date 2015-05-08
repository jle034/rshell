#include <iostream>
#include <stdio.h>
//#include <unistd.h>
//#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
//#include <cstdlib>
//#include <cstring>
//#include <string>
//#include <string.h>	
//#include <errno.h>
//#include <pwd.h>
//#include <vector>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
//#include <boost/foreach.hpp>

using namespace std;
using namespace boost;

// function prints the prompt to look like this:
// [userName]@[hostName] $
// returns nothing
void prompt() {
	char* userName = getlogin();
	if(userName == NULL) {
		perror("getlogin()");
	}
	char hostName[64];
	int checkHostName = gethostname(hostName, sizeof(hostName));		
	if(checkHostName == -1) {
		perror("gethostname()");
	}
	cout << userName << "@" << hostName  << " $ ";
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

vector<char*> splitSemicolon(string userInput) {
	string s  = userInput;
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
	string s  = userInput;
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

// function uses strtok() to parse string blurb
vector<char*> getCommands(char* charBlurb) {
	char* temp = charBlurb;	
	string blurb(temp);

	string repAnd = " * ";
	string repOr = " ! ";	
	vector<char*> semicolonVec;
	string trueString = "true";
	char* trueChar = (char*)trueString.c_str();

	// if blurb is empty
	// returns empty vector
	if(blurb.size() == 0) {
		return semicolonVec;
	}

	// changes all instances of "||" into "!"
	// changes al instances of "&&" into "*"
	for(unsigned i = 0; i < blurb.size() - 1; i++) {
		if(blurb.at(i) == '|') {
			if(blurb.at(i + 1) == '|') {
				blurb.replace(i, 2, repOr);
			}
		}
		else if(blurb.at(i) == '&') {
			if(blurb.at(i + 1) == '&') {
				blurb.replace(i, 2, repAnd);
			}
		}
	}

//	string temp = blurb;
//	char* charBlurb = (char*)temp.c_str();

	char* charTemp = new char[blurb.length() + 1];   //blurb.c_str();
	strcpy(charTemp, blurb.c_str());
//	delete [] blurb;

	char* token;
	token = strtok(charTemp, "!*");

	while(token != NULL) {
		string str = string(token);
		semicolonVec.push_back(token);
		if(str.size() == 0) {
			cout << "EMPTY" << endl;
			semicolonVec.push_back(trueChar);
		}
		token = strtok(NULL, "!*");
	}
	return semicolonVec;
}

// function parses string blurb
// returns vector of ANDs and ORs in order of appearance
vector<char> getConnectors(char* blurb) {
	char* temp = blurb;
	string str(temp);
	vector<char> v;
	for(unsigned i = 0; i < str.size() - 1; i++) {
		if((str.at(i) == '&') && (str.at(i + 1) == '&')) {
			i++;
			v.push_back('&');
		}
		else if((str.at(i) == '|') && (str.at(i + 1) == '|')) {
			i++;
			v.push_back('|');
		}
	}
	return v;	
}

// function takes in a command (already parsed by spaces)
// and executes the command using execvp
// returns true if command executes
// returns false if command is invalid or does not execute
bool executeCommand(vector<char*> command) {
	
	if(command.size() == 1) {
		string something(command.at(0));
//		cout << "Something = " << something << endl;
//		cout << "command.at(0) = " << command.at(0) << endl;	
		if(something == "exit") {
//			cout << "FOUND EXIT" << endl;
			exit(1);
		}
		command.at(0) = new char[something.length() + 1];
		strcpy(command.at(0), something.c_str());
//		cout << "command.at(0) = " << command.at(0) << endl;
	}
	
	int pid = fork();

	// if fork produces an error
	if(pid == -1) {
//		cout << "PERROR FORK" << endl;
		perror("fork");
		exit(1);
//		return false;
	}
	
	// if child
	else if(pid == 0) {
		char* argv[sizeof(command) + 1];

//		cout << "Parsed Command: in executeCommand BBBBBBBB";
//		for(int k = 0; k < command.size(); k++) {
//			cout << "<" << command.at(k) << ">" << " ";
//		}
//		cout << endl;

		unsigned i = 0;
		for(i = 0; i < command.size(); i++) {
			argv[i] = new char[command.size() + 1];
			strcpy(argv[i], command[i]);
		}
		argv[i] = 0;

//		cout << "Parsed Command: in executeCommand AAAAAAAA";
//		for(int j = 0; j < command.size(); j++) {
//			cout << "<" << command.at(j) << ">" << " ";
//		}
//		cout << endl;

		if(execvp(argv[0], argv) == -1) {
//			cout << "ERROR!!!!!!";
			perror("execvp");
		}
		exit(1);
	}

	// if parent
	else {
// 		wait(NULL);
		int status;

		if(waitpid(pid, &status, 0) == -1) {
			perror("waitpid");
			exit(1);
		}
		if(status == 0) {
			return true;
		}
		return false;
	}
}

void executeBlurb(vector<char*> commands, vector<char> connectors) {
	

/*
	if(commands.size() == 0) {
		string trueString = "true";
		char* temp = (char*)trueString.c_str();
		commands.push_back(temp);
	}
*/

	if(commands.size() == 1) {
		vector<char*> parsedCommand = splitSpace(commands.at(0));
//		cout << "PARSED COMMAND: in executeBlurb ";
//		for(int i = 0; i < parsedCommand.size(); i++) {
//			cout << "<" << parsedCommand.at(i) << ">" << " ";
//		}
//		cout << endl;
		executeCommand(parsedCommand);
	}	

	else if(commands.size() > 1) {
		
		bool previous;
		int count = 0;
		vector<char*> parsedCommand = splitSpace(commands.at(0));
//		cout << "PARSED COMMAND: in executeBlurb ";
//		cout << "parsedCommand.size() = " << parsedCommand.size();
//		for(int i = 0; i < parsedCommand.size(); i++) {
//			cout << "<" << parsedCommand.at(i) << ">" << " ";
//		}
//		cout << endl;
//		cout << "HERE2" << endl;
		previous = executeCommand(parsedCommand);		

		for(unsigned i = 1; i < commands.size(); i++) {
			if(connectors.at(count) == '&') {
				if(previous) {
					vector<char*> parsedCommand = splitSpace(commands.at(i));
//					cout << "PARSED COMMAND: in executeBlurb ";
//					for(int i = 0; i < parsedCommand.size(); i++) {
//						cout << "<" << parsedCommand.at(i) << ">" << " ";
//					}
					previous = executeCommand(parsedCommand);		
				}	
			}
			else if(connectors.at(count) == '|') {
				if(!previous) {
					vector<char*> parsedCommand = splitSpace(commands.at(i));
//					cout << "PARSED COMMAND: in executeBlurb ";
//					for(int i = 0; i < parsedCommand.size(); i++) {
//						cout << "<" << parsedCommand.at(i) << ">" << " ";
//					}
					previous = executeCommand(parsedCommand);					
				}
			}	
			count++;
		}
	}
}

int main(int argc, char* argv[]) {

	while(1) {

		// outputs the prompt
		prompt();

		// gets input and stores in userInput
		string userInput;
		getline(cin, userInput);

		// remove comments from userInput (found after "#")
//		cout << "User Input: " << endl << userInput << endl << endl;
		removeComments(userInput);
//		cout << "User Input W/O Comments: " << endl << userInput << endl << endl;
	
		// parse userInput by semicolons
		// store in wordVec
//		cout << "User Input split by semicolons: " << endl;
		vector<char*> scVec  = splitSemicolon(userInput);
//		cout << "scVec.size() = " << scVec.size() << endl;
//		if(scVec.size() != 0) {
//			for(int i = 0; i < scVec.size(); i++) {
//				cout << scVec.at(i) << endl;
//			}
//			cout << endl;
//		}	

		// testing olderParseBlurb Function
//		cout << "Testing olderParseBlurb Function: " << endl;
		for(unsigned j = 0; j < scVec.size(); j++) {
//			cout << "Blurb " << j << ": " << endl;
			vector<char*> commandVec = getCommands(scVec.at(j));
			vector<char> connectorVec = getConnectors(scVec[j]);
//			cout << "commandVec.size() = " << commandVec.size() << endl;
//			cout << "COMMANDS: ";
//			if(commandVec.size() != 0) {	
//				for(int i = 0; i < commandVec.size(); i++) {
//					cout << "<" << commandVec.at(i) << "> ";
//				}
//			}
//			cout << endl;
//			cout << "CONNECTORS: ";
//			if(connectorVec.size() != 0) {
//				for(int i = 0; i < connectorVec.size(); i++) {
//					cout << connectorVec.at(i) << " ";
//				}
//			}
//			cout << endl;
			executeBlurb(commandVec, connectorVec);
		}
		
/*	
		for (int i = 0; i < scVec.size(); i++) {
			removeSpaces(scVec.at(i));
			cout << scVec.at(i) << endl;
		}	
		cout << endl;

		cout << "User Input split by ORs and ANDs: " << endl;
		vector<string> orVec = splitOrsAnds(userInput);
		for(int i = 0; i < orVec.size(); i++) {
			cout << orVec.at(i) << endl;
		} 
		cout << endl;

		cout << "Vector of ANDs and ORs: " << endl;
		vector<string> temp = parseBlurb(userInput);
		for(int i = 0; i < temp.size(); i++) {
			cout << temp.at(i) << endl;
		}
		cout << endl;
*/
	}

	return 0;
}

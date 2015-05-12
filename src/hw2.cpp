#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

void prompt();
void removeComments(string& s);
vector<char*> splitSemicolon(string userInput);
vector<char*> splitSpace(string userInput);
vector<char*> getCommands(char* charBlurb);
vector<char> getConnectors(char* blurb);
bool executeCommand(vector<char*> command);
void executeBlurb(vector<char*> commands, vector<char> connectors);

int main(int argc, char* argv[]) {

	while(1) {

		// outputs the prompt
		prompt();

		// gets input and stores in userInput
		string userInput;
		getline(cin, userInput);

		// remove comments from userInput (found after "#")
		removeComments(userInput);
	
		// parse userInput by semicolons
		// store in wordVec
		vector<char*> scVec  = splitSemicolon(userInput);

		for(unsigned j = 0; j < scVec.size(); j++) {
			vector<char*> commandVec = getCommands(scVec.at(j));
			vector<char> connectorVec = getConnectors(scVec[j]);
			executeBlurb(commandVec, connectorVec);
		}
	}
	return 0;
}

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
// returns vector<char*> of all commands separated by connectors && and ||
vector<char*> getCommands(char* charBlurb) {
	char* temp = charBlurb;	
	string blurb(temp);

	string repAnd = " * ";
	string repOr = " ! ";	
	vector<char*> semicolonVec;
	string trueString = "true";
	char* trueChar = (char*)trueString.c_str();

	// if blurb is empty
	// return empty vector
	if(blurb.size() == 0) {
		return semicolonVec;
	}

	// changes all instances of "||" into "!"
	// changes all instances of "&&" into "*"
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

	char* charTemp = (char*)blurb.c_str();
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

// function takes in a single command (already parsed by spaces)
// and executes the command using execvp
// returns true if command executes
// returns false if command is invalid or does not execute
bool executeCommand(vector<char*> command) {
	
	if(command.size() == 1) {
		string something = command.at(0);
		if(something == "exit") {
			exit(1);
		}
		command.at(0) = (char*)something.c_str();
	}
	
	int pid = fork();
	// if fork produces an error
	if(pid == -1) {
		perror("fork");
		exit(1);
	}
	
	// if child
	else if(pid == 0) {
		char* argv[sizeof(command) + 1];

		unsigned i = 0;
		for(i = 0; i < command.size(); i++) {
			argv[i] = command[i];
		}
		argv[i] = 0;

		if(execvp(argv[0], argv) == -1) {
			perror("execvp");
		}
		exit(1);
	}

	// else parent
	else {
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

	if(commands.size() == 1) {
		vector<char*> parsedCommand = splitSpace(commands.at(0));
		executeCommand(parsedCommand);
	}	

	else if(commands.size() > 1) {
		
		bool previous;
		int count = 0;
		vector<char*> parsedCommand = splitSpace(commands.at(0));
		previous = executeCommand(parsedCommand);		

		for(unsigned i = 1; i < commands.size(); i++) {
			// if there is an &&, 
			// execute the current command only if prev returns true
			if(connectors.at(count) == '&') {
				if(previous) {
					vector<char*> parsedCommand = splitSpace(commands.at(i));
					previous = executeCommand(parsedCommand);		
				}	
			}
			// if there is an ||
			// execute the current command only if prev returns false
			else if(connectors.at(count) == '|') {
				if(!previous) {
					vector<char*> parsedCommand = splitSpace(commands.at(i));
					previous = executeCommand(parsedCommand);					
				}
			}	
			count++;
		}
	}
}


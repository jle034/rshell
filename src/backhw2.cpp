#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

void prompt();
void removeComments(string& s);
int findThis(vector<char*> v, string s);
//string charToString(char*);
vector<char*> splitSemicolon(string userInput);
vector<char*> splitSpace(string userInput);
vector<char*> getCommands(char* charBlurb);
vector<string> getConnectors(char* blurb);
bool executeCommand(vector<char*> command);
void executeBlurb(vector<char*> commands, vector<string> connectors);


int main(int argc, char* argv[]) {

/*
	vector<char*> testVec = splitSemicolon("something;i have no idea;this");
	char* testingChar = testVec.at(0);
	string temp = charToString(testingChar);
	cout << "temp: " << temp << endl;
	cout << "testingChar: " << testingChar << endl;
	temp.append("BLAH");
	cout << "temp: " << temp << endl;
	cout << "testingChar: " << testingChar << endl;	

//	string temp = string(testVec.at(0));
//	string another = temp;
//	cout << "testVec.at(0): " << testVec.at(0) << endl;
//	temp.append("WEE");
//	cout << "temp: " << temp << endl;
//	cout << "testVec.at(0): " << testVec.at(0) << endl;
//	cout << "another: " << another << endl;
//	
//	
//	testVec.at(0) = &another.at(0);
//	cout << "testVec.at(0): " << testVec.at(0) << endl;

	vector<char*> testVec = splitSemicolon("g++ main.cpp;;somehtinghere;");
//	cout << "argc: " << argc << endl;
	for(unsigned i = 0; i < testVec.size(); i++) {
		cout << "<" << testVec.at(i) << "> ";
	}
	cout << endl;
	cout << "output: " << findThis(testVec, "ls") << endl;
	cout << "testVec after: ";
	for(unsigned i = 0; i < testVec.size(); i++) {
		cout << "<" << testVec.at(i) << "> ";
	}
	cout << endl;
*/

	while(1) {


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
			vector<char*> commandVec = getCommands(scVec.at(j));
			vector<string> connectorVec = getConnectors(scVec.at(j));
//			cout << "commandVec" << j << ": ";
//			for(unsigned k = 0; k < commandVec.size(); k++) {
//				cout << '<' << commandVec.at(k) << '>' << ' ';
//			}
//			cout << endl;
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
//			cout << "FOUND IT!!" << endl;
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

/*
string charToString(char* charPointer) {
	string temp = string(charPointer);
	string another = temp;
	return another;
}
*/

// function parses string userInput by ";"
// returns these as a vector<char*> 
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

// function uses strtok() to parse string blurb by connectors && and ||
// returns vector<char*> of all commands in the char* charBlurb
vector<char*> getCommands(char* charBlurb) {
	char* temp = charBlurb;	
	string blurb(temp);
	string hold = blurb;

	// replace connectors with these strings
	// takes care of cases where there are no spaces between connectors and commands
	string repAnd = " * ";
	string repOr = " ! ";	
	string repPipe = " | ";
	string repOut = " > ";
	string repOutOut = " >> ";
	string repIn = " < ";
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
			else if(blurb.at(i + 1) != '|') {
				blurb.replace(i, 1, repPipe);
			}
		}
		else if(blurb.at(i) == '&') {
			if(blurb.at(i + 1) == '&') {
				blurb.replace(i, 2, repAnd);
			}
		}
/*
		else if((blurb.at(i) == '>')) {
			if(blurb.at(i + 1) == '>') {
				blurb.replace(i, 2, repOutOut);
			}
			else if(blurb.at(i + 1) != '>') {
				blurb.replace(i, 1, repOut);
			}
		}
		else if(blurb.at(i) == '<') {
			blurb.replace(i, 1, repIn);
		}
*/
	}
//	cout << "blurb: " << '<' << blurb << '>' << endl;

	char* charTemp = &blurb.at(0); 
	char* token;
	token = strtok(charTemp, "!*");
//	cout << "token: " << token << endl;

	while(token != NULL) {
		string str = string(token);
		semicolonVec.push_back(token);
		if(str.size() == 0) {
//			cout << "EMPTY" << endl;
			semicolonVec.push_back(trueChar);
		}
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
/*
		else if((str.at(i) == '|') && !(str.at(i + 1) == '|')) {
			v.push_back("|");
		}
		else if(str.at(i) == '<') {
			v.push_back("<");
		}
		else if((str.at(i) == '>') && !(str.at(i + 1) == '>')) {
			v.push_back(">");
		}
		else if((str.at(i) == '>') && (str.at(i + 1) == '>')) {
			i++;
			v.push_back(">>");
		}
*/
	}
	return v;	
}

// function takes in a single command (already parsed by spaces)
// and executes the command using execvp
// returns true if command executes
// returns false if command is invalid or does not execute
bool executeCommand(vector<char*> command) {

/*
	cout << "command parsed by spaces: ";
	for(unsigned i = 0; i < command.size(); i ++) {
		cout << "<" << command.at(i) << "> ";
	}
	cout << endl;
*/	

	if(command.size() == 1) {
		string something = string(command.at(0));
		string hold = something;
		if(something == "exit") {
			exit(1);
		}
		command.at(0) = &hold.at(0);
	}
	
	int pid = fork();
	// if fork produces an error
	if(pid == -1) {
		perror("fork");
		exit(1);
	}
	
	// if child
	else if(pid == 0) {


/*
////////////////////////////////////////////////////////////////////////////////
		if(findThis(command, ">") == -2) {
			cerr << "Error: Cannot have more than one output redirection" << endl;
			exit(1);	
		}	
		else if(findThis(command, ">") >= 0) {
			cout << "FOUND ONE >" << endl;
		}

		if(findThis(command, ">>") == -2) {
			cerr << "Error: Cannot have more than one output redirection" << endl;
			exit(1);
		}
		else if(findThis(command, ">>") >= 0) {
			cout << "FOUND ONE >>" << endl;
		}

		if(findThis(command, "<") == -2) {
			cerr << "Error: Cannot have more than one input redirecton" << endl;
			exit(1);
		}
*/
		char* argv[sizeof(command) + 1];

		unsigned i = 0;
		for(i = 0; i < command.size(); i++) {
			argv[i] = command[i];
		}
		argv[i] = 0;

		if(execvp(*argv, argv) == -1) {
			perror("execvp");
			exit(1);
		}
		return true;
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

void executeBlurb(vector<char*> commands, vector<string> connectors) {

	if(commands.size() == 1) {
		string temp = string(commands.at(0));
		string hold = temp;
		vector<char*> parsedCommand = splitSpace(temp);
		commands.at(0) = &hold.at(0);
		executeCommand(parsedCommand);
	}	

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


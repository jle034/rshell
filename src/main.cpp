#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
// #include <cstring>
// #include <string.h>	
#include <errno.h>
#include <pwd.h>
// #include <vector>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
// #include <boost/foreach.hpp>

using namespace std;
using namespace boost;

// function prints the prompt to look like this:
// [userName]@[hostName] $
void prompt() {
	string userName = getlogin();
	char hostName[64];
	gethostname(hostName, sizeof(hostName));		
	cout << userName << "@" << hostName  << " $ ";
}

// function removes comments in string& userInput
// comments are denoted by a "#"
void removeComments(string& s) {
	size_t start = s.find("#");
	if (start != string::npos) {
		s.erase(start);
	}
}

// function parses string userInput by ";", " ", "&", and "|"
// this separates the userInput into the individual commands
// returns these commands as a vector<char*>
vector<string> splitSemicolons(string userInput) {
	vector<string> commandsVec;
	split(commandsVec, userInput, is_any_of(";"), token_compress_on);
	return commandsVec;
}

int main(int argc, char* argv[]) {

	while(1) {

		prompt();

		string userInput;
		getline(cin, userInput);

		if (userInput == "exit") {
			exit(0);
		}

		cout << "User Input: " << endl << userInput << endl << endl;
		removeComments(userInput);
		cout << "User Input W/O Comments: " << endl << userInput << endl << endl;

		vector<string> wordVec  = splitSemicolons(userInput);
		cout << "userInput split by semicolons: " << endl;
		for (int i = 0; i < wordVec.size(); i++) {
			cout << wordVec.at(i) << endl;
		}	
		cout << endl;

	}
	return 0;
}

/*

// function parses string userInput by ";"
// this separates the userInput into the individual commands
// returns these commands as a vector<char*>
vector<char*> splitSemiColon(string userInput) {
	string semicolonString = userInput;
	char* semicolonInput = (char*)semicolonString.c_str();
	vector <char*> semicolonVec;		

	char* semicolonToken;
	semicolonToken = strtok(semicolonInput, "; &|");

	while(semicolonToken != NULL) {
		semicolonVec.push_back(semicolonToken);
		semicolonToken = strtok(NULL, "; &|");
	}
	return semicolonVec;
}

// function parses string userInput by " "
// returns these as a vector<char*>
vector<char*> splitSpace(string userInput) {
	string spaceString = userInput;
	char* spaceInput = (char*)spaceString.c_str();
	vector<char*> spaceVec;

	char* currToken;
	currToken = strtok(spaceInput, " ");

	while(currToken != NULL) {
		spaceVec.push_back(currToken);
		currToken = strtok(NULL, " ");
	}
	return spaceVec;
}

int main(int argc, char* argv[]) {

	while(1) {
		
		cout << "$ ";

		string userInput;
		getline(cin, userInput);

		if (userInput == "exit") {
			exit(0);
		}

		cout << "User Input: " << endl << userInput << endl;
		removeComments(userInput);
		cout << "User Input W/O Comments: " << endl << userInput << endl;

		string semicolon_userInput = userInput;

		vector<char*> commandVec = splitSemiColon(semicolon_userInput);
		cout << "userInput split by semicolons: " << endl;
		for (int i = 0; i < commandVec.size(); i++) {
			cout << commandVec.at(i) << endl;
		}	
		cout << endl;
		cout << "userInput after parsing semicolons: " << userInput << endl << endl;
		

		string space_userInput = userInput;
		cout << "Space User Input: " << space_userInput << endl;		

		vector<char*> spaceVec = splitSpace(space_userInput);
		cout << "spaceVec.size() = " << spaceVec.size() << endl;
		cout << "userInput split by spaces: " << endl;
		for (int i = 0; i < spaceVec.size(); i++) {
			cout << spaceVec.at(i) << endl;
		}
		cout << endl;
		cout << "userInput: " << userInput << endl << endl;

	}
	return 0;
}
*/


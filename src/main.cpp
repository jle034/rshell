#include <iostream>
// #include <stdio.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <stdlib.h>
// #include <cstring>
// #include <string.h>	
// #include <errno.h>
// #include <pwd.h>
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

// function removes comments in string& s
// comments are denoted by a "#"
void removeComments(string& s) {
	size_t start = s.find("#");
	if (start != string::npos) {
		s.erase(start);
	}
}

// function parses string userInput by ";"
// returns these commands in a vector<string>
vector<string> splitSemicolons(string userInput) {
	vector<string> tokenVec;
	split(tokenVec, userInput, is_any_of(";"), token_compress_on);
	return tokenVec;
}

// function parses string userInput by "&&"
// returns these commands in a vector<string>
vector<string> splitAnds(string userInput) {
	vector<string> tokenVec;
	split(tokenVec, userInput, is_any_of("&&"), token_compress_on);
	return tokenVec;
}

// function parses string userInput by "||"
// return these commands in a vector<string>
vector<string> splitOrs(string userInput) {
	vector<string> tokenVec;
	split(tokenVec, userInput, is_any_of("||"), token_compress_on);
	return tokenVec;
}

void removeSpaces(string& blurb) {
	string temp = blurb;

	// remove spaces from beginning
	int i = 0;
	int begin = 0;
	if(temp.at(0) != ' ') {
		begin = 0;
	}	
	else {
		while(temp.at(i) == ' ') {
			i++;	
		}
		begin = i;
	}

	// remove spaces from end
	int end = 0;
	i = temp.size() - 1;
	if(temp.at(temp.size()-1) != ' ') {
		end = temp.size()-1;
	}
	else {
		while(temp.at(i) == ' ') {
			i--;
		}
		end = i;
	}

	// cut substring from begin to end
	temp = temp.substr(begin, end - begin + 1);

	/*********************************************************
  		REMOVE WHITESPACE FROM INSIDE STRING HERE!!!
  	*********************************************************/		

	blurb = temp;
}


int main(int argc, char* argv[]) {

	while(1) {

		// outputs the prompt
		prompt();

		// gets input and stores in userInput
		string userInput;
		getline(cin, userInput);

		// exits program if user inputs "exit"
		if (userInput == "exit") {
			exit(0);
		}
		
/*
		cout << "User Input: " << '|' << userInput << '|' << endl << endl;
		removeSpaces(userInput);
		cout << "User Input: " << '|' << userInput << '|' <<  endl << endl;
*/
	
		// remove comments found after "#"
		cout << "User Input: " << endl << userInput << endl << endl;
		removeComments(userInput);
		cout << "User Input W/O Comments: " << endl << userInput << endl << endl;

		// parse userInput by semicolons
		// store in wordVec
		vector<string> semicolonVec  = splitSemicolons(userInput);

		for (int i = 0; i < semicolonVec.size(); i++) {
				
			cout << semicolonVec.at(i) << endl;
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


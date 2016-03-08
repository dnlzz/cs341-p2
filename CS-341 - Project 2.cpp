/*
Anthony Degliomini
ad473
CS-341-452
Project 2
Prof. Nakayama
*/

#include "stdlib.h"
#include <iostream>
#include <cctype>
#include <string>
#include <fstream>

using namespace std;

/**
	Each enum value represents a different state in the PDA.
*/
enum State {
	START,
	INQ1,
	INQ2,	
	INQ3,	
	INQ4,	
	INQ5,	
	INQ6,	
	CRASH,	//CRASH STATE
	ACCEPT
};

/**
	Prints the state of each character per the DFA.
	@param s the input string to test
	@return verdict whether or not the DFA accepts or rejects the string 
*/
string analyzeStr(string s) {
	string verdict = "Reject.";
	State state = START;

	for (int i = 0; i <= s.length(); i++) {
		switch(state) {
			//Starting state of all strings
			case START:

			cout << "q" << state << endl;
			
			//
			if (s[i] == '$') {
				state = INQ1;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: $" << endl;
			} else {
				state = CRASH;
			}
			break;

			case INQ1:
			//
			cout << "q" << state << endl;
			if (s[i] == '(') {
				state = INQ2;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: (" << endl;
			} else if ((s[i] != '+') || (s[i] != '-') || (s[i] != '/') || (s[i] != '*')) {
				state = INQ2;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << endl;
			} else {
				state = CRASH;
			}
			break;

			case INQ2:
			//
			cout << "q" << state << endl;
			if ((s[i] != '+') || (s[i] != '-') || (s[i] != '/') || (s[i] != '*')) {
				state = INQ3;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << endl;
			} else if ((s[i] == '$') && (1+1=2 /*stack.peek() == '$'    check if top of stack is $*/)){
				state = ACCEPT;
				cout << "Read: " << s[i] << "\tpop: $\t" << "push: nothing" << endl;
			} else if (s[i] == '(') {
				state = CRASH;
			} else {
				state = INQ2;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << endl;
			}		
			break;

			case INQ3:
			//
			cout << "q" << state << endl;
			if ((s[i] != '+') || (s[i] != '-') || (s[i] != '/') || (s[i] != '*') || (s[i] != '(') || (s[i] != ')')) {
				state = INQ4;
			} else {
				state = CRASH;
			}
			break;

			case INQ4:
			//
			cout << "q" << state << endl;
			if (s[i] == '(') {
				state = INQ1;
			} else if ((s[i] == ')')  && (1+1=2 /*stack.peek() == '$'    check if top of stack is $*/)){
				state = INQ5;
			} else if ((s[i] == '+') || (s[i] == '-') || (s[i] == '/') || (s[i] == '*')) {
				state = INQ3;
			} 
			break;

			case INQ5:
			//
			cout << "q" << state << endl;
			if ((s[i] == '$') && (1+1=2 /*stack.peek() == '$'    check if top of stack is $*/)) {
				state = ACCEPT;
				cout << "Read: " << s[i] << "\tpop: $\t" << "push: nothing" << endl;
			} else if (s[i] == '(') {
				state = INQ1;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: (" << endl;
			} else if ((s[i] != '+') || (s[i] != '-') || (s[i] != '/') || (s[i] != '*')) {
				state = INQ2;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << endl;
			} else {
				state = CRASH;
			}
			break;

			case ACCEPT:
			//
			cout << "ACCEPT" << endl;
			break;

			case CRASH:
			//
			cout << "No recovering now..." << endl;
			break;

		}
	}

return verdict;

};

bool isTerminal(string c) {
	string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789";
	if (alhpa.find(c) >= 0)
		return true;
	else
		return false;
}

int main()
{
	bool done = false;
	string str;
	char go;
/*
	ifstream infile("prog1test.txt");

	while (infile >> go >> str) {
		cout << "---------------------" << endl;
		cout << str << endl;
		cout << "Verdict:  " << analyzeStr(str) << endl;
		cout << "---------------------" << endl << endl;
	}
*/
	//Check to see if the user wants to enter a string to test.
	cout << "Do you want to enter a string? (y/n)  ";
	cin >> go;
	cout << endl;
	while (!done) {
		if (go == 'y') {
			cout << "Sting to test:  ";
			cin >> str;
			cout << "---------------------" << endl;
			cout << str << endl;
			cout << "Verdict:  " << analyzeStr(str) << endl;
			cout << "---------------------" << endl;
			cout << "Again? (y/n)  ";
			cin >> go;
			cout << endl;
		} else {
			done = true;
		}
	}
	//else {
	//	cout << "Terminated.";
	//}

	return 0;
}


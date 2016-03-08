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
#include <stack>

#define TRUE 1;

using namespace std;

bool isTerminal(char c);
bool isOperator(char c);

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
	stack<char> stk;

	for (int i = 0; i <= s.length(); i++) {
		switch(state) {
			//Starting state of all strings
			case START:

			cout << "q" << state << endl;
			
			//
			if (s[i] == '$') {
				state = INQ1;
				stk.push('$');
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: $\t" << "TOS: " << stk.top() << endl;
			} else {
				state = CRASH;
			}
			break;

			case INQ1:
			//
			cout << "q" << state << endl;
			if (s[i] == '(') {
				state = INQ1;
				stk.push('(');
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: ("  << "TOS: " << stk.top()<< endl;
			} else if (isOperator(s[i])) {
				state = CRASH;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing"  << "TOS: " << stk.top()<< endl;
			} else if (isTerminal(s[i])) {
				state = INQ2;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			}
			break;

			case INQ2:
			//
			cout << "q" << state << endl;
			if ((s[i] == '$') && (stk.top() == '$') ){
				state = ACCEPT;
				cout << "Read: " << s[i] << "\tpop: $\t" << "push: nothing" << "TOS: " << "stack empty" << endl;
			} else if (isTerminal(s[i])) {
				state = INQ2;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			} else if (isOperator(s[i])) {
				state = INQ3;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			} else if ((s[i] == ')') && (stk.top() == '(')) {
				state = INQ5;
				stk.pop();
				cout << "Read: " << s[i] << "\tpop: (\t" << "push: nothing"  << "TOS: " << stk.top()<< endl;
			} else {
				state = CRASH;
				cout << "Read: " << s[i] << "\tpop: (\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			}
			/*
			if ((s[i] != '+') || (s[i] != '-') || (s[i] != '/') || (s[i] != '*')) {
				state = INQ3;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			} else if ((s[i] == '$') && (stk.top() == '$') ){
				state = ACCEPT;
				cout << "Read: " << s[i] << "\tpop: $\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			} else if(s[i] == '(') {
				state = INQ1;
				stk.push('(');
			} else {
				state = INQ2;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			}	
			*/	
			break;

			case INQ3:
			//
			cout << "q" << state << endl;
			if (isTerminal(s[i])) {
				state = INQ4;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			} else if (s[i] == '(') {
				state = INQ1;
				stk.push('(');
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: ("  << "TOS: " << stk.top()<< endl;
			} else {
				state = CRASH;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			}
			break;


			case INQ4:
			//
			cout << "q" << state << endl;
			if ((s[i] == '$') && (stk.top() == '$') ){
				state = ACCEPT;
				cout << "Read: " << s[i] << "\tpop: $\t" << "push: nothing" << "TOS: " << "stack empty" << endl;
			} else if ((s[i] == ')') && (stk.top() == '(')) {
				state = INQ5;
				stk.pop();
				cout << "Read: " << s[i] << "\tpop: (\t" << "push: nothing"  << "TOS: " << stk.top()<< endl;
			} else if (isTerminal(s[i])) {
				state = INQ4;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			} else if (s[i] == '(') {
				state = INQ1;
				stk.push('(');
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: ("  << "TOS: " << stk.top()<< endl;
			} else if (isOperator(s[i])) {
				state = INQ3;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			} else {
				state = CRASH;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			}


			/*
			if (s[i] == '(') {
				state = INQ1;
				stk.push('(');
					cout << "Read: " << s[i] << "\tpop: (\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			} else if ((s[i] == ')')  && (stk.top() == '(')){
				state = INQ5;
				stk.pop();
				cout << "Read: " << s[i] << "\tpop: (\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			} else if ((s[i] == ')')  && (stk.top() != '(')){
				state = CRASH;
				cout << "Read: " << s[i] << "\tpop: ( FAILED\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			} else if ((s[i] == '+') || (s[i] == '-') || (s[i] == '/') || (s[i] == '*')) {
				state = INQ3;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			} else if ((s[i] == '$') && (stk.top() == '$')){
				state = ACCEPT;
				cout << "Read: " << s[i] << "\tpop: $\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			} else {
				state = INQ4;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			}
			*/
			break;

			case INQ5:
			//
			cout << "q" << state << endl;
			if ((s[i] == '$') && (stk.top() == '$') ){
				state = ACCEPT;
				cout << "Read: " << s[i] << "\tpop: $\t" << "push: nothing" << "TOS: " << "stack empty" << endl;
			} else if (s[i] == '(') {
				state = INQ1;
				stk.push('(');
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: ("  << "TOS: " << stk.top()<< endl;
			} else if (isTerminal(s[i])) {
				state = INQ2;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			} else if (s[i] == ')') {
				state = INQ5;
				stk.pop();
				cout << "Read: " << s[i] << "\tpop: (\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			} else if (isOperator(s[i])) {
				state = INQ3;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			} else {
				state = CRASH;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			}
			/*
			if ((s[i] == '$') && (stk.top() == '$' )) {
				state = ACCEPT;
				cout << "Read: " << s[i] << "\tpop: $\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			} else if (s[i] == '(') {
				state = INQ1;
				stk.push('(');
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: (" << "TOS: " << stk.top() << endl;
			} else if ((s[i] == ')') && (stk.top() == '(') ){
				state = INQ5;
				stk.pop();
				cout << "Read: " << s[i] << "\tpop: (\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			} else if ((s[i] != '+') || (s[i] != '-') || (s[i] != '/') || (s[i] != '*')) {
				state = INQ2;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing" << "TOS: " << stk.top() << endl;
			} else {
				state = CRASH;
			}

			*/
			break;

			case ACCEPT:
			//
			verdict = "Accept.";
			break;

			case CRASH:
			//
			cout << "No recovering now..." << endl;
			return verdict;
			break;

		}
	}

return verdict;

};


bool isTerminal(char c) {
	string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789";
	if (alpha.find(c) != string::npos)
		return true;
	else
		return false;
}

bool isOperator(char c) {
	string alpha = "+-*/";
	if (alpha.find(c) != string::npos)
		return true;
	else
		return false;
}

int main()
{
	bool done = false;
	string str;
	char go;

	ifstream infile("prog2test.txt");

	while (infile >> go >> str) {
		cout << "---------------------" << endl;
		cout << str << endl;
		cout << "Verdict:  " << analyzeStr(str) << endl;
		cout << "---------------------" << endl << endl;
	}

/*
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

*/
	//else {
	//	cout << "Terminated.";
	//}

	return 0;
}


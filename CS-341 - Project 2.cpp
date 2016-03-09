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

using namespace std;

bool isTerminal(char c);
bool isOperator(char c);

/**
	Each enum value represents a different state in the PDA.
*/
enum State {
	START,	//START STATE
	INQ1,
	INQ2,	
	INQ3,	
	INQ4,	
	INQ5,		
	CRASH,	//CRASH STATE
	ACCEPT  //ACCEPT STATE
};

/**
	Prints the state of each character per the PDA.
	@param s the input string to test
	@return verdict whether or not the PDA accepts or rejects the string 
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
			
			//Starting state pushes a $ onto the stack to keep track of the bottom of the stack.
			if (s[i] == '$') {
				state = INQ1;
				stk.push('$');
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: $\t" << "TOS: " << stk.top() << endl;
			} else {
				state = CRASH;
			}
			break;

			case INQ1:
			//We need to check if our string starts with a '(' or a letter and make sure it
			//doesn't start with an operator.
			cout << "q" << state << endl;
			if (s[i] == '(') {
				state = INQ1;
				stk.push('(');
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: (\t"  << "TOS: " << stk.top()<< endl;
			} else if (isOperator(s[i])) {
				state = CRASH;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing\t"  << "TOS: " << stk.top()<< endl;
			} else if (isTerminal(s[i])) {
				state = INQ2;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing\t" << "TOS: " << stk.top() << endl;
			}
			break;

			case INQ2:
			//If our string starts with a letter and is followed by only letters we can keep accumulating 
			//characters and eventually accept the string as long as the stack still has a '$'' on top.
			//If we come across an operator, this will be valid because there was a terminal that was already read.
			//If we read a ')' in this state, and the top of the stack shows a '(' this is acceptable.
			//Reading any other characters is invvalid.
			cout << "q" << state << endl;
			if ((s[i] == '$') && (stk.top() == '$') ){
				state = ACCEPT;
				cout << "Read: " << s[i] << "\tpop: $\t" << "push: nothing\t" << "TOS: " << "stack empty" << endl;
			} else if (isTerminal(s[i])) {
				state = INQ2;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing\t" << "TOS: " << stk.top() << endl;
			} else if (isOperator(s[i])) {
				state = INQ3;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing\t" << "TOS: " << stk.top() << endl;
			} else if ((s[i] == ')') && (stk.top() == '(')) {
				state = INQ5;
				stk.pop();
				cout << "Read: " << s[i] << "\tpop: (\t" << "push: nothing\t"  << "TOS: " << stk.top()<< endl;
			} else {
				state = CRASH;
				cout << "Read: " << s[i] << "\tpop: (\t" << "push: nothing\t" << "TOS: " << stk.top() << endl;
			}

			break;

			case INQ3:
			//We have just seen an operator and are now accumulating either terminals or starting to read more '('
			//Reading any other characters are invvalid.
			cout << "q" << state << endl;
			if (isTerminal(s[i])) {
				state = INQ4;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing\t" << "TOS: " << stk.top() << endl;
			} else if (s[i] == '(') {
				state = INQ1;
				stk.push('(');
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: (\t"  << "TOS: " << stk.top()<< endl;
			} else {
				state = CRASH;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing\t" << "TOS: " << stk.top() << endl;
			}
			break;


			case INQ4:
			//If we read a terminal we stay in this state and can continue to read but must eventually read a ')'
			//assuming there is a '(' already read previously.
			//If no '(' have been read this far, but operators were read, this can also transition to the accepting state
			//as long as the stack still has a '$'' on top.
			//If an operator is read, we transition to the appropriate state. 
			cout << "q" << state << endl;
			if ((s[i] == '$') && (stk.top() == '$') ){
				state = ACCEPT;
				cout << "Read: " << s[i] << "\tpop: $\t" << "push: nothing\t" << "TOS: " << "stack empty" << endl;
			} else if ((s[i] == ')') && (stk.top() == '(')) {
				state = INQ5;
				stk.pop();
				cout << "Read: " << s[i] << "\tpop: (\t" << "push: nothing\t"  << "TOS: " << stk.top()<< endl;
			} else if (isTerminal(s[i])) {
				state = INQ4;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing\t" << "TOS: " << stk.top() << endl;
			} else if (s[i] == '(') {
				state = INQ1;
				stk.push('(');
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: (\t"  << "TOS: " << stk.top()<< endl;
			} else if (isOperator(s[i])) {
				state = INQ3;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing\t" << "TOS: " << stk.top() << endl;
			} else {
				state = CRASH;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing\t" << "TOS: " << stk.top() << endl;
			}

			break;

			case INQ5:
			//If we read and popped a '(' and ')' in the previous state, we may be able to read a '$'
			//as our last character before the end of the string. This will lead to us accepting the input string.
			//We can start a new "batch" of '()' or start accumulating terminals.
			//We stay in this state reading and popping ')' until the stack has no more '(' to pop.
			//We can also read an operator and will transition to the appropriate state.
			cout << "q" << state << endl;
			if ((s[i] == '$') && (stk.top() == '$') ){
				state = ACCEPT;
				cout << "Read: " << s[i] << "\tpop: $\t" << "push: nothing\t" << "TOS: " << "stack empty" << endl;
			} else if (s[i] == '(') {
				state = INQ1;
				stk.push('(');
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: (\t"  << "TOS: " << stk.top()<< endl;
			} else if (isTerminal(s[i])) {
				state = INQ2;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing\t" << "TOS: " << stk.top() << endl;
			} else if (s[i] == ')') {
				state = INQ5;
				stk.pop();
				cout << "Read: " << s[i] << "\tpop: (\t" << "push: nothing\t" << "TOS: " << stk.top() << endl;
			} else if (isOperator(s[i])) {
				state = INQ3;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing\t" << "TOS: " << stk.top() << endl;
			} else {
				state = CRASH;
				cout << "Read: " << s[i] << "\tpop: nothing\t" << "push: nothing\t" << "TOS: " << stk.top() << endl;
			}

			break;

			case ACCEPT:
			//We have read the correct input and the last character read was a '$'
			verdict = "Accept.";
			break;

			case CRASH:
			//Something went terribly, terribly wrong.
			//We are in trouble.
			cout << "No recovering now..." << endl;
			return verdict;
			break;

		}
	}

return verdict;

};

//Checks to see if our current character is in the list of terminals.
bool isTerminal(char c) {
	string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789";
	if (alpha.find(c) != string::npos)
		return true;
	else
		return false;
}

//Checks to see if our current character is in the list of operators.
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


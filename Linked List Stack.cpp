#pragma warning( disable : 26451)    // Suppress casting double to unsigned int.

#include "Linked List Stack.h"

using namespace std;

template <class T>
Node<T>::Node()			// The constructor, responsible for initialising the variables of type T and Node*.
{
	data = {};
	next = {};
	top = {};
};

template <class T>
void Node<T>::push(const T& data)		// The function that handles pushing new data onto the stack:
{
	// create new temp node and allocate memory to the new Node:
	Node<T>* temp = new Node<T>;

	// check if the stack is full - stack overflow, if not push the data onto the stack:
	if (!temp)
	{
		throw out_of_range("Exception: Stack<T>::push() cannot be done as there is a stack overflow!");
		return;
	}

	// parse the data into the temp Node:
	temp->data = data;

	// allocate the pointer reference top to the next node in temp:
	temp->next = top;

	// make temp the top of the stack:
	top = temp;

	// output that the data has been successfully pushed onto the stack in the console:
	cout << "Node " << data << " has been pushed onto the stack." << endl;
};

template <class T>
void Node<T>::pop()			// The function that is responsible for removing the top item from the stack.
{
	// create new temp node and allocate memory to the new Node:
	Node<T>* temp = new Node<T>;

	// check for the stack being empty - stack underflow, if not then remove the data at the top of the stack:
	if (top == NULL)
	{
		throw out_of_range("Exception: Stack<T>::pop() cannot be done as there is no data in the stack / STACK UNDERFLOW.");
		return;
	}
	else
	{
		// assign top to the temp node:
		temp = top;

		// assign the second node to the top node:
		top = top->next;

		// destroy the link between the first and second node:
		temp->next = NULL;

		// release the memory held by the top node that has been removed:
		delete temp;

		// display in the console that the node has been successfully popped:
		cout << "The top node has been popped." << endl;
	}
};

template <class T>
const T Node<T>::peek()		// The function responsible for displaying the node at the top of the stack.
{
	// check there is data in the stack:
	if (top == 0)
	{
		throw out_of_range("Exception: Stack<T>::peek() cannot be done as there is no data in the stack.");
	}

	// display the top node in the console:
	cout << "The item currently on top of the stack is: " << top->data << endl;

	return top->data;
};


template <class T>
int Node<T>::isEmpty()		// The function responsible for determining and displaying if the stack is empty:
{
	if (top != NULL)
	{
		cout << "The stack is not empty." << endl;
		return 0;
	}
	else if (top == NULL)
	{
		cout << "The stack is empty." << endl;
		return 1;
	}
	return 0;
};


template <class T>
void Node<T>::stringReversal()    // This part of the program is so simple that it doesnt require its own class, so i just implemented it as a stack function.
{
	string word = "";
	int wordLength = 14;
	string finalLetter = "";

	while (wordLength > 13)
	{
		word = "";
		cout << "Enter a word to be reversed: ";
		cin >> word;

		wordLength = word.length();

		if (wordLength > 13)
		{
			cout << "Word cannot be more than 13 characters, enter a shorter word: ";
		}
	}

	// easiest way to do this is to select each char from the word, parse as a string using stringStack.
	for (int i = 0; i < word.length(); ++i)
	{
		char ch = word.at(i);
		string word{ch};
		push(word);

		if (i == (wordLength - 1))
		{
			finalLetter = word;
		}
	}

	// create new temp node and allocate memory to the new Node:
	Node<T>* temp = new Node<T>;

	// check for stack underflow:
	if (top == NULL)
	{
		throw out_of_range("Exception: Stack<T>::stringReversal() cannot be done as there is no data in the stack / STACK UNDERFLOW.");
		return;
	}
	else
	{
		// assign top to the temp node:
		temp = top;

		// display to the console the stack:
		cout << "Reversed String: ";
		while (temp != NULL)
		{
			// print the contents of the stack:
			cout << temp->data;

			// assign the temp next node to the temp node:
			temp = temp->next;
		}
		cout << endl;
	}

	// Final letter requirement:
	string input = "";

	while (input != "Y" && input != "y" && input != "N" && input != "n")
	{
		cout << "Would you like to see the last letter of the input word? (Y/N)";
		cin >> input;

		if (input == "Y" || input == "y")
		{
			cout << "Final letter is: " << finalLetter << endl;
		}
		else if (input == "N" || input == "n")
		{
			break;
		}
		else
		{
			cout << "Enter Y/N: ";
		}
	}
};

// Expression conversion class utlizises the stack but is not a function of it - all functions below use my stack - char/double/int stack(s)!
// Check for operators (+-*/)
bool ExpressionConverter::isOperator(char c)
{
	return (!isalpha(c) && !isdigit(c));
};

// Check for operands (numbers) in the expression.
bool ExpressionConverter::isOperand(char c)
{
	// If the character is a digit then it must 
	// be an operand 
	return isdigit(c);
};

// Allocate BODMAS Priority.
int ExpressionConverter::getPriority(char C)
{
	if (C == '-' || C == '+')
		return 1;
	else if (C == '*' || C == '/')
		return 2;
	else if (C == '^')
		return 3;
	return 0;
};

// convert infix to postfix
string ExpressionConverter::infixToPostfix(string infix)
{
	infix = '(' + infix + ')';
	int l = infix.size();
	Node<char>* char_stack = new Node<char>();    // My stack- char_stack.
	string output;

	for (int i = 0; i < l; i++) {

		// If the scanned character is an operand, add it to output.
		if (isalpha(infix[i]) || isdigit(infix[i]))
		{
			output += infix[i];
		}
		// If the scanned character is '(', push it to the stack.
		else if (infix[i] == '(')
		{
			char_stack->push('(');
		}
		// If the scanned character is ')', pop and output from the stack until '(' is encountered.
		else if (infix[i] == ')')
		{
			while (char_stack->peek() != '(')
			{
				output += char_stack->peek();
				char_stack->pop();
			}
			// Remove '(' from the stack
			char_stack->pop();
		}
		else    // Operator found
		{
			if (isOperator(char_stack->peek()))
			{
				while ((getPriority(infix[i]) < getPriority(char_stack->peek())) || (getPriority(infix[i])
					<= getPriority(char_stack->peek()) && infix[i] == '^'))    // also account for powers (^).
				{
					output += char_stack->peek();
					char_stack->pop();
				}

				// Push current Operator on stack
				char_stack->push(infix[i]);
			}
		}
	}
	return output;
};

// convert infix to prefix
string ExpressionConverter::infixToPrefix(string infix)
{
	int expressionSize = infix.size();

	// Reverse infix
	reverse(infix.begin(), infix.end());

	// Replace ( with ) and vice versa
	for (int i = 0; i < expressionSize; i++) {

		if (infix[i] == '(') 
		{
			infix[i] = ')';
			i++;
		}
		else if (infix[i] == ')') 
		{
			infix[i] = '(';
			i++;
		}
	}
	string prefix = infixToPostfix(infix);

	// Reverse postfix to become prefix.
	reverse(prefix.begin(), prefix.end());

	return prefix;
};

// Evaluate a Prefix expression. - Uses a double_stack.
double ExpressionConverter::evaluatePrefix(string exprsn)
{
	// intantiate an object of our Linked List Stack ADT of type double - double_stack. 
	struct Node<double>* double_stack = new Node<double>;

	for (int j = exprsn.size() - 1; j >= 0; j--) 
	{
		// Push operand to Stack To convert exprsn[j] to digit subtract '0' from exprsn[j]. 
		if (isOperand(exprsn[j]))
		{
			double_stack->push(exprsn[j] - '0');
		}
		else
		{
			// Operator encountered - So pop two elements from Stack 
			double operator1 = double_stack->peek();
			double_stack->pop();
			double operator2 = double_stack->peek();
			double_stack->pop();

			// Use switch case to operate on operator1 and operator2 and perform operator1 "Operand" operator2. 
			switch (exprsn[j]) 
			{
			case '+':
				double_stack->push(operator1 + operator2);
				break;
			case '-':
				double_stack->push(operator1 - operator2);
				break;
			case '*':
				double_stack->push(operator1 * operator2);
				break;
			case '/':
				double_stack->push(operator1 / operator2);
				break;
			}
		}
	}

	return double_stack->peek();
};

// evalutate a Postfix expression. - Uses an int_stack.
int ExpressionConverter::evaluatePostfix(char* exp)
{
	// intantiate an object of our Linked List Stack ADT of type double - char_stack. 
	struct Node<int>* int_stack = new Node<int>;
	int i = 0;

	// Scan all characters one by one  
	for (i = 0; exp[i]; ++i)
	{
		//if the character is blank space then continue  
		if (exp[i] == ' ') { continue; }

		// If the scanned character is an operand (number here), push it to the stack.  
		else if (isdigit(exp[i]))
		{
			int_stack->push(exp[i] - '0');
		}

		// If the scanned character is an operator, pop two elements from stack then apply the operator "case exp[i]". 
		else
		{
			int val1 = int_stack->peek();
			int_stack->pop();
			int val2 = int_stack->peek();
			int_stack->pop();

			switch (exp[i])
			{
			case '+': int_stack->push(val2 + val1); break;
			case '-': int_stack->push(val2 - val1); break;
			case '*': int_stack->push(val2 * val1); break;
			case '/': int_stack->push(val2 / val1); break;
			}
		}
	}
	return int_stack->peek();
};


// The main function, where the objects of the stack template are created, and the functions called.
int main()
{
	try	// try is to pass any exceptions to catch.
	{
		// String reversal: (Handled in the stack so no need for lots of main code.)
		//intantiate an object of our Linked List Stack ADT of type string - string_stack for string reversal.
		Node<string>* stringStack = new Node<string>();

		stringStack->stringReversal();

		delete stringStack;    // clean up memory from stack object instantiation.
		cout << endl;
		system("pause");    // Wait for user input

		// Expression Conversion: (External class to stack, so lots of testing and assignments happening in main.)
		//intantiate an object of our ExpressionConverter class to perform our infix->Pre/Postfix conversions/evaluations.
		ExpressionConverter* EC = new ExpressionConverter();

		string expression = "";    // User expression to convert/evaluate.

		cout << endl << "-------------------STACK OPERATIONS----------------------" << endl;

		cout << "Enter an expression (Max 4 Numbers with the operators (+ - * /) )";
		cin >> expression;

		cout << endl << "-------------------Prefix Conversion----------------------" << endl;
		string Prefix = EC->infixToPrefix(expression);

		cout << endl << "-------------------Postfix Conversion----------------------" << endl;
		string Postfix = EC->infixToPostfix(expression);

		cout << endl << "-------------------Results----------------------" << endl;
		cout << endl << "Expression in Infix (Original) is: " << expression << endl;
		cout << "Expression In Prefix is: " << Prefix << endl;
		cout << "Expression In Postfix is: " << Postfix << endl << endl;

		system("pause");    // wait for user input.

		// Expression Evaluation.
		cout << endl << "----------------------------EVALUATION STACK OPERATIONS-------------------" << endl;

		// Expression evaluation from Prefix.
		cout << endl << "----------------------------Prefix Evaluation OPERATION-------------------" << endl;
		double PrefixEvaluated = EC->evaluatePrefix(Prefix);

		// Expression evaluation from Postfix.
		cout << endl << "----------------------------Postfix Evaluation OPERATION-------------------" << endl;
		char* PostfixChar = &Postfix[0];
		int PostfixEvaluated = EC->evaluatePostfix(PostfixChar);

		// Expression evaluation Results.
		cout << endl << "----------------------------Prefix + Postfix Evaluation OPERATION RESULTS-------------------" << endl;
		cout << endl << "Original Expression (Infix): " << "'" << expression << "'" << endl;
		cout << endl << "The Prefix Expression: " << "'" << Prefix << "'" << " Evaluated equals: " << PrefixEvaluated << endl;
		cout << "The Postfix Expression: " << "'" << Postfix << "'" << " Evaluated equals: " << PostfixEvaluated << endl << endl;

		delete EC;    // clean up memory from ExpressionConverter object instantiation.
	}
	catch (const exception& ex)			// This handles the exceptions defined in the functions, causing the program to exit correctly.
	{
		cout << ex.what() << endl;
	}

	system("pause");    // User input ends the program.
	return 0;
};
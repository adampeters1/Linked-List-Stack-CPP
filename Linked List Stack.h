#pragma once

#include <iostream>
#include <string>

using namespace std;

class ExpressionConverter
{
public:
	bool isOperator(char c);
	bool isOperand(char c);
	int getPriority(char C);
	string infixToPostfix(string infix);
	string infixToPrefix(string infix);
	int evaluatePostfix(char* exp);
	double evaluatePrefix(string exprsn);
};

template <class T>
class Node			// This declares all of our variables and methods for our template stack class (Node).
{
private:
	T data;
	Node* next;
	Node* top;
public:
	Node();    // constructor

	void push(const T& data);
	void pop();
	const T peek();
	int isEmpty();

	void stringReversal();
};



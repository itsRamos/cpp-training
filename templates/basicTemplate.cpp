// Basic example of a template
// author: Erick Ramos
// date: January 31, 2018

#include <iostream>
#include <vector>
using namespace std;

template<class T>
T minimum(T number1, T number2) {
	return (number1 < number2) ? number1 : number2;
}

template<class T>
T maximum(T number1, T number2) {
	return (number1 > number2) ? number1 : number2;
}

// The main function
int main() {
    
	// Test with T arguments.
	int num1 = 5;
	int num2 = 3;
	cout << "minimum of 5, 3 is:  " ;
	cout << minimum(num1, num2) << endl;
	cout << "maximum of 5, 3 is:  " ;
	cout << maximum(num1, num2) << endl;

	// Test with double arguments.
	double num3 = 5.5;
	double num4 = 3.5;
	cout << "minimum of 5.5, 3.5 is:  " ;
	cout << minimum(num3, num4) << endl;
	cout << "maximum of 5.5, 3.5 is:  " ;
	cout << maximum(num3, num4) << endl;

	// Test with string arguments.
	string hello = "hello";
	string hi = "hi";
	cout << "minimum of \"hello\" and \"hi\" is: ";
	cout << minimum(hello, hi) << endl;
	cout << "maximum of \"hello\" and \"hi\" is: ";
	cout << maximum(hello, hi) << endl;

	return 0;
}

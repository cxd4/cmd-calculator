/************************************************************/
/*															*/
/* Created by Ryan Collins 2012-2013, use at your own risk.	*/
/*															*/
/************************************************************/

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	while(true)
	{
		double num1, num2;
		cout << "Please enter a number: ";
		cin >> num1;
		cout << "Please enter another number: ";
		cin >> num2;

		// Add first and second number
		cout << num1 << " + " << num2 << " = " << num1 + num2 << endl;

		// Subtract first and second number
		cout << num1 << " - " << num2 << " = " << num1 - num2 << endl;

		// Multiply first and second number
		cout << num1 << " * " << num2 << " = " << num1 * num2 << endl;

		// Divide first and second number
		// Make sure not to divide by zero, prevents crashing
		if (num2 == 0)
			cout << "Error cannot divide by 0" << endl;
		else
			cout << num1 << " / " << num2 << " = " << num1 / num2 << endl;

		// Square root of first number
		cout << "The square root of " << num1 << " is " << sqrt(num1) << endl;

		// Square root of second number
		cout << "The square root of " << num2 << " is " << sqrt(num2) << endl;

		// First number to the power of the second number
		cout << num1 << " to the power of " << num2 << " is " << pow(num1, num2) << endl;

		// Find the larger of the two numbers, if any
		if (num1 == num2)
			cout << "The two numbers are equal" << endl;
		else
		{
			if (num1 > num2)
				cout << num1 << " is larger than " << num2 << endl;
			if (num1 < num2)
				cout << num2 << " is larger than " << num1 << endl;
		}
		cout << "----------------------------------" << endl;
	}
}
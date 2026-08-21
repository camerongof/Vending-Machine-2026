#pragma once

#include "machineHeader.h"
#include <iostream>
#include <iomanip>
#include <stack>


VendingMachine::VendingMachine()
{
	programStart();
}

void VendingMachine::programStart()
{
	setPrice();
}

/*void VendingMachine::intial()
{
	int i, n;

	// the below will check if any cell/stack is empty and if so will load that cell with the value 0
	//row A
	if (i == 0)
	{
		if (n == 0)
		{
			while (a1.empty())
			{
				a1.push(0);
			}
		}
		else if (n == 1)
		{
			while (a2.empty())
			{
				a2.push(0);
			}
		}
		else if (n == 2)
		{
			while (a3.empty())
			{
				a3.push(0);
			}
		}
		else if (n == 3)
		{
			while (a4.empty())
			{
				a4.push(0);
			}
		}
		else if (n == 4)
		{
			while (a5.empty())
			{
				a5.push(0);
			}
		}
	} // row A
	//row B
	else if (i == 1)
	{
		if (n == 0)
		{
			while (b1.empty())
			{
				b1.push(0);
			}
		}
		else if (n == 1)
		{
			while (b2.empty())
			{
				b2.push(0);
			}
		}
		else if (n == 2)
		{
			while (b3.empty())
			{
				b3.push(0);
			}
		}
		else if (n == 3)
		{
			while (b4.empty())
			{
				b4.push(0);
			}
		}
		else if (n == 4)
		{
			while (b5.empty())
			{
				b5.push(0);
			}
		}
	}
	//row C
	else if (i == 2)
	{
		if (n == 0)
		{
			while (c1.empty())
			{
				c1.push(0);
			}
		}
		else if (n == 1)
		{
			while (c2.empty())
			{
				c2.push(0);
			}
		}
		else if (n == 2)
		{
			while (c3.empty())
			{
				c3.push(0);
			}
		}
		else if (n == 3)
		{
			while (c4.empty())
			{
				c4.push(0);
			}
		}
		else if (n == 4)
		{
			while (c5.empty())
			{
				c5.push(0);
			}
		}
	}
	//row D
	else if (i == 3)
	{
		if (n == 0)
		{
			while (d1.empty())
			{
				d1.push(0);
			}
		}
		else if (n == 1)
		{
			while (d2.empty())
			{
				d2.push(0);
			}
		}
		else if (n == 2)
		{
			while (d3.empty())
			{
				d3.push(0);
			}
		}
		else if (n == 3)
		{
			while (d4.empty())
			{
				d4.push(0);
			}
		}
		else if (n == 4)
		{
			while (d5.empty())
			{
				d5.push(0);
			}
		}
	}
	//row E
	else if (i == 4)
	{
		if (n == 0)
		{
			while (e1.empty())
			{
				e1.push(0);
			}
		}
		else if (n == 1)
		{
			while (e2.empty())
			{
				e2.push(0);
			}
		}
		else if (n == 2)
		{
			while (e3.empty())
			{
				e3.push(0);
			}
		}
		else if (n == 3)
		{
			while (e4.empty())
			{
				e4.push(0);
			}
		}
		else if (n == 4)
		{
			while (e5.empty())
			{
				e5.push(0);
			}
		}
	}
	//row F
	else if (i == 5)
	{
		if (n == 0)
		{
			while (f1.empty())
			{
				f1.push(0);
			}
		}
		else if (n == 1)
		{
			while (f2.empty())
			{
				f2.push(0);
			}
		}
		else if (n == 2)
		{
			while (f3.empty())
			{
				f3.push(0);
			}
		}
		else if (n == 3)
		{
			while (f4.empty())
			{
				f4.push(0);
			}
		}
		else if (n == 4)
		{
			while (f5.empty())
			{
				f5.push(0);
			}
		}
	}
	//row G
	else if (i == 6)
	{
		if (n == 0)
		{
			while (g1.empty())
			{
				g1.push(0);
			}
		}
		else if (n == 1)
		{
			while (g2.empty())
			{
				g2.push(0);
			}
		}
		else if (n == 2)
		{
			while (g3.empty())
			{
				g3.push(0);
			}
		}
		else if (n == 3)
		{
			while (g4.empty())
			{
				g4.push(0);
			}
		}
		else if (n == 4)
		{
			while (g5.empty())
			{
				g5.push(0);
			}
		}
	}
}*/

void VendingMachine::setPrice()
{
	// loop to randomly assign a price between .25 and $5 to every cell of the price array, prices are random at the start of program
	for (int i = 0; i < R; i++)
	{
		for (int n = 0; n < C; n++)
		{
			price[i][n] = (rand() % 20 + 1) * .25;
		}
	}
}

double VendingMachine::returnPrice(int i, int n)
{
	return price[i][n];
}

// function to be used with display function to show the updated value for any cell at any time
int VendingMachine::update(int i, int n)
{
	// the below will check if any cell/stack is empty and if so will load that cell with the value 0
	{//row A
		if (i == 0)
		{
			if (n == 0)
			{
				while (a1.empty())
				{
					a1.push(0);
				}
			}
			else if (n == 1)
			{
				while (a2.empty())
				{
					a2.push(0);
				}
			}
			else if (n == 2)
			{
				while (a3.empty())
				{
					a3.push(0);
				}
			}
			else if (n == 3)
			{
				while (a4.empty())
				{
					a4.push(0);
				}
			}
			else if (n == 4)
			{
				while (a5.empty())
				{
					a5.push(0);
				}
			}
		} // row A
		//row B
		else if (i == 1)
		{
			if (n == 0)
			{
				while (b1.empty())
				{
					b1.push(0);
				}
			}
			else if (n == 1)
			{
				while (b2.empty())
				{
					b2.push(0);
				}
			}
			else if (n == 2)
			{
				while (b3.empty())
				{
					b3.push(0);
				}
			}
			else if (n == 3)
			{
				while (b4.empty())
				{
					b4.push(0);
				}
			}
			else if (n == 4)
			{
				while (b5.empty())
				{
					b5.push(0);
				}
			}
		}
		//row C
		else if (i == 2)
		{
			if (n == 0)
			{
				while (c1.empty())
				{
					c1.push(0);
				}
			}
			else if (n == 1)
			{
				while (c2.empty())
				{
					c2.push(0);
				}
			}
			else if (n == 2)
			{
				while (c3.empty())
				{
					c3.push(0);
				}
			}
			else if (n == 3)
			{
				while (c4.empty())
				{
					c4.push(0);
				}
			}
			else if (n == 4)
			{
				while (c5.empty())
				{
					c5.push(0);
				}
			}
		}
		//row D
		else if (i == 3)
		{
			if (n == 0)
			{
				while (d1.empty())
				{
					d1.push(0);
				}
			}
			else if (n == 1)
			{
				while (d2.empty())
				{
					d2.push(0);
				}
			}
			else if (n == 2)
			{
				while (d3.empty())
				{
					d3.push(0);
				}
			}
			else if (n == 3)
			{
				while (d4.empty())
				{
					d4.push(0);
				}
			}
			else if (n == 4)
			{
				while (d5.empty())
				{
					d5.push(0);
				}
			}
		}
		//row E
		else if (i == 4)
		{
			if (n == 0)
			{
				while (e1.empty())
				{
					e1.push(0);
				}
			}
			else if (n == 1)
			{
				while (e2.empty())
				{
					e2.push(0);
				}
			}
			else if (n == 2)
			{
				while (e3.empty())
				{
					e3.push(0);
				}
			}
			else if (n == 3)
			{
				while (e4.empty())
				{
					e4.push(0);
				}
			}
			else if (n == 4)
			{
				while (e5.empty())
				{
					e5.push(0);
				}
			}
		}
		//row F
		else if (i == 5)
		{
			if (n == 0)
			{
				while (f1.empty())
				{
					f1.push(0);
				}
			}
			else if (n == 1)
			{
				while (f2.empty())
				{
					f2.push(0);
				}
			}
			else if (n == 2)
			{
				while (f3.empty())
				{
					f3.push(0);
				}
			}
			else if (n == 3)
			{
				while (f4.empty())
				{
					f4.push(0);
				}
			}
			else if (n == 4)
			{
				while (f5.empty())
				{
					f5.push(0);
				}
			}
		}
		//row G
		else if (i == 6)
		{
			if (n == 0)
			{
				while (g1.empty())
				{
					g1.push(0);
				}
			}
			else if (n == 1)
			{
				while (g2.empty())
				{
					g2.push(0);
				}
			}
			else if (n == 2)
			{
				while (g3.empty())
				{
					g3.push(0);
				}
			}
			else if (n == 3)
			{
				while (g4.empty())
				{
					g4.push(0);
				}
			}
			else if (n == 4)
			{
				while (g5.empty())
				{
					g5.push(0);
				}
			}
		}
	}
	// this function will use the global stack variables and return their top values to be displayed in the display function
	//this is done by taking the variables passed in from display (the ith row and the nth column) and using the if/else statments for comparison
	{
	if (i == 0)
	{
		if (n == 0)
			return a1.top();
		else if (n == 1)
			return a2.top();
		else if (n == 2)
			return a3.top();
		else if (n == 3)
			return a4.top();
		else if (n == 4)
			return a5.top();
	}
	else if (i == 1)
	{
		if (n == 0)
			return b1.top();
		else if (n == 1)
			return b2.top();
		else if (n == 2)
			return b3.top();
		else if (n == 3)
			return b4.top();
		else if (n == 4)
			return b5.top();
	}
	else if (i == 2)
	{
		if (n == 0)
			return c1.top();
		else if (n == 1)
			return c2.top();
		else if (n == 2)
			return c3.top();
		else if (n == 3)
			return c4.top();
		else if (n == 4)
			return c5.top();
	}
	else if (i == 3)
	{
		if (n == 0)
			return d1.top();
		else if (n == 1)
			return d2.top();
		else if (n == 2)
			return d3.top();
		else if (n == 3)
			return d4.top();
		else if (n == 4)
			return d5.top();
	}
	else if (i == 4)
	{
		if (n == 0)
			return e1.top();
		else if (n == 1)
			return e2.top();
		else if (n == 2)
			return e3.top();
		else if (n == 3)
			return e4.top();
		else if (n == 4)
			return e5.top();
	}
	else if (i == 5)
	{
		if (n == 0)
			return f1.top();
		else if (n == 1)
			return f2.top();
		else if (n == 2)
			return f3.top();
		else if (n == 3)
			return f4.top();
		else if (n == 4)
			return f5.top();
	}
	else if (i == 6)
	{
		if (n == 0)
			return g1.top();
		else if (n == 1)
			return g2.top();
		else if (n == 2)
			return g3.top();
		else if (n == 3)
			return g4.top();
		else if (n == 4)
			return g5.top();
	}
	}
	return 0;
}

// function will construct the visual of the vending machine
void VendingMachine::display()
{
	cout << "\t----------------------------" << endl;
	cout << "\t| /| 1 | 2 | 3 | 4 | 5 |\\ |" << endl;
	cout << "\t----------------------------" << endl;
	for (int i = 0; i < R; i++)
	{// for loop will construct row by row and below if statement will output designation for each row 
		if (i == 0)
			cout << "\t|A/";
		else if (i == 1)
			cout << "\t|B/";
		else if (i == 2)
			cout << "\t|C/";
		else if (i == 3)
			cout << "\t|D/";
		else if (i == 4)
			cout << "\t|E/";
		else if (i == 5)
			cout << "\t|F/";
		else if (i == 6)
			cout << "\t|G/";

		for (int n = 0; n < C; n++)
		{// for loop for the columns
			content[i][n] = update(i, n);
			cout << "|" << setw(2) << content[i][n] << " ";
		}
		if (i == 0)
			cout << "|\\A|" << endl;
		else if (i == 1)
			cout << "|\\B|" << endl;
		else if (i == 2)
			cout << "|\\C|" << endl;
		else if (i == 3)
			cout << "|\\D|" << endl;
		else if (i == 4)
			cout << "|\\E|" << endl;
		else if (i == 5)
			cout << "|\\F|" << endl;
		else if (i == 6)
			cout << "|\\G|" << endl;
		cout << "\t----------------------------" << endl;
	}
	cout << "\t|        || PUSH ||       |" << endl;
}

// function that works identical to display function, however does not use update or the global stacks, instead uses the pass price array to show prices of each cell
void VendingMachine::showPrice()
{
		cout << "\t------------------------------------------" << endl;
		cout << "\t| /|   1  |   2  |   3  |   4  |   5  |\\ |" << endl;
		cout << "\t------------------------------------------" << endl;
		for (int i = 0; i < R; i++)
		{// for loop will construct row by row and below if statement will output designation for each row 
			if (i == 0)
				cout << "\t|A/";
			else if (i == 1)
				cout << "\t|B/";
			else if (i == 2)
				cout << "\t|C/";
			else if (i == 3)
				cout << "\t|D/";
			else if (i == 4)
				cout << "\t|E/";
			else if (i == 5)
				cout << "\t|F/";
			else if (i == 6)
				cout << "\t|G/";

			for (int n = 0; n < C; n++)
			{// for loop for the columns
				cout << "|" << setw(5) << fixed << setprecision(2) << returnPrice(i, n);
			}
			if (i == 0)
				cout << "|\\A|" << endl;
			else if (i == 1)
				cout << "|\\B|" << endl;
			else if (i == 2)
				cout << "|\\C|" << endl;
			else if (i == 3)
				cout << "|\\D|" << endl;
			else if (i == 4)
				cout << "|\\E|" << endl;
			else if (i == 5)
				cout << "|\\F|" << endl;
			else if (i == 6)
				cout << "|\\G|" << endl;
			cout << "\t------------------------------------------" << endl;
		}
		cout << "\t|                || PUSH ||              |" << endl;
}

/* ErrorStatus VendingMachine
{
	if
}
*/

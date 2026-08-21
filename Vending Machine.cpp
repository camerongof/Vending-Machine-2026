// vending machie coding challenge, this is assuming a 7 x 5 machine
// program should expect money in all denominations, random amount at the start of the program
// every cell should use a stack, random cost?

//*NOTE* loadSpecific and unloadSpecific validate both the row and column before changing a cell *NOTE*

#include <iostream>
#include <iomanip>
#include <stack>
#include <string>
#include <cctype>
#include <ctime>
#include <limits>
#include "machineHeader.h"

const float dollar = 1.0f, quarter = .25f, dime = .1f, nickel = .05f, penny = .01f;// intialization for money worth 
//float remainder = 0.00;

// inventory stacks are declared in the header and defined once here
stack<int> a1, a2, a3, a4, a5, b1, b2, b3, b4, b5, c1, c2, c3, c4, c5;
stack<int> d1, d2, d3, d4, d5, e1, e2, e3, e4, e5, f1, f2, f3, f4, f5, g1, g2, g3, g4, g5;

void display(int content[][C], int rows); // function will construct the visual of the vending machine
int update(int i, int n); // function to be used with display function to show the updated value for any cell at any time
void loadAll(); // function to load every stack until full: 10
void unloadAll(); //function to unload every stack until empty: 0
void loadSpecific(); //function to load a specific cell until full: 10
void unloadSpecific(); //function to unload a specific cell until empty: 0
stack<int>& inventoryAt(int i, int n);
bool buyItem(VendingMachine& machine, float& credit);
//float changeMoney(float credit);

int main()
{
	int choice1, choice2, choice3, choice4, choice5, dol_count, quart_count, dime_count, nick_count, pen_count;
	int dol_take = 0, quart_take = 0, dime_take = 0, nick_take = 0, pen_take = 0;
	int amount = 0;
	float total, credit = 0.00f;
	bool canBuy = false, exit1, exit2, exit3, exit4, exit5;

	srand(static_cast<unsigned int>(time(nullptr)));
	VendingMachine Operation; // new instance of the machine; constructor begins program initialization
	//TODO ErrorStatus Status = ErrorStatus::Invalid_Status; // sets default status

	do {// start of main menu, exit1 and choice1 are used here
		exit1 = false;
		cout << "\t\tVending Machine\n";
		Operation.display();
		cout << "\n\tMain menu:\n\t1. Supplier menu\n\t2. Customer menu\n\t3. Exit program\n\t";
		cin >> choice1;
		while (choice1 < 1 || choice1 > 3)
		{
			cout << "\n\tError: Invalid input\n\t";
			cin >> choice1;
		}

		switch (choice1)
		{//start of submenu 1, exit2 and choice2 are used here
		case 1:
			do {
				exit2 = false;
				system("CLS");// this will clear the screen per loop
				cout << "\t\tVending Machine\n";
				Operation.display();
				cout << "\n\tSupplier menu:\n\t1. Load all\n\t2. Unload all\n\t3. Load specific cell\n\t4. Unload specific cell\n\t5. Exit submenu\n\t";
				cin >> choice2;
				while (choice2 < 1 || choice2 > 5)
				{
					cout << "\n\tError: Invalid input\n\t";
					cin >> choice2;
				}
				switch (choice2)
				{
				case 1:
					loadAll();
					break;
				case 2:
					unloadAll();
					break;
				case 3:
					loadSpecific();
					break;
				case 4:
					unloadSpecific();
					break;
				case 5:
					system("CLS"); // clear screen is used here to clear the supplier menu before going back to main
					exit2 = true; // choosing 5 will set the bool to true, breaking the loop
					break;
				}// end of submenu 1
			} while (exit2 == false);
			break;

		case 2:
			// the below will set the count for each money denomination, for each denomination at most will be 10 and at least 1 each. At most a customer will have 
			// $14.10 and at least $1.41. Customer money amount is random every time customer menu is accessed from main menu
			dol_count = rand() % 10 + 1, quart_count = rand() % 10 + 1, dime_count = rand() % 10 + 1, nick_count = rand() % 10 + 1, pen_count = rand() % 10 + 1;
			dol_take = quart_take = dime_take = nick_take = pen_take = 0;
			credit = 0.00f;
			total = (dol_count * dollar) + (quart_count * quarter) + (dime_count * dime) + (nick_count * nickel) + (pen_count * penny);

			// start of submenu 2, exit3 and choice3 are used here
			do {
				exit3 = false;
				system("CLS");// this will clear the screen per loop
				cout << "\t\tVending Machine\n";
				Operation.display();
				cout << "\n\tYou find some money in your pocket:";
				cout << "\n\tDol: " << dol_count << " Q: " << quart_count << " D: " << dime_count << " N: " << nick_count << " P: " << pen_count << " Total: $" << total << " Credit: $" << credit;
				cout << "\n\tCustomer menu:\n\t1. See Price\n\t2. Enter money\n\t3. Buy item\n\t4. Unload specific cell\n\t5. Exit submenu\n\t";
				cin >> choice3;
				while (choice3 < 1 || choice3 > 5)
				{
					cout << "\n\tError: Invalid input\n\t";
					cin >> choice3;
				}
				switch (choice3)
				{
				case 1:
					// this is purely to show prices throughout the machine, exit4 and choice4 used here. Submenu 2A
					do
					{// submenu A within submenu 2, start
						exit4 = false;
						system("CLS");// this will clear the screen per loop
						cout << "\t\tVending Machine\n";
						Operation.showPrice();
						cout << "\n\tGo back?\n\t1.Yes\n\t2.No\n\t";
						cin >> choice4;

						while (choice4 < 1 || choice4 > 2)
						{
							cout << "\n\tError: Invalid input\n\t";
							cin >> choice4;
						}
						switch (choice4)
						{
						case 1:
							system("CLS");
							exit4 = true;
							break;
						case 2:
							break;
						}
						// submenu A within submenu 3, end
					} while (exit4 == false);
					break;
				case 2:
					// Menu to enter a given amount of a denomination for credit in the machine. Submenu 2B
					do {// submenu B within submenu 2, start
						exit5 = false;
						// below total and credit will be updated after every loop
						total = (dol_count * dollar) + (quart_count * quarter) + (dime_count * dime) + (nick_count * nickel) + (pen_count * penny);
						credit = (dol_take * dollar) + (quart_take * quarter) + (dime_take * dime) + (nick_take * nickel) + (pen_take * penny);
						system("CLS");// this will clear the screen per loop
						cout << "\t\tVending Machine\n";
						Operation.display();
						cout << "\n\tDol: " << dol_count << " Q: " << quart_count << " D: " << dime_count << " N: " << nick_count << " P: " << pen_count << " Total: $" << total << " Credit: $" << credit;
						cout << "\n\tEnter Money:\n\t1. Dollars\n\t2. Quarters\n\t3. Dimes\n\t4. Nickels\n\t5. Pennies\n\t6. Done\n\t";
						cin >> choice5;
						while (choice5 < 1 || choice5 > 6)
						{
							cout << "\n\tError: Invalid input\n\t";
							cin >> choice5;
						}
						switch (choice5)
						{
						case 1:// dollars
							cout << "\n\tHow many?\n\t";
							cin >> amount;
							while (amount < 0 || amount > dol_count)
							{
								cout << "\n\tError: You don't have this amount\n\tHow many?\n\t";
								cin >> amount;
							}
							dol_count = dol_count - amount;
							dol_take = dol_take + amount;
							break;
						case 2:// quarters
							cout << "\n\tHow many?\n\t";
							cin >> amount;
							while (amount < 0 || amount > quart_count)
							{
								cout << "\n\tError: You don't have this amount\n\tHow many?\n\t";
								cin >> amount;
							}
							quart_count = quart_count - amount;
							quart_take = quart_take + amount;
							break;
						case 3:// dimes
							cout << "\n\tHow many?\n\t";
							cin >> amount;
							while (amount < 0 || amount > dime_count)
							{
								cout << "\n\tError: You don't have this amount\n\tHow many?\n\t";
								cin >> amount;
							}
							dime_count = dime_count - amount;
							dime_take = dime_take + amount;
							break;
						case 4: //nickels
							cout << "\n\tHow many?\n\t";
							cin >> amount;
							while (amount < 0 || amount > nick_count)
							{
								cout << "\n\tError: You don't have this amount\n\tHow many?\n\t";
								cin >> amount;
							}
							nick_count = nick_count - amount;
							nick_take = nick_take + amount;
							break;
						case 5: //pennies
							cout << "\n\tHow many?\n\t";
							cin >> amount;
							while (amount < 0 || amount > pen_count)
							{
								cout << "\n\tError: You don't have this amount\n\tHow many?\n\t";
								cin >> amount;
							}
							pen_count = pen_count - amount;
							pen_take = pen_take + amount;
							break;
						case 6:
							system("CLS");
							exit5 = true;
							break;
						}// submenu B within submenu 2, end
					} while (exit5 == false);
					break;
				case 3:
					canBuy = buyItem(Operation, credit);
					if (canBuy == true)
						cout << "\n\tPurchase complete. Remaining credit: $" << fixed << setprecision(2) << credit << "\n";
					else
						cout << "\n\tPurchase could not be completed.\n";
					system("pause");
					break;
				case 4:
					unloadSpecific();
					break;
				case 5:
					system("CLS"); // clear screen is used here to clear the supplier menu before going back to main
					exit3 = true; // choosing 5 will set the bool to true, breaking the loop
					break;
				}// end of submenu 2
			} while (exit3 == false);

			break;

		case 3:
			exit1 = true; // choosing 3 will set bool to true, which will break the loop
			break;
		}
		//end of main menu
	} while (exit1 == false);

	system("pause");
	return 0;
}

// returns the stack for a cell after the row and column have been validated
stack<int>& inventoryAt(int i, int n)
{
	static stack<int>* inventory[R][C] =
	{
		{ &a1, &a2, &a3, &a4, &a5 },
		{ &b1, &b2, &b3, &b4, &b5 },
		{ &c1, &c2, &c3, &c4, &c5 },
		{ &d1, &d2, &d3, &d4, &d5 },
		{ &e1, &e2, &e3, &e4, &e5 },
		{ &f1, &f2, &f3, &f4, &f5 },
		{ &g1, &g2, &g3, &g4, &g5 }
	};

	return *inventory[i][n];
}

// checks the selected cell, verifies credit, and removes one item from its stack
bool buyItem(VendingMachine& machine, float& credit)
{
	char input;
	int inputN;

	cout << "\n\tInput cell row (ex:a): ";
	cin >> input;
	input = static_cast<char>(toupper(static_cast<unsigned char>(input)));
	while (input < 'A' || input > 'G')
	{
		cout << "\n\tError: invalid input\n\tInput cell row (ex:a): ";
		cin >> input;
		input = static_cast<char>(toupper(static_cast<unsigned char>(input)));
	}

	cout << "\n\tInput cell column (ex:1): ";
	while (!(cin >> inputN) || inputN < 1 || inputN > C)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\n\tError: invalid input\n\tInput cell column (ex:1): ";
	}

	const int i = input - 'A';
	const int n = inputN - 1;
	stack<int>& selectedCell = inventoryAt(i, n);
	const double selectedPrice = machine.returnPrice(i, n);

	if (selectedCell.empty() || selectedCell.top() == 0)
	{
		cout << "\n\tError: this cell is empty.\n";
		return false;
	}

	if (credit + 0.001f < selectedPrice)
	{
		cout << "\n\tError: item costs $" << fixed << setprecision(2) << selectedPrice
			<< " but current credit is $" << credit << ".\n";
		return false;
	}

	selectedCell.pop();
	credit -= static_cast<float>(selectedPrice);
	if (credit < 0.001f)
		credit = 0.00f;

	return true;
}

/* TODO bool buyItem(float price[][C], int rows, float credit)
{
	int i, n;
	char input;
	int inputN;
	cout << "\n\tInput cell row (ex:a): ";
	cin >> input;

	//the below is input validation
	if (input != 'a' && input != 'A' && input != 'b' && input != 'B' && input != 'c' && input != 'C' && input != 'd' && input != 'D' && input != 'e' && input != 'E' && input != 'f' && input != 'F' && input != 'g' && input != 'G')
	{
		do
		{
			cout << "\n\tError: invalid input\n\t\n\tInput cell row (ex:a): ";
			cin >> input;
		} while (input != 'a' && input != 'A' && input != 'b' && input != 'B' && input != 'c' && input != 'C' && input != 'd' && input != 'D' && input != 'e' && input != 'E' && input != 'f' && input != 'F' && input != 'g' && input != 'G');
	}

	cout << "\n\tInput cell column (ex:1): ";
	cin >> inputN;

	//if (inputN <= 0 || inputN >= 6);
	//{
	do
	{
		cout << "\n\tError: invalid input\n\t\n\tInput cell column (ex:1): ";
		cin >> inputN;
	} while (inputN <= 0 || inputN >= 6);
	//}//*NOTE* bug validation works, however correct input need to be entered twice to break out of loop, otherwise loop correctly works
	// row A
	if (input == 'a' || input == 'A') // this will look for the character of the input string and match to the row designation
	{
		i = 0; // row
		n = inputN; // column
		// The below will check if credit is adequate for purchase, if condition is met the true will be returned, else false
		if (credit >= price[i][n])
			return true;
		else
			return false;
	}
	//row B
	else if (input == 'b' || input == 'B') // this will look for the character of the input string and match to the row designation
	{
		i = 1; // row
		n = inputN; // column
					// The below will check if credit is adequate for purchase, if condition is met the true will be returned, else false
		if (credit >= price[i][n])
			return true;
		else
			return false;
	}
	//row C
	else if (input == 'c' || input == 'C') // this will look for the character of the input string and match to the row designation
	{
		i = 2; // row
		n = inputN; // column
					// The below will check if credit is adequate for purchase, if condition is met the true will be returned, else false
		if (credit >= price[i][n])
			return true;
		else
			return false;
	}
	//row D
	else if (input == 'd' || input == 'D') // this will look for the character of the input string and match to the row designation
	{
		i = 3; // row
		n = inputN; // column
					// The below will check if credit is adequate for purchase, if condition is met the true will be returned, else false
		if (credit >= price[i][n])
			return true;
		else
			return false;
	}
	//row E
	else if (input == 'e' || input == 'E') // this will look for the character of the input string and match to the row designation
	{
		i = 4; // row
		n = inputN; // column
					// The below will check if credit is adequate for purchase, if condition is met the true will be returned, else false
		if (credit >= price[i][n])
			return true;
		else
			return false;
	}
	//row F
	else if (input == 'f' || input == 'F') // this will look for the character of the input string and match to the row designation
	{
		i = 5; // row
		n = inputN; // column
					// The below will check if credit is adequate for purchase, if condition is met the true will be returned, else false
		if (credit >= price[i][n])
			return true;
		else
			return false;
	}
	//row G
	else if (input == 'g' || input == 'G') // this will look for the character of the input string and match to the row designation
	{
		i = 6; // row
		n = inputN; // column
					// The below will check if credit is adequate for purchase, if condition is met the true will be returned, else false
		if (credit >= price[i][n])
			return true;
		else
			return false;
	}
}*/

//float changeMoney(float credit)
//{
	//if (credit >= dollar)
	//{
		//float remainder = credit % dollar;
	//}
//}


//function to unload a specific cell until empty: 0
void unloadSpecific()
{
	char input;
	int inputN;
	cout << "\n\tInput cell row (ex:a): ";
	cin >> input;

	//the below is input validation
	if (input != 'a' && input != 'A' && input != 'b' && input != 'B' && input != 'c' && input != 'C' && input != 'd' && input != 'D' && input != 'e' && input != 'E' && input != 'f' && input != 'F' && input != 'g' && input != 'G')
	{
		do
		{
			cout << "\n\tError: invalid input\n\t\n\tInput cell row (ex:a): ";
			cin >> input;
		} while (input != 'a' && input != 'A' && input != 'b' && input != 'B' && input != 'c' && input != 'C' && input != 'd' && input != 'D' && input != 'e' && input != 'E' && input != 'f' && input != 'F' && input != 'g' && input != 'G');
	}

	cout << "\n\tInput cell column (ex:1): ";
	cin >> inputN;

	if (inputN <= 0 || inputN >= 6)
	{
		do
		{
			cout << "\n\tError: invalid input\n\t\n\tInput cell column (ex:1): ";
			cin >> inputN;
		} while (inputN <= 0 || inputN >= 6);
	}//*NOTE* bug validation works, however correct input need to be entered twice to break out of loop, otherwise loop correctly works
	//row A
	if (input == 'a' || input == 'A') // this will look for the character of the input string and match to the row designation
	{
		if (inputN == 1)// nested if will look for the column number
		{
			while (a1.top() != 0)// this will look at the top of the stack, which should be the number 0 if nothing else, if the top of the stack is greater than 0, the number will be decemented via popping
			{// making it the new top. will continue until condition is satisfied
				a1.pop();
			};
			while (a1.empty())// this while loop acts as a second check, if the stack is ever empty, the stack will push until its not
			{
				a1.push(0);
			}
		}
		else if (inputN == 2)
		{
			while (a2.top() != 0)
			{
				a2.pop();
			}
			while (a2.empty())
			{
				a2.push(0);
			}
		}
		else if (inputN == 3)
		{
			while (a3.top() != 0)
			{
				a3.pop();
			}
			while (a3.empty())
			{
				a3.push(0);
			}
		}
		else if (inputN == 4)
		{
			while (a4.top() != 0)
			{
				a4.pop();
			}
			while (a4.empty())
			{
				a4.push(0);
			}
		}
		else if (inputN == 5)
		{
			while (a5.top() != 0)
			{
				a5.pop();
			}
			while (a5.empty())
			{
				a5.push(0);
			}
		}
	} // row A
	  //row B
	else if (input == 'b' || input == 'B') // this will look for the character of the input string and match to the row designation
	{
		if (inputN == 1)// nested if will look for the column number
		{
			while (b1.top() != 0)// this will look at the top of the stack, which should be the number 0 if nothing else, if the top of the stack is greater than 0, the number will be decemented via popping
			{// making it the new top. will continue until condition is satisfied
				b1.pop();
			};
			while (b1.empty())// this while loop acts as a second check, if the stack is ever empty, the stack will push until its not
			{
				b1.push(0);
			}
		}
		else if (inputN == 2)
		{
			while (b2.top() != 0)
			{
				b2.pop();
			}
			while (b2.empty())
			{
				b2.push(0);
			}
		}
		else if (inputN == 3)
		{
			while (b3.top() != 0)
			{
				b3.pop();
			}
			while (b3.empty())
			{
				b3.push(0);
			}
		}
		else if (inputN == 4)
		{
			while (b4.top() != 0)
			{
				b4.pop();
			}
			while (b4.empty())
			{
				b4.push(0);
			}
		}
		else if (inputN == 5)
		{
			while (b5.top() != 0)
			{
				b5.pop();
			}
			while (b5.empty())
			{
				b5.push(0);
			}
		}
	}
	//row C
	else if (input == 'c' || input == 'C') // this will look for the character of the input string and match to the row designation
	{
		if (inputN == 1)// nested if will look for the column number
		{
			while (c1.top() != 0)// this will look at the top of the stack, which should be the number 0 if nothing else, if the top of the stack is greater than 0, the number will be decemented via popping
			{// making it the new top. will continue until condition is satisfied
				c1.pop();
			};
			while (c1.empty())// this while loop acts as a second check, if the stack is ever empty, the stack will push until its not
			{
				c1.push(0);
			}
		}
		else if (inputN == 2)
		{
			while (c2.top() != 0)
			{
				c2.pop();
			}
			while (c2.empty())
			{
				c2.push(0);
			}
		}
		else if (inputN == 3)
		{
			while (c3.top() != 0)
			{
				c3.pop();
			}
			while (c3.empty())
			{
				c3.push(0);
			}
		}
		else if (inputN == 4)
		{
			while (c4.top() != 0)
			{
				c4.pop();
			}
			while (c4.empty())
			{
				c4.push(0);
			}
		}
		else if (inputN == 5)
		{
			while (c5.top() != 0)
			{
				c5.pop();
			}
			while (c5.empty())
			{
				c5.push(0);
			}
		}
	}
	//row D
	else if (input == 'd' || input == 'D') // this will look for the character of the input string and match to the row designation
	{
		if (inputN == 1)// nested if will look for the column number
		{
			while (d1.top() != 0)// this will look at the top of the stack, which should be the number 0 if nothing else, if the top of the stack is greater than 0, the number will be decemented via popping
			{// making it the new top. will continue until condition is satisfied
				d1.pop();
			};
			while (d1.empty())// this while loop acts as a second check, if the stack is ever empty, the stack will push until its not
			{
				d1.push(0);
			}
		}
		else if (inputN == 2)
		{
			while (d2.top() != 0)
			{
				d2.pop();
			}
			while (d2.empty())
			{
				d2.push(0);
			}
		}
		else if (inputN == 3)
		{
			while (d3.top() != 0)
			{
				d3.pop();
			}
			while (d3.empty())
			{
				d3.push(0);
			}
		}
		else if (inputN == 4)
		{
			while (d4.top() != 0)
			{
				d4.pop();
			}
			while (d4.empty())
			{
				d4.push(0);
			}
		}
		else if (inputN == 5)
		{
			while (d5.top() != 0)
			{
				d5.pop();
			}
			while (d5.empty())
			{
				d5.push(0);
			}
		}
	}
	//row E
	else if (input == 'e' || input == 'E') // this will look for the character of the input string and match to the row designation
	{
		if (inputN == 1)// nested if will look for the column number
		{
			while (e1.top() != 0)// this will look at the top of the stack, which should be the number 0 if nothing else, if the top of the stack is greater than 0, the number will be decemented via popping
			{// making it the new top. will continue until condition is satisfied
				e1.pop();
			};
			while (e1.empty())// this while loop acts as a second check, if the stack is ever empty, the stack will push until its not
			{
				e1.push(0);
			}
		}
		else if (inputN == 2)
		{
			while (e2.top() != 0)
			{
				e2.pop();
			}
			while (e2.empty())
			{
				e2.push(0);
			}
		}
		else if (inputN == 3)
		{
			while (e3.top() != 0)
			{
				e3.pop();
			}
			while (e3.empty())
			{
				e3.push(0);
			}
		}
		else if (inputN == 4)
		{
			while (e4.top() != 0)
			{
				e4.pop();
			}
			while (e4.empty())
			{
				e4.push(0);
			}
		}
		else if (inputN == 5)
		{
			while (e5.top() != 0)
			{
				e5.pop();
			}
			while (e5.empty())
			{
				e5.push(0);
			}
		}
	}
	//row F
	else if (input == 'f' || input == 'F') // this will look for the character of the input string and match to the row designation
	{
		if (inputN == 1)// nested if will look for the column number
		{
			while (f1.top() != 0)// this will look at the top of the stack, which should be the number 0 if nothing else, if the top of the stack is greater than 0, the number will be decemented via popping
			{// making it the new top. will continue until condition is satisfied
				f1.pop();
			};
			while (f1.empty())// this while loop acts as a second check, if the stack is ever empty, the stack will push until its not
			{
				f1.push(0);
			}
		}
		else if (inputN == 2)
		{
			while (f2.top() != 0)
			{
				f2.pop();
			}
			while (f2.empty())
			{
				f2.push(0);
			}
		}
		else if (inputN == 3)
		{
			while (f3.top() != 0)
			{
				f3.pop();
			}
			while (f3.empty())
			{
				f3.push(0);
			}
		}
		else if (inputN == 4)
		{
			while (f4.top() != 0)
			{
				f4.pop();
			}
			while (f4.empty())
			{
				f4.push(0);
			}
		}
		else if (inputN == 5)
		{
			while (f5.top() != 0)
			{
				f5.pop();
			}
			while (f5.empty())
			{
				f5.push(0);
			}
		}
	}
	//row G
	else if (input == 'g' || input == 'G') // this will look for the character of the input string and match to the row designation
	{
		if (inputN == 1)// nested if will look for the column number
		{
			while (g1.top() != 0)// this will look at the top of the stack, which should be the number 0 if nothing else, if the top of the stack is greater than 0, the number will be decemented via popping
			{// making it the new top. will continue until condition is satisfied
				g1.pop();
			};
			while (g1.empty())// this while loop acts as a second check, if the stack is ever empty, the stack will push until its not
			{
				g1.push(0);
			}
		}
		else if (inputN == 2)
		{
			while (g2.top() != 0)
			{
				g2.pop();
			}
			while (g2.empty())
			{
				g2.push(0);
			}
		}
		else if (inputN == 3)
		{
			while (g3.top() != 0)
			{
				g3.pop();
			}
			while (g3.empty())
			{
				g3.push(0);
			}
		}
		else if (inputN == 4)
		{
			while (g4.top() != 0)
			{
				g4.pop();
			}
			while (g4.empty())
			{
				g4.push(0);
			}
		}
		else if (inputN == 5)
		{
			while (g5.top() != 0)
			{
				g5.pop();
			}
			while (g5.empty())
			{
				g5.push(0);
			}
		}
	}
}

//function to load a specific cell until full: 10
void loadSpecific()
{
	int num;
	char input;
	int inputN;
	cout << "\n\tInput cell row (ex:a): ";
	cin >> input;

	//the below is input validation
	if (input != 'a' && input != 'A' && input != 'b' && input != 'B' && input != 'c' && input != 'C' && input != 'd' && input != 'D' && input != 'e' && input != 'E' && input != 'f' && input != 'F' && input != 'g' && input != 'G')
	{
		do
		{
			cout << "\n\tError: invalid input\n\t\n\tInput cell row (ex:a): ";
			cin >> input;
		} while (input != 'a' && input != 'A' && input != 'b' && input != 'B' && input != 'c' && input != 'C' && input != 'd' && input != 'D' && input != 'e' && input != 'E' && input != 'f' && input != 'F' && input != 'g' && input != 'G');
	}

	cout << "\n\tInput cell column (ex:1): ";
	cin >> inputN;

	if (inputN <= 0 || inputN >= 6)
	{
		do
		{
			cout << "\n\tError: invalid input\n\t\n\tInput cell column (ex:1): ";
			cin >> inputN;
		} while (inputN <= 0 || inputN >= 6);
	}//*NOTE* bug validation works, however correct input need to be entered twice to break out of loop, otherwise loop correctly works

	//row A
	if (input == 'a' || input == 'A') // this will look for the character of the input string and match to the row designation
	{
		if (inputN == 1)// nested if will look for the column number
		{
			while (a1.top() <= MAX_INVENTORY)// this will look at the top of the stack, which should be the number 0 if nothing else, if the top of the stack is less than MAX_INVENTORY, the number will be incemented and saved
			{// seperately and pushed into the stack making it the new top. will continue until condition is satisfied
				num = a1.top() + 1;
				a1.push(num);
			};
			while (a1.top() > MAX_INVENTORY)// this while loop acts as a second check, if the stack top is ever greater than MAX_INVENTORY, the stack will pop until its not
			{
				a1.pop();
			}
		}
		else if (inputN == 2)
		{
			while (a2.top() <= MAX_INVENTORY)
			{
				num = a2.top() + 1;
				a2.push(num);
			}
			while (a2.top() > MAX_INVENTORY)
			{
				a2.pop();
			}
		}
		else if (inputN == 3)
		{
			while (a3.top() <= MAX_INVENTORY)
			{
				num = a3.top() + 1;
				a3.push(num);
			}
			while (a3.top() > MAX_INVENTORY)
			{
				a3.pop();
			}
		}
		else if (inputN == 4)
		{
			while (a4.top() <= MAX_INVENTORY)
			{
				num = a4.top() + 1;
				a4.push(num);
			}
			while (a4.top() > MAX_INVENTORY)
			{
				a4.pop();
			}
		}
		else if (inputN == 5)
		{
			while (a5.top() <= MAX_INVENTORY)
			{
				num = a5.top() + 1;
				a5.push(num);
			}
			while (a5.top() > MAX_INVENTORY)
			{
				a5.pop();
			}
		}
	} // row A
	  //row B
	else if (input == 'b' || input == 'B') // this will look for the character of the input string and match to the row designation
	{
		if (inputN == 1)// nested if will look for the column number
		{
			while (b1.top() <= MAX_INVENTORY)// this will look at the top of the stack, which should be the number 0 if nothing else, if the top of the stack is less than MAX_INVENTORY, the number will be incemented and saved
			{// seperately and pushed into the stack making it the new top. will continue until condition is satisfied
				num = b1.top() + 1;
				b1.push(num);
			};
			while (b1.top() > MAX_INVENTORY)// this while loop acts as a second check, if the stack top is ever greater than MAX_INVENTORY, the stack will pop until its not
			{
				b1.pop();
			}
		}
		else if (inputN == 2)
		{
			while (b2.top() <= MAX_INVENTORY)
			{
				num = b2.top() + 1;
				b2.push(num);
			}
			while (b2.top() > MAX_INVENTORY)
			{
				b2.pop();
			}
		}
		else if (inputN == 3)
		{
			while (b3.top() <= MAX_INVENTORY)
			{
				num = b3.top() + 1;
				b3.push(num);
			}
			while (b3.top() > MAX_INVENTORY)
			{
				b3.pop();
			}
		}
		else if (inputN == 4)
		{
			while (b4.top() <= MAX_INVENTORY)
			{
				num = b4.top() + 1;
				b4.push(num);
			}
			while (b4.top() > MAX_INVENTORY)
			{
				b4.pop();
			}
		}
		else if (inputN == 5)
		{
			while (b5.top() <= MAX_INVENTORY)
			{
				num = b5.top() + 1;
				b5.push(num);
			}
			while (b5.top() > MAX_INVENTORY)
			{
				b5.pop();
			}
		}
	}
	//row C
	else if (input == 'c' || input == 'C') // this will look for the character of the input string and match to the row designation
	{
		if (inputN == 1)// nested if will look for the column number
		{
			while (c1.top() <= MAX_INVENTORY)// this will look at the top of the stack, which should be the number 0 if nothing else, if the top of the stack is less than MAX_INVENTORY, the number will be incemented and saved
			{// seperately and pushed into the stack making it the new top. will continue until condition is satisfied
				num = c1.top() + 1;
				c1.push(num);
			};
			while (c1.top() > MAX_INVENTORY)// this while loop acts as a second check, if the stack top is ever greater than MAX_INVENTORY, the stack will pop until its not
			{
				c1.pop();
			}
		}
		else if (inputN == 2)
		{
			while (c2.top() <= MAX_INVENTORY)
			{
				num = c2.top() + 1;
				c2.push(num);
			}
			while (c2.top() > MAX_INVENTORY)
			{
				c2.pop();
			}
		}
		else if (inputN == 3)
		{
			while (c3.top() <= MAX_INVENTORY)
			{
				num = c3.top() + 1;
				c3.push(num);
			}
			while (c3.top() > MAX_INVENTORY)
			{
				c3.pop();
			}
		}
		else if (inputN == 4)
		{
			while (c4.top() <= MAX_INVENTORY)
			{
				num = c4.top() + 1;
				c4.push(num);
			}
			while (c4.top() > MAX_INVENTORY)
			{
				c4.pop();
			}
		}
		else if (inputN == 5)
		{
			while (c5.top() <= MAX_INVENTORY)
			{
				num = c5.top() + 1;
				c5.push(num);
			}
			while (c5.top() > MAX_INVENTORY)
			{
				c5.pop();
			}
		}
	}
	//row D
	else if (input == 'd' || input == 'D') // this will look for the character of the input string and match to the row designation
	{
		if (inputN == 1)// nested if will look for the column number
		{
			while (d1.top() <= MAX_INVENTORY)// this will look at the top of the stack, which should be the number 0 if nothing else, if the top of the stack is less than MAX_INVENTORY, the number will be incemented and saved
			{// seperately and pushed into the stack making it the new top. will continue until condition is satisfied
				num = d1.top() + 1;
				d1.push(num);
			};
			while (d1.top() > MAX_INVENTORY)// this while loop acts as a second check, if the stack top is ever greater than MAX_INVENTORY, the stack will pop until its not
			{
				d1.pop();
			}
		}
		else if (inputN == 2)
		{
			while (d2.top() <= MAX_INVENTORY)
			{
				num = d2.top() + 1;
				d2.push(num);
			}
			while (d2.top() > MAX_INVENTORY)
			{
				d2.pop();
			}
		}
		else if (inputN == 3)
		{
			while (d3.top() <= MAX_INVENTORY)
			{
				num = d3.top() + 1;
				d3.push(num);
			}
			while (d3.top() > MAX_INVENTORY)
			{
				d3.pop();
			}
		}
		else if (inputN == 4)
		{
			while (d4.top() <= MAX_INVENTORY)
			{
				num = d4.top() + 1;
				d4.push(num);
			}
			while (d4.top() > MAX_INVENTORY)
			{
				d4.pop();
			}
		}
		else if (inputN == 5)
		{
			while (d5.top() <= MAX_INVENTORY)
			{
				num = d5.top() + 1;
				d5.push(num);
			}
			while (d5.top() > MAX_INVENTORY)
			{
				d5.pop();
			}
		}
	}
	//row E
	else if (input == 'e' || input == 'E') // this will look for the character of the input string and match to the row designation
	{
		if (inputN == 1)// nested if will look for the column number
		{
			while (e1.top() <= MAX_INVENTORY)// this will look at the top of the stack, which should be the number 0 if nothing else, if the top of the stack is less than MAX_INVENTORY, the number will be incemented and saved
			{// seperately and pushed into the stack making it the new top. will continue until condition is satisfied
				num = e1.top() + 1;
				e1.push(num);
			};
			while (e1.top() > MAX_INVENTORY)// this while loop acts as a second check, if the stack top is ever greater than MAX_INVENTORY, the stack will pop until its not
			{
				e1.pop();
			}
		}
		else if (inputN == 2)
		{
			while (e2.top() <= MAX_INVENTORY)
			{
				num = e2.top() + 1;
				e2.push(num);
			}
			while (e2.top() > MAX_INVENTORY)
			{
				e2.pop();
			}
		}
		else if (inputN == 3)
		{
			while (e3.top() <= MAX_INVENTORY)
			{
				num = e3.top() + 1;
				e3.push(num);
			}
			while (e3.top() > MAX_INVENTORY)
			{
				e3.pop();
			}
		}
		else if (inputN == 4)
		{
			while (e4.top() <= MAX_INVENTORY)
			{
				num = e4.top() + 1;
				e4.push(num);
			}
			while (e4.top() > MAX_INVENTORY)
			{
				e4.pop();
			}
		}
		else if (inputN == 5)
		{
			while (e5.top() <= MAX_INVENTORY)
			{
				num = e5.top() + 1;
				e5.push(num);
			}
			while (e5.top() > MAX_INVENTORY)
			{
				e5.pop();
			}
		}
	}
	//row F
	else if (input == 'f' || input == 'F') // this will look for the character of the input string and match to the row designation
	{
		if (inputN == 1)// nested if will look for the column number
		{
			while (f1.top() <= MAX_INVENTORY)// this will look at the top of the stack, which should be the number 0 if nothing else, if the top of the stack is less than MAX_INVENTORY, the number will be incemented and saved
			{// seperately and pushed into the stack making it the new top. will continue until condition is satisfied
				num = f1.top() + 1;
				f1.push(num);
			};
			while (f1.top() > MAX_INVENTORY)// this while loop acts as a second check, if the stack top is ever greater than MAX_INVENTORY, the stack will pop until its not
			{
				f1.pop();
			}
		}
		else if (inputN == 2)
		{
			while (f2.top() <= MAX_INVENTORY)
			{
				num = f2.top() + 1;
				f2.push(num);
			}
			while (f2.top() > MAX_INVENTORY)
			{
				f2.pop();
			}
		}
		else if (inputN == 3)
		{
			while (f3.top() <= MAX_INVENTORY)
			{
				num = f3.top() + 1;
				f3.push(num);
			}
			while (f3.top() > MAX_INVENTORY)
			{
				f3.pop();
			}
		}
		else if (inputN == 4)
		{
			while (f4.top() <= MAX_INVENTORY)
			{
				num = f4.top() + 1;
				f4.push(num);
			}
			while (f4.top() > MAX_INVENTORY)
			{
				f4.pop();
			}
		}
		else if (inputN == 5)
		{
			while (f5.top() <= MAX_INVENTORY)
			{
				num = f5.top() + 1;
				f5.push(num);
			}
			while (f5.top() > MAX_INVENTORY)
			{
				f5.pop();
			}
		}
	}
	//row G
	else if (input == 'g' || input == 'G') // this will look for the character of the input string and match to the row designation
	{
		if (inputN == 1)// nested if will look for the column number
		{
			while (g1.top() <= MAX_INVENTORY)// this will look at the top of the stack, which should be the number 0 if nothing else, if the top of the stack is less than MAX_INVENTORY, the number will be incemented and saved
			{// seperately and pushed into the stack making it the new top. will continue until condition is satisfied
				num = g1.top() + 1;
				g1.push(num);
			};
			while (g1.top() > MAX_INVENTORY)// this while loop acts as a second check, if the stack top is ever greater than MAX_INVENTORY, the stack will pop until its not
			{
				g1.pop();
			}
		}
		else if (inputN == 2)
		{
			while (g2.top() <= MAX_INVENTORY)
			{
				num = g2.top() + 1;
				g2.push(num);
			}
			while (g2.top() > MAX_INVENTORY)
			{
				g2.pop();
			}
		}
		else if (inputN == 3)
		{
			while (g3.top() <= MAX_INVENTORY)
			{
				num = g3.top() + 1;
				g3.push(num);
			}
			while (g3.top() > MAX_INVENTORY)
			{
				g3.pop();
			}
		}
		else if (inputN == 4)
		{
			while (g4.top() <= MAX_INVENTORY)
			{
				num = g4.top() + 1;
				g4.push(num);
			}
			while (g4.top() > MAX_INVENTORY)
			{
				g4.pop();
			}
		}
		else if (inputN == 5)
		{
			while (g5.top() <= MAX_INVENTORY)
			{
				num = g5.top() + 1;
				g5.push(num);
			}
			while (g5.top() > MAX_INVENTORY)
			{
				g5.pop();
			}
		}
	}
}

//function to unload every stack until empty: 0
void unloadAll()
{// the below will check each stack to see if it is not empty and if so will delete the entire stack
 //row A
	{
		while (!a1.empty())
		{
			a1.pop();
		}

		while (!a2.empty())
		{
			a2.pop();
		}

		while (!a3.empty())
		{
			a3.pop();
		}

		while (!a4.empty())
		{
			a4.pop();
		}

		while (!a5.empty())
		{
			a5.pop();
		}
	}
	//row B
	{
		while (!b1.empty())
		{
			b1.pop();
		}

		while (!b2.empty())
		{
			b2.pop();
		}

		while (!b3.empty())
		{
			b3.pop();
		}

		while (!b4.empty())
		{
			b4.pop();
		}

		while (!b5.empty())
		{
			b5.pop();
		}
	}
	//row C
	{
		while (!c1.empty())
		{
			c1.pop();
		}

		while (!c2.empty())
		{
			c2.pop();
		}

		while (!c3.empty())
		{
			c3.pop();
		}

		while (!c4.empty())
		{
			c4.pop();
		}

		while (!c5.empty())
		{
			c5.pop();
		}
	}
	//row D
	{
		while (!d1.empty())
		{
			d1.pop();
		}

		while (!d2.empty())
		{
			d2.pop();
		}

		while (!d3.empty())
		{
			d3.pop();
		}

		while (!d4.empty())
		{
			d4.pop();
		}

		while (!d5.empty())
		{
			d5.pop();
		}
	}
	//row E
	{
		while (!e1.empty())
		{
			e1.pop();
		}

		while (!e2.empty())
		{
			e2.pop();
		}

		while (!e3.empty())
		{
			e3.pop();
		}

		while (!e4.empty())
		{
			e4.pop();
		}

		while (!e5.empty())
		{
			e5.pop();
		}
	}
	//row F
	{
		while (!f1.empty())
		{
			f1.pop();
		}

		while (!f2.empty())
		{
			f2.pop();
		}

		while (!f3.empty())
		{
			f3.pop();
		}

		while (!f4.empty())
		{
			f4.pop();
		}

		while (!f5.empty())
		{
			f5.pop();
		}
	}
	//row G
	{
		while (!g1.empty())
		{
			g1.pop();
		}

		while (!g2.empty())
		{
			g2.pop();
		}

		while (!g3.empty())
		{
			g3.pop();
		}

		while (!g4.empty())
		{
			g4.pop();
		}

		while (!g5.empty())
		{
			g5.pop();
		}
	}

	//the below will load all cell stacks with value 0
	int i = 0;
	//row A
	{
		a1.push(i); // this will load the value 0 into the stack

		a2.push(i);

		a3.push(i);

		a4.push(i);

		a5.push(i);
	}
	//row B
	{
		b1.push(i); // this will load the value 0 into the stack

		b2.push(i);

		b3.push(i);

		b4.push(i);

		b5.push(i);
	}
	//row C
	{
		c1.push(i); // this will load the value 0 into the stack

		c2.push(i);

		c3.push(i);

		c4.push(i);

		c5.push(i);
	}
	//row D
	{
		d1.push(i); // this will load the value 0 into the stack

		d2.push(i);

		d3.push(i);

		d4.push(i);

		d5.push(i);
	}
	//row E
	{
		e1.push(i); // this will load the value 0 into the stack

		e2.push(i);

		e3.push(i);

		e4.push(i);

		e5.push(i);
	}
	//row F
	{
		f1.push(i); // this will load the value 0 into the stack

		f2.push(i);

		f3.push(i);

		f4.push(i);

		f5.push(i);
	}
	//row G
	{
		g1.push(i); // this will load the value 0 into the stack

		g2.push(i);

		g3.push(i);

		g4.push(i);

		g5.push(i);
	}
}

// function to load every stack until full: 10
void loadAll()
{// the below will check each stack to see if it is not empty and will proceed to delete the entire stack
	//row A
	{
		while (!a1.empty())
		{
			a1.pop();
		}

		while (!a2.empty())
		{
			a2.pop();
		}

		while (!a3.empty())
		{
			a3.pop();
		}

		while (!a4.empty())
		{
			a4.pop();
		}

		while (!a5.empty())
		{
			a5.pop();
		}
	}
	//row B
	{
		while (!b1.empty())
		{
			b1.pop();
		}

		while (!b2.empty())
		{
			b2.pop();
		}

		while (!b3.empty())
		{
			b3.pop();
		}

		while (!b4.empty())
		{
			b4.pop();
		}

		while (!b5.empty())
		{
			b5.pop();
		}
	}
	//row C
	{
		while (!c1.empty())
		{
			c1.pop();
		}

		while (!c2.empty())
		{
			c2.pop();
		}

		while (!c3.empty())
		{
			c3.pop();
		}

		while (!c4.empty())
		{
			c4.pop();
		}

		while (!c5.empty())
		{
			c5.pop();
		}
	}
	//row D
	{
		while (!d1.empty())
		{
			d1.pop();
		}

		while (!d2.empty())
		{
			d2.pop();
		}

		while (!d3.empty())
		{
			d3.pop();
		}

		while (!d4.empty())
		{
			d4.pop();
		}

		while (!d5.empty())
		{
			d5.pop();
		}
	}
	//row E
	{
		while (!e1.empty())
		{
			e1.pop();
		}

		while (!e2.empty())
		{
			e2.pop();
		}

		while (!e3.empty())
		{
			e3.pop();
		}

		while (!e4.empty())
		{
			e4.pop();
		}

		while (!e5.empty())
		{
			e5.pop();
		}
	}
	//row F
	{
		while (!f1.empty())
		{
			f1.pop();
		}

		while (!f2.empty())
		{
			f2.pop();
		}

		while (!f3.empty())
		{
			f3.pop();
		}

		while (!f4.empty())
		{
			f4.pop();
		}

		while (!f5.empty())
		{
			f5.pop();
		}
	}
	//row G
	{
		while (!g1.empty())
		{
			g1.pop();
		}

		while (!g2.empty())
		{
			g2.pop();
		}

		while (!g3.empty())
		{
			g3.pop();
		}

		while (!g4.empty())
		{
			g4.pop();
		}

		while (!g5.empty())
		{
			g5.pop();
		}
	}

	//the below will load all cell stacks with values 0 - 10
	//row A
	{
		int i = 0;
		a1.push(i); // this will load the value 0 into the stack, the reason is so there will be a size to compare for the next line
		while (a1.size() <= MAX_INVENTORY) // this will continue to load values into the given stack until the MAX_INVENTORY size has been reached
		{
			i++;
			a1.push(i);
		}

		i = 0; // i will always be reset to 0 for every cell
		a2.push(i);
		while (a2.size() <= MAX_INVENTORY)
		{
			i++;
			a2.push(i);
		}

		i = 0;
		a3.push(i);
		while (a3.size() <= MAX_INVENTORY)
		{
			i++;
			a3.push(i);
		}

		i = 0;
		a4.push(i);
		while (a4.size() <= MAX_INVENTORY)
		{
			i++;
			a4.push(i);
		}

		i = 0;
		a5.push(i);
		while (a5.size() <= MAX_INVENTORY)
		{
			i++;
			a5.push(i);
		}
	}
	//row B
	{
		int i = 0;
		b1.push(i);
		while (b1.size() <= MAX_INVENTORY)
		{
			i++;
			b1.push(i);
		}

		i = 0;
		b2.push(i);
		while (b2.size() <= MAX_INVENTORY)
		{
			i++;
			b2.push(i);
		}

		i = 0;
		b3.push(i);
		while (b3.size() <= MAX_INVENTORY)
		{
			i++;
			b3.push(i);
		}

		i = 0;
		b4.push(i);
		while (b4.size() <= MAX_INVENTORY)
		{
			i++;
			b4.push(i);
		}

		i = 0;
		b5.push(i);
		while (b5.size() <= MAX_INVENTORY)
		{
			i++;
			b5.push(i);
		}
	}
	//row C
	{
		int i = 0;
		c1.push(i);
		while (c1.size() <= MAX_INVENTORY)
		{
			i++;
			c1.push(i);
		}

		i = 0;
		c2.push(i);
		while (c2.size() <= MAX_INVENTORY)
		{
			i++;
			c2.push(i);
		}

		i = 0;
		c3.push(i);
		while (c3.size() <= MAX_INVENTORY)
		{
			i++;
			c3.push(i);
		}

		i = 0;
		c4.push(i);
		while (c4.size() <= MAX_INVENTORY)
		{
			i++;
			c4.push(i);
		}

		i = 0;
		c5.push(i);
		while (c5.size() <= MAX_INVENTORY)
		{
			i++;
			c5.push(i);
		}
	}
	//row D
	{
		int i = 0;
		d1.push(i);
		while (d1.size() <= MAX_INVENTORY)
		{
			i++;
			d1.push(i);
		}

		i = 0;
		d2.push(i);
		while (d2.size() <= MAX_INVENTORY)
		{
			i++;
			d2.push(i);
		}

		i = 0;
		d3.push(i);
		while (d3.size() <= MAX_INVENTORY)
		{
			i++;
			d3.push(i);
		}

		i = 0;
		d4.push(i);
		while (d4.size() <= MAX_INVENTORY)
		{
			i++;
			d4.push(i);
		}

		i = 0;
		d5.push(i);
		while (d5.size() <= MAX_INVENTORY)
		{
			i++;
			d5.push(i);
		}
	}
	//row E
	{
		int i = 0;
		e1.push(i);
		while (e1.size() <= MAX_INVENTORY)
		{
			i++;
			e1.push(i);
		}

		i = 0;
		e2.push(i);
		while (e2.size() <= MAX_INVENTORY)
		{
			i++;
			e2.push(i);
		}

		i = 0;
		e3.push(i);
		while (e3.size() <= MAX_INVENTORY)
		{
			i++;
			e3.push(i);
		}

		i = 0;
		e4.push(i);
		while (e4.size() <= MAX_INVENTORY)
		{
			i++;
			e4.push(i);
		}

		i = 0;
		e5.push(i);
		while (e5.size() <= MAX_INVENTORY)
		{
			i++;
			e5.push(i);
		}
	}
	//row F
	{
		int i = 0;
		f1.push(i);
		while (f1.size() <= MAX_INVENTORY)
		{
			i++;
			f1.push(i);
		}

		i = 0;
		f2.push(i);
		while (f2.size() <= MAX_INVENTORY)
		{
			i++;
			f2.push(i);
		}

		i = 0;
		f3.push(i);
		while (f3.size() <= MAX_INVENTORY)
		{
			i++;
			f3.push(i);
		}

		i = 0;
		f4.push(i);
		while (f4.size() <= MAX_INVENTORY)
		{
			i++;
			f4.push(i);
		}

		i = 0;
		f5.push(i);
		while (f5.size() <= MAX_INVENTORY)
		{
			i++;
			f5.push(i);
		}
	}
	//row G
	{
		int i = 0;
		g1.push(i);
		while (g1.size() <= MAX_INVENTORY)
		{
			i++;
			g1.push(i);
		}

		i = 0;
		g2.push(i);
		while (g2.size() <= MAX_INVENTORY)
		{
			i++;
			g2.push(i);
		}

		i = 0;
		g3.push(i);
		while (g3.size() <= MAX_INVENTORY)
		{
			i++;
			g3.push(i);
		}

		i = 0;
		g4.push(i);
		while (g4.size() <= MAX_INVENTORY)
		{
			i++;
			g4.push(i);
		}

		i = 0;
		g5.push(i);
		while (g5.size() <= MAX_INVENTORY)
		{
			i++;
			g5.push(i);
		}
	}
}

// function to be used with display function to show the updated value for any cell at any time
int update(int i, int n)
{// the below will check if any cell is empty and if so will load that cell with the value 0
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

	// this function will use the global stack variables and return their top values to be displayed in the display function
	//this is done by taking the variables passed in from display (the ith row and the nth column) and using the if/else statments for comparison
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
	return 0;
}

// function will construct the visual of the vending machine
void display(int content[][C], int rows)
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
			cout << "| " << content[i][n] << " ";
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

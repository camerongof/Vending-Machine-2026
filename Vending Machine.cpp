// Vending Machine.cpp : Defines the entry point for the application.
//

#include "consoleUI.h"
#include "machineHeader.h"


int main()
{
	VendingMachine machine; // create one machine that retains its prices and inventory for the full program
	runApplication(machine); // begin the console menus and pass them the machine state
	return 0;
}

// TODO (completed 2026): buyItem was originally commented out and only compared float credit
// to a private price array. VendingMachine::purchase now checks the selected cell, checks stock,
// compares integer cents, removes one item, and returns the customer's remaining credit.

// DEPRECATED: changeMoney was an unfinished floating point remainder function. Wallet credit and
// every slot price now use integer cents, so subtraction returns the exact remaining credit directly.

// DEPRECATED: the original main function contained every supplier, customer, money, and price loop.
// Those menus now live in consoleUI.cpp so this entry point only creates the machine and starts the UI.

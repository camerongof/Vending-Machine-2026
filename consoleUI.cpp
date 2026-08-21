#include "consoleUI.h"

#include "machineHeader.h"

#include <array>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>


namespace
{
	constexpr size_t MONEY_TYPES = 5; // number of supported money denominations
	constexpr array<int, MONEY_TYPES> MONEY_VALUES = { 100, 25, 10, 5, 1 }; // value of each denomination in cents
	constexpr array<const char*, MONEY_TYPES> MONEY_NAMES = { "Dollars", "Quarters", "Dimes", "Nickels", "Pennies" }; // menu name for each denomination

	struct Wallet // holds the customer's pocket money and the credit already entered into the machine
	{
		array<int, MONEY_TYPES> counts{}; // stores the available count for each denomination
		int creditInCents = 0; // stores inserted money separately from the remaining pocket money

		int pocketTotalInCents() const
		{
			int total = 0; // begins the total at zero before adding each denomination

			for (size_t index = 0; index < MONEY_TYPES; index++) // add the value of every denomination in the wallet
			{
				total += counts[index] * MONEY_VALUES[index];
			}

			return total;
		}
	};

	string formatMoney(int cents)
	{
		ostringstream output; // formats cents without changing the formatting used by cout
		output << '$' << cents / 100 << '.' << setw(2) << setfill('0') << cents % 100;
		return output.str();
	}

	void clearScreen()
	{
		cout << "\x1B[2J\x1B[H"; // clear the terminal and move the cursor back to the top-left corner
	}

	void displayTitle()
	{
		cout << "\t\tVending Machine\n"; // keep the title used by the original menus
	}

	void waitForEnter()
	{
		cout << "\n\tPress Enter to continue...";
		string unusedInput;
		getline(cin, unusedInput); // wait for a full line because all menu input also uses getline
	}

	int readIntInRange(const string& prompt, int minimum, int maximum)
	{
		while (true) // continue asking until the user enters one whole number inside the requested range
		{
			cout << prompt;
			string input;

			if (!getline(cin, input)) // exit cleanly if the console input stream is closed
			{
				exit(0);
			}

			istringstream parser(input); // parse the line without leaving cin in a failed state
			int value;
			char extraCharacter;

			if (parser >> value && !(parser >> extraCharacter) && value >= minimum && value <= maximum) // accept only one valid integer
			{
				return value;
			}

			cout << "\n\tError: enter a number from " << minimum << " to " << maximum << ".\n";
		}
	}

	CellPosition readCellPosition()
	{
		char rowLabel = 0;

		while (rowLabel < 'A' || rowLabel > 'G') // continue asking until the user enters one row from A through G
		{
			cout << "\n\tInput cell row (ex:A): ";
			string input;
			getline(cin, input);

			istringstream parser(input); // read one character and reject any extra non-space input
			char extraCharacter;

			if (parser >> rowLabel && !(parser >> extraCharacter))
			{
				rowLabel = static_cast<char>(toupper(static_cast<unsigned char>(rowLabel))); // allow either uppercase or lowercase rows
			}
			else
			{
				rowLabel = 0;
			}

			if (rowLabel < 'A' || rowLabel > 'G')
			{
				cout << "\n\tError: enter one row from A to G.\n";
			}
		}

		const int columnNumber = readIntInRange("\n\tInput cell column (ex:1): ", 1, static_cast<int>(MACHINE_COLUMNS));
		return { static_cast<size_t>(rowLabel - 'A'), static_cast<size_t>(columnNumber - 1) }; // convert the displayed labels to zero-based indexes
	}

	Wallet createWallet()
	{
		static mt19937 randomEngine(random_device{}()); // retain one random engine for every customer session
		uniform_int_distribution<int> moneyCount(1, 10); // match the original range of one to ten of each denomination
		Wallet wallet;

		for (int& count : wallet.counts) // assign a random count to every denomination in the wallet
		{
			count = moneyCount(randomEngine);
		}

		return wallet;
	}

	void displayWallet(const Wallet& wallet)
	{
		cout << "\n\tYou find some money in your pocket:";
		cout << "\n\tDol: " << wallet.counts[0]
			<< " Q: " << wallet.counts[1]
			<< " D: " << wallet.counts[2]
			<< " N: " << wallet.counts[3]
			<< " P: " << wallet.counts[4]
			<< " Total: " << formatMoney(wallet.pocketTotalInCents())
			<< " Credit: " << formatMoney(wallet.creditInCents) << '\n';
	}

	void runPriceScreen(const VendingMachine& machine)
	{
		clearScreen();
		displayTitle();
		machine.displayPrices(cout); // display every cell using the prices owned by the machine
		waitForEnter();
	}

	void runEnterMoneyMenu(const VendingMachine& machine, Wallet& wallet)
	{
		bool finished = false;

		while (!finished) // continue accepting denominations until the customer selects Done
		{
			clearScreen();
			displayTitle();
			machine.displayInventory(cout);
			displayWallet(wallet);

			cout << "\n\tEnter Money:\n";
			for (size_t index = 0; index < MONEY_TYPES; index++) // construct one menu option for each supported denomination
			{
				cout << "\t" << index + 1 << ". " << MONEY_NAMES[index] << '\n';
			}
			cout << "\t6. Done\n";

			const int choice = readIntInRange("\t", 1, 6);
			if (choice == 6)
			{
				finished = true;
				continue;
			}

			const size_t moneyIndex = static_cast<size_t>(choice - 1); // convert the menu choice to the matching array index
			const int availableCount = wallet.counts[moneyIndex];
			const int amount = readIntInRange("\n\tHow many?\n\t", 0, availableCount);

			wallet.counts[moneyIndex] -= amount; // remove the inserted money from the customer's pocket
			wallet.creditInCents += amount * MONEY_VALUES[moneyIndex]; // add the exact cent value to the machine credit
		}
	}

	void runPurchase(VendingMachine& machine, Wallet& wallet)
	{
		const CellPosition position = readCellPosition(); // ask for the A-G and 1-5 cell that should be purchased
		const PurchaseResult result = machine.purchase(position, wallet.creditInCents);

		switch (result.status) // display a message that matches the reason the purchase passed or failed
		{
		case PurchaseStatus::Ok:
			wallet.creditInCents = result.remainingCreditInCents; // keep the credit returned by the successful purchase
			cout << "\n\tPurchase complete. Remaining credit: " << formatMoney(wallet.creditInCents) << "\n";
			break;
		case PurchaseStatus::OutOfStock:
			cout << "\n\tError: this cell is empty.\n";
			break;
		case PurchaseStatus::InsufficientCredit:
			cout << "\n\tError: item costs " << formatMoney(result.priceInCents)
				<< " but current credit is " << formatMoney(wallet.creditInCents) << ".\n";
			break;
		case PurchaseStatus::InvalidCell:
			cout << "\n\tError: the selected cell does not exist.\n";
			break;
		}

		waitForEnter();
	}

	void runSupplierMenu(VendingMachine& machine)
	{
		bool finished = false;

		while (!finished) // continue showing supplier options until Exit submenu is selected
		{
			clearScreen();
			displayTitle();
			machine.displayInventory(cout);
			cout << "\n\tSupplier menu:\n"
				<< "\t1. Load all\n"
				<< "\t2. Unload all\n"
				<< "\t3. Load specific cell\n"
				<< "\t4. Unload specific cell\n"
				<< "\t5. Exit submenu\n";

			const int choice = readIntInRange("\t", 1, 5);
			switch (choice)
			{
			case 1:
				machine.loadAll(); // fill every cell to 10
				break;
			case 2:
				machine.unloadAll(); // empty every cell
				break;
			case 3:
				machine.loadCell(readCellPosition()); // fill the selected validated cell to 10
				break;
			case 4:
				machine.unloadCell(readCellPosition()); // empty the selected validated cell
				break;
			case 5:
				finished = true;
				break;
			}
		}
	}

	void runCustomerMenu(VendingMachine& machine)
	{
		Wallet wallet = createWallet(); // create a new random pocket amount every time the customer menu is entered
		bool finished = false;

		while (!finished) // continue showing customer options until Exit submenu is selected
		{
			clearScreen();
			displayTitle();
			machine.displayInventory(cout);
			displayWallet(wallet);
			cout << "\n\tCustomer menu:\n"
				<< "\t1. See Price\n"
				<< "\t2. Enter money\n"
				<< "\t3. Buy item\n"
				<< "\t4. Unload specific cell\n"
				<< "\t5. Exit submenu\n";

			const int choice = readIntInRange("\t", 1, 5);
			switch (choice)
			{
			case 1:
				runPriceScreen(machine); // show the price assigned to every machine cell
				break;
			case 2:
				runEnterMoneyMenu(machine, wallet); // move selected pocket money into machine credit
				break;
			case 3:
				runPurchase(machine, wallet); // attempt to vend one item from the selected cell
				break;
			case 4:
				// DEPRECATED BEHAVIOR: the original customer menu allowed inventory to be unloaded.
				// This option remains here to preserve the requested functionality, but would normally be supplier-only.
				machine.unloadCell(readCellPosition());
				break;
			case 5:
				finished = true;
				break;
			}
		}
	}
}

void runApplication(VendingMachine& machine)
{
	bool finished = false;

	while (!finished) // continue showing the main menu until Exit program is selected
	{
		clearScreen();
		displayTitle();
		machine.displayInventory(cout);
		cout << "\n\tMain menu:\n"
			<< "\t1. Supplier menu\n"
			<< "\t2. Customer menu\n"
			<< "\t3. Exit program\n";

		const int choice = readIntInRange("\t", 1, 3);
		switch (choice)
		{
		case 1:
			runSupplierMenu(machine); // open the menu used to load and unload inventory
			break;
		case 2:
			runCustomerMenu(machine); // open the menu used to view prices, enter money, and buy items
			break;
		case 3:
			finished = true;
			break;
		}
	}
}


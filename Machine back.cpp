#include "machineHeader.h"

#include <iomanip>
#include <ostream>
#include <random>


VendingMachine::VendingMachine()
{
	setPrices(); // assign prices once when the vending machine is created
}

void VendingMachine::setPrices()
{
	random_device randomSource; // receives a seed value from the operating system
	mt19937 randomEngine(randomSource()); // generates the random values used for each cell
	uniform_int_distribution<int> quarterUnits(1, 20); // represents prices from one to twenty quarters

	for (auto& row : slots) // loop through each row in the fixed vending machine grid
	{
		for (auto& slot : row) // loop through each cell in the current row
		{
			slot.priceInCents = quarterUnits(randomEngine) * 25; // convert the random quarter amount to cents
		}
	}
}

void VendingMachine::loadAll()
{
	for (auto& row : slots) // loop through each row that needs to be loaded
	{
		for (auto& slot : row) // loop through each cell in the current row
		{
			slot.quantity = MAX_INVENTORY; // fill the cell to the same maximum used by the original stacks
		}
	}
}

void VendingMachine::unloadAll()
{
	for (auto& row : slots) // loop through each row that needs to be unloaded
	{
		for (auto& slot : row) // loop through each cell in the current row
		{
			slot.quantity = 0; // set the displayed count to empty
		}
	}
}

bool VendingMachine::loadCell(CellPosition position)
{
	if (!isValid(position)) // prevent an invalid row or column from accessing the array
	{
		return false;
	}

	slots[position.row][position.column].quantity = MAX_INVENTORY; // fill the selected cell to 10
	return true;
}

bool VendingMachine::unloadCell(CellPosition position)
{
	if (!isValid(position)) // prevent an invalid row or column from accessing the array
	{
		return false;
	}

	slots[position.row][position.column].quantity = 0; // empty the selected cell
	return true;
}

PurchaseResult VendingMachine::purchase(CellPosition position, int availableCreditInCents)
{
	if (!isValid(position)) // return an error before trying to read an invalid cell
	{
		return { PurchaseStatus::InvalidCell, 0, availableCreditInCents };
	}

	Slot& selectedSlot = slots[position.row][position.column]; // store a reference to the selected cell for the remaining checks

	if (selectedSlot.quantity == 0) // an empty cell cannot vend an item
	{
		return { PurchaseStatus::OutOfStock, selectedSlot.priceInCents, availableCreditInCents };
	}

	if (availableCreditInCents < selectedSlot.priceInCents) // compare money as whole cents to avoid floating point rounding
	{
		return { PurchaseStatus::InsufficientCredit, selectedSlot.priceInCents, availableCreditInCents };
	}

	selectedSlot.quantity--; // remove one item after all purchase checks have passed
	availableCreditInCents -= selectedSlot.priceInCents; // deduct the selected price from the customer's credit
	return { PurchaseStatus::Ok, selectedSlot.priceInCents, availableCreditInCents };
}

int VendingMachine::quantityAt(CellPosition position) const
{
	if (!isValid(position)) // return a safe value when the caller supplies an invalid cell
	{
		return 0;
	}

	return slots[position.row][position.column].quantity;
}

int VendingMachine::priceAt(CellPosition position) const
{
	if (!isValid(position)) // return a safe value when the caller supplies an invalid cell
	{
		return 0;
	}

	return slots[position.row][position.column].priceInCents;
}

void VendingMachine::displayInventory(ostream& output) const
{
	output << "\t----------------------------\n";
	output << "\t| /| 1 | 2 | 3 | 4 | 5 |\\ |\n";
	output << "\t----------------------------\n";

	for (size_t row = 0; row < MACHINE_ROWS; row++) // construct the display one lettered row at a time
	{
		const char rowLabel = static_cast<char>('A' + row); // convert row 0-6 to its A-G label
		output << "\t|" << rowLabel << "/";

		for (size_t column = 0; column < MACHINE_COLUMNS; column++) // add the five inventory counts for this row
		{
			output << "|" << setw(2) << slots[row][column].quantity << " ";
		}

		output << "|\\" << rowLabel << "|\n";
		output << "\t----------------------------\n";
	}

	output << "\t|        || PUSH ||       |\n";
}

void VendingMachine::displayPrices(ostream& output) const
{
	const ios::fmtflags previousFlags = output.flags(); // save the caller's existing number formatting
	const streamsize previousPrecision = output.precision(); // save the caller's existing decimal precision

	output << fixed << setprecision(2); // display every price with two decimal places
	output << "\t-----------------------------------------------\n";
	output << "\t| /|    1 |    2 |    3 |    4 |    5 |\\ |\n";
	output << "\t-----------------------------------------------\n";

	for (size_t row = 0; row < MACHINE_ROWS; row++) // construct the price display one lettered row at a time
	{
		const char rowLabel = static_cast<char>('A' + row); // convert row 0-6 to its A-G label
		output << "\t|" << rowLabel << "/";

		for (size_t column = 0; column < MACHINE_COLUMNS; column++) // add the five prices for this row
		{
			const double priceInDollars = slots[row][column].priceInCents / 100.0; // convert cents for display only
			output << "|" << setw(6) << priceInDollars;
		}

		output << "|\\" << rowLabel << "|\n";
		output << "\t-----------------------------------------------\n";
	}

	output << "\t|                   || PUSH ||                |\n";
	output.flags(previousFlags); // restore the number formatting used before this function
	output.precision(previousPrecision); // restore the previous decimal precision
}

bool VendingMachine::isValid(CellPosition position)
{
	return position.row < MACHINE_ROWS && position.column < MACHINE_COLUMNS; // both indexes must remain inside the fixed grid
}

// DEPRECATED: the original load and unload functions pushed or popped every number from 0 to 10
// on 35 separate stacks. The quantity assignments above keep the same visible counts and results
// without retaining ten historical integers for every full cell.

// DEPRECATED: the original update function contained an A1-G5 if/else tree to find a stack.
// SlotGrid allows the validated row and column to access the matching cell directly.

// DEPRECATED: the original setPrice function used rand() and was called twice during startup.
// setPrices now uses the standard random library once during construction and stores prices as cents.


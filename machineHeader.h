#pragma once

#include <array>
#include <cstddef>
#include <iosfwd>

using namespace std;

constexpr size_t MACHINE_ROWS = 7; // fixed number of lettered rows in the vending machine
constexpr size_t MACHINE_COLUMNS = 5; // fixed number of numbered columns in the vending machine
constexpr int MAX_INVENTORY = 10; // maximum number of items that can be held in one cell

struct CellPosition // holds the zero-based row and column for one vending machine cell
{
	size_t row;
	size_t column;
};

enum class PurchaseStatus // lists each result that can be returned by the purchase function
{
	Ok,
	InvalidCell,
	OutOfStock,
	InsufficientCredit
};

struct PurchaseResult // returns the status and updated money values from a purchase attempt
{
	PurchaseStatus status;
	int priceInCents;
	int remainingCreditInCents;
};

class VendingMachine
{
public:
	VendingMachine(); // constructs the machine with empty cells and a random price for each cell

	void loadAll(); // loads every cell to MAX_INVENTORY
	void unloadAll(); // unloads every cell to 0
	bool loadCell(CellPosition position); // loads one validated cell to MAX_INVENTORY
	bool unloadCell(CellPosition position); // unloads one validated cell to 0
	PurchaseResult purchase(CellPosition position, int availableCreditInCents); // attempts to vend one item from the selected cell

	int quantityAt(CellPosition position) const; // returns the current item count for one cell
	int priceAt(CellPosition position) const; // returns the price of one cell in cents
	void displayInventory(ostream& output) const; // displays the A-G and 1-5 inventory grid
	void displayPrices(ostream& output) const; // displays the A-G and 1-5 price grid

private:
	struct Slot // groups the values that belong to one vending machine cell
	{
		int priceInCents = 0;
		int quantity = 0;
	};

	using SlotRow = array<Slot, MACHINE_COLUMNS>; // represents one row of five cells
	using SlotGrid = array<SlotRow, MACHINE_ROWS>; // represents the full seven by five machine

	SlotGrid slots{}; // stores all prices and inventory without separate A1-G5 stack variables

	void setPrices(); // assigns a price from $0.25 to $5.00 to every cell
	static bool isValid(CellPosition position); // checks that a row and column are inside the grid
};

// TODO (completed 2026): ErrorStatus was originally declared but never connected to the menus.
// PurchaseStatus now reports the errors that can actually occur during a purchase.

// DEPRECATED: the original header declared 35 stacks named a1 through g5 and stored each count
// as a stack of every number below it. SlotGrid now stores one quantity and one price per cell,
// which keeps the same A-G by 1-5 layout without the duplicate stack memory or global variables.

// DEPRECATED: programStart, intial, setPrice, showPrice, returnPrice, update, and display were
// previously exposed as separate setup and display functions. Construction now performs setup,
// and the smaller public functions above expose only the operations used by the menus.


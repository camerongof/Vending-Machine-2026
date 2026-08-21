# Vending Machine

## Project purpose

This project began as a college C++ assignment and was built to emulate the basic operations of a vending machine. The project is now being used as a controlled test of AI agent capability, including reading older code, understanding its intended behavior, preserving that behavior, modernizing the structure, and verifying the finished program.

The program remains a Windows console application and targets the Visual Studio 2026 `v145` toolset with C++17.

## What the original program accomplished

The original program represented a vending machine as a grid with seven lettered rows and five numbered columns. This created 35 selectable cells ranging from A1 to G5.

Each cell used its own stack to represent inventory. The number at the top of the stack represented the current item count, with a maximum inventory of 10 items per cell.

The program provided two main operating areas:

- The supplier menu allowed every cell to be loaded or unloaded at once.
- The supplier menu also allowed one specific A-G and 1-5 cell to be loaded or unloaded.
- The customer menu displayed the price assigned to every cell.
- The customer received a random amount of dollars, quarters, dimes, nickels, and pennies.
- Money could be moved from the customer's pocket into vending machine credit.
- A purchase checked the selected cell, available inventory, item price, and customer credit.
- A successful purchase removed one item and deducted its price from the available credit.

Prices were randomly assigned in quarter increments from $0.25 to $5.00. The console display showed the current quantity for every cell and updated after supplier or customer operations.

The program also retained the customer menu option for unloading a specific cell. This is not a normal customer operation, but it remains available because it was part of the original program behavior.

## What the modernization accomplished

The modernization kept the same vending machine behavior while replacing the repeated storage and control paths with smaller reusable functions.

The 35 separate stacks were replaced by one fixed `std::array` grid. Each grid position now contains one slot with a price and quantity. This keeps the same A-G by 1-5 layout without storing every previous inventory number or maintaining separate variables named A1 through G5.

The small row and column loops were kept because the machine is naturally a two-dimensional grid. These loops do not allocate additional memory. The repeated A1-G5 `if` and `else` branches were removed because a validated row and column can now access the correct slot directly.

Money is stored as integer cents instead of floating point values. This allows prices, credit, and purchase deductions to be calculated without decimal rounding problems.

Random prices and customer money now use the C++ standard random library. Prices are assigned once when the vending machine is created, and a new random wallet is created whenever the customer menu is entered.

Console input now reads and validates a complete line. Letters, extra characters, and numbers outside the accepted range display an error and allow the user to try again without leaving the input stream in a failed state.

The program was also separated by responsibility:

- `Vending Machine.cpp` creates the vending machine and starts the application.
- `machineHeader.h` declares the machine grid, purchase results, and public operations.
- `Machine back.cpp` implements inventory, pricing, purchasing, and grid display behavior.
- `consoleUI.h` declares the console application entry function.
- `consoleUI.cpp` contains the main, supplier, customer, money, price, and purchase menus.

Completed TODO items include connecting the purchase operation, reporting purchase results, deducting credit, and removing inventory. Deprecated functions and storage methods have explanations near the locations where their replacements are now used.

The modernization reduced the source and header files from roughly 3,400 lines to approximately 600 lines while keeping the same menu flow and visible vending machine operations.

## Building the project

1. Open `Vending Machine.sln` in Visual Studio 2026.
2. Select the `Debug` configuration and `x64` platform.
3. Build the solution.
4. Run the program from Visual Studio or use `x64/Debug/Vending Machine.exe` after the build completes.

## Current status

The Debug x64 configuration builds successfully with the Visual Studio 2026 `v145` toolset. Supplier loading, supplier unloading, price display, money entry, purchases, remaining credit, inventory reduction, invalid input recovery, and program exit have been tested.

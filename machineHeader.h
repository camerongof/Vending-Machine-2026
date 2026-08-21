#pragma once

#include <stack>

using namespace std;


const int R = 7, C = 5, MAX_INVENTORY = 10; //constant values for rows and columns, max size for stacks, allows for 0 - 10

// initialization for integer stacks of each cell
extern stack<int> a1, a2, a3, a4, a5, b1, b2, b3, b4, b5, c1, c2, c3, c4, c5;
extern stack<int> d1, d2, d3, d4, d5, e1, e2, e3, e4, e5, f1, f2, f3, f4, f5, g1, g2, g3, g4, g5;

enum class ErrorStatus
{
	Invalid_Status,
	Invalid_Input,
	Invalid_Amount,
	Exit_Ok,
	Exit_NotOk,
	Ok
};
class VendingMachine
{
public:
	VendingMachine(); // constructor

	void programStart();
	void intial();
	void setPrice();
	void showPrice();
	double returnPrice(int i, int n);
	int update(int i, int n);
	void display();

private:
	double price[R][C];
	int content[R][C];
};

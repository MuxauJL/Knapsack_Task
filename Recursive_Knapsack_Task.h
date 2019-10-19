#pragma once
#include "AKnapsack_Task.h"
#include <map>

using k_w = std::pair<short int, short int>;
using opt_z_f_x = std::pair<short int, std::vector<bool>>;
class Recursive_Knapsack_Task :
	public AKnapsack_Task
{
private:
	std::map<k_w, opt_z_f_x> cache;
public:
	Recursive_Knapsack_Task(short int A, short int n, std::vector<short int> a, std::vector<short int> C) :
		AKnapsack_Task(A, n, a, C) {}
	virtual short int solve();
	short int solve_z(short int k, short int w);
};


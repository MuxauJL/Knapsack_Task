#pragma once
#include "AKnapsack_Task.h"
#include <map>

using k_w = std::pair<int, int>;
using opt_z_f_x = std::pair<int, std::vector<int>>;
class Recursive_Knapsack_Task :
	public AKnapsack_Task
{
private:
	std::map<k_w, opt_z_f_x> cache;
public:
	Recursive_Knapsack_Task(int A, int n, std::vector<int> a, std::vector<int> C) :
		AKnapsack_Task(A, n, a, C) {}
	virtual int solve();
	int solve_z(int k, int w);
};


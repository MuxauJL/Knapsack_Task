#pragma once
#include "AKnapsack_Task.h"
#include <map>

using pos = std::pair<short int, short int>;
class Table_Knapsack_Task :
	public AKnapsack_Task
{
private:
	std::vector<short int> v1, v2;
	std::map<pos, std::vector<bool>> x_w_k;
	std::vector<short int>* previous_f;
	std::vector<short int>* next_f;
public:
	Table_Knapsack_Task(short int A, short int n, std::vector<short int> a, std::vector<short int> C) :
		AKnapsack_Task(A, n, a, C) {
		v1.resize(A + 1, 0);
		v2.resize(A + 1, 0);
	}
	virtual short int solve(short int k);
};


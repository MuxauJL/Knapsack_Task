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
		v1.reserve(A + 1);
		v2.reserve(A + 1);
		previous_f = &v1;
		next_f = &v2;
		for (int w = 0; w <= A; ++w) {
			if (a[0] <= w) {
				v1.push_back(C[0]);
				x_w_k[pos(w, 0)] = { 1 };
			}
			else {
				v1.push_back(0);
				x_w_k[pos(w, 0)] = { 0 };
			}
			v2.push_back(0);
		}
	}
	virtual short int solve();
};


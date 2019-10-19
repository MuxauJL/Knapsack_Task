#pragma once
#include "AKnapsack_Task.h"
#include "ISort_Strategy.h"

class Greedy_Knapsack_Task :
	public AKnapsack_Task
{
private:
	double percent;
	std::vector<short int> indexes;
	ISort_Strategy* sort_strategy;
public:
	Greedy_Knapsack_Task(short int A, short int n, std::vector<short int> a, std::vector<short int> C, ISort_Strategy * strategy) :
		AKnapsack_Task(A, n, a, C), sort_strategy(strategy) {
		percent = 0;
		sort_strategy->sort(A, n, a, C, indexes);
	}
	void set_percent(double p) { percent = p; }
	virtual short int solve() {
		int capacity = A;
		int cost = 0;
		for (int i = 0; i < n/* * percent*/; ++i) {
			int current = a[indexes[i]];
			if (capacity - current >= 0) {
				x[indexes[i]] = 1;
				capacity -= current;
				cost += C[indexes[i]];
			}
		}
		return cost;
	}
};
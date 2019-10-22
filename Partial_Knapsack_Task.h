#pragma once
#include "AKnapsack_Task.h"
#include "ISort_Strategy.h"
#include "Table_Knapsack_Task.h"
#include <memory>

class Partial_Knapsack_Task :
	public AKnapsack_Task
{
private:
	std::vector<short int> indexes;
	ISort_Strategy* sort_strategy;
	std::unique_ptr<AKnapsack_Task> solver;
public:
	Partial_Knapsack_Task(short int A, short int n, std::vector<short int> a, std::vector<short int> C, ISort_Strategy * strategy) :
		AKnapsack_Task(A, n, a, C), sort_strategy(strategy) {
		sort_strategy->sort(A, n, a, C, indexes);
		std::vector<short int> sorted_a, sorted_C;
		sorted_a.reserve(n);
		sorted_C.reserve(n);
		for (size_t i = 0; i < n; ++i) {
			sorted_a.push_back(a[indexes[i]]);
			sorted_C.push_back(C[indexes[i]]);
		}
		solver = std::unique_ptr<AKnapsack_Task>(
			new Table_Knapsack_Task(A, n, sorted_a, sorted_C));
	}
	virtual short int solve(short int k) {
		auto result_f = solver->solve(k);
		auto result_x = solver->get_x();
		for (size_t i = 0; i < result_x.size(); ++i) 
			if (result_x[i])
				x[indexes[i]] = 1;
		return result_f;
	}
};
#pragma once
#include <vector>
class AKnapsack_Task
{
protected:
	short int A;
	short int n;
	std::vector<short int> a;
	std::vector<short int> C;
	std::vector<bool> x;
public:
	AKnapsack_Task(short int A, short int n, std::vector<short int> a, std::vector<short int> C) {
		this->A = A;
		this->n = n;
		this->a = a;
		this->C = C;
		x.resize(n, 0);
	}
	short int solve() { return solve(n); };
	virtual short int solve(short int k) = 0;
	std::vector<bool> get_x() { return x; }
};


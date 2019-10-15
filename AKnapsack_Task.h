#pragma once
#include <vector>
class AKnapsack_Task
{
protected:
	int A;
	int n;
	std::vector<int> a;
	std::vector<int> C;
	std::vector<int> x;
public:
	AKnapsack_Task(int A, int n, std::vector<int> a, std::vector<int> C) {
		this->A = A;
		this->n = n;
		this->a = a;
		this->C = C;
		x.resize(n, 0);
	}
	virtual int solve() = 0;
	std::vector<int> get_x() { return x; }
};


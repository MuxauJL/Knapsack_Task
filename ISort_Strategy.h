#pragma once
#include <vector>
class ISort_Strategy {
public:
	virtual void sort(int A, int n, const std::vector<int>& a, const std::vector<int>& C, std::vector<int>& result_indexes) = 0;
};
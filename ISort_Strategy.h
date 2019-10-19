#pragma once
#include <vector>
class ISort_Strategy {
public:
	virtual void sort(short int A, short int n, const std::vector<short int>& a, const std::vector<short int>& C, std::vector<short int>& result_indexes) = 0;
};
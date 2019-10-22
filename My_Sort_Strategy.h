#pragma once
#include "ISort_Strategy.h"
#include <algorithm>

class My_Sort_Strategy :
	public ISort_Strategy {
	virtual void sort(short int A, short int n, const std::vector<short int>& a, const std::vector<short int>& C, std::vector<short int>& indexes) {
		indexes.reserve(n);
		for (int i = 0; i < n; ++i)
			indexes.push_back(i);

		auto comp = [&a, &C](const int& idx1, const int& idx2) {
			return ((static_cast<double>(C[idx1]) / a[idx1] > static_cast<double>(C[idx2]) / a[idx2]) && C[idx1] > C[idx2]);
		};
		std::sort(indexes.begin(), indexes.end(), comp);
	}
};
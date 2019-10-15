#pragma once
#include "ISort_Strategy.h"
#include <algorithm>

class Basic_Sort_Strategy :
	public ISort_Strategy {
	virtual void sort(int A, int n, const std::vector<int>& a, const std::vector<int>& C, std::vector<int>& indexes) {
		indexes.reserve(n);
		for (int i = 0; i < n; ++i)
			indexes.push_back(i);
		auto comp = [&a, &C](const int& idx1, const int& idx2) {
			return ((double)C[idx1] / a[idx1] > (double)C[idx2] / a[idx2]);
		};
		std::sort(indexes.begin(), indexes.end(), comp);
	}
};

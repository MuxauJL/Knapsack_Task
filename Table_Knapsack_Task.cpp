#include "Table_Knapsack_Task.h"
#include <algorithm>

int Table_Knapsack_Task::solve()
{
	for (size_t k = 1; k < n; ++k) {
		for (size_t w = 0; w <= A; ++w) {
			int f1 = (*previous_f)[w];
			int f2;
			if (a[k] <= w) {
				f2 = C[k] + (*previous_f)[w - a[k]];
				if (f1 <= f2) {
					(*next_f)[w] = f2;
					std::vector<int>* x_ptr = &x_w_k[pos(w, k)];
					*x_ptr = x_w_k[pos(w - a[k], k - 1)];
					x_ptr->push_back(1);
				}
				else {
					(*next_f)[w] = f1;
					std::vector<int>* x_ptr = &x_w_k[pos(w, k)];
					*x_ptr = x_w_k[pos(w, k - 1)];
					x_ptr->push_back(0);
				}
			}
			else {
				(*next_f)[w] = f1;
				std::vector<int>* x_ptr = &x_w_k[pos(w, k)];
				*x_ptr = x_w_k[pos(w, k - 1)];
				x_ptr->push_back(0);
			}
		}
		std::swap(previous_f, next_f);
	}
	auto it = x_w_k.find(pos(A, n - 1));
	if (it != x_w_k.end())
		x = it->second;
	else
		throw ("Can't find x*(z(n,A))");
	return (*previous_f)[A];
}

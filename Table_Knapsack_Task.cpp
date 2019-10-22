#include "Table_Knapsack_Task.h"
#include <algorithm>

short int Table_Knapsack_Task::solve(short int k)
{
	previous_f = &v1;
	next_f = &v2;
	for (int w = 0; w <= A; ++w) {
		if (a[0] <= w) {
			v1[w] = C[0];
			x_w_k[pos(w, 0)] = { 1 };
		}
		else {
			v1[w] = 0;
			x_w_k[pos(w, 0)] = { 0 };
		}
		v2[w] = 0;
	}

	for (size_t i = 1; i < k; ++i) {
		for (size_t w = 0; w <= A; ++w) {
			int f1 = (*previous_f)[w];
			int f2;
			if (a[i] <= w) {
				f2 = C[i] + (*previous_f)[w - a[i]];
				if (f1 <= f2) {
					(*next_f)[w] = f2;
					std::vector<bool>* x_ptr = &x_w_k[pos(w, i)];
					*x_ptr = x_w_k[pos(w - a[i], i - 1)];
					x_ptr->push_back(1);
				}
				else {
					(*next_f)[w] = f1;
					std::vector<bool>* x_ptr = &x_w_k[pos(w, i)];
					*x_ptr = x_w_k[pos(w, i - 1)];
					x_ptr->push_back(0);
				}
			}
			else {
				(*next_f)[w] = f1;
				std::vector<bool>* x_ptr = &x_w_k[pos(w, i)];
				*x_ptr = x_w_k[pos(w, i - 1)];
				x_ptr->push_back(0);
			}
		}
		std::swap(previous_f, next_f);
	}
	auto it = x_w_k.find(pos(A, k - 1));
	if (it != x_w_k.end())
		x = it->second;
	else
		throw ("Can't find x*(z(n,A))");
	return (*previous_f)[A];
}

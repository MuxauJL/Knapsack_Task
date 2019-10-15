#include "Recursive_Knapsack_Task.h"

int Recursive_Knapsack_Task::solve()
{
	int result = solve_z(n - 1, A);
	auto it = cache.find(k_w(n - 1, A));
	if (it != cache.end())
		x = it->second.second;
	else
		throw ("Can't find x*(z(n,A))");
	return result;
}

int Recursive_Knapsack_Task::solve_z(int k, int w)
{
	if (k == 0)
		if (a[k] <= w) {
			opt_z_f_x* z_f_x_ptr = &cache[k_w(k, w)];
			z_f_x_ptr->first = C[k];
			z_f_x_ptr->second = { 1 };
			return C[k];
		}
		else {
			opt_z_f_x* z_f_x_ptr = &cache[k_w(k, w)];
			z_f_x_ptr->first = 0;
			z_f_x_ptr->second = { 0 };
			return 0;
		}
	int f1;
	auto it = cache.find(k_w(k - 1, w));
	if (it != cache.end())
		f1 = it->second.first;
	else
		f1 = solve_z(k - 1, w);
	int f2;
	it = cache.find(k_w(k - 1, w - a[k]));
	if (it != cache.end())
		f2 = it->second.first + C[k];
	else
		f2 = solve_z(k - 1, w - a[k]) + C[k];
	if (a[k] <= w) {
		if (f1 <= f2) {
			opt_z_f_x* z_ptr = &cache[k_w(k, w)];
			z_ptr->first = f2;
			z_ptr->second = cache[k_w(k - 1, w - a[k])].second;
			z_ptr->second.push_back(1);
			return f2;
		}
		else {
			opt_z_f_x* z_ptr = &cache[k_w(k, w)];
			z_ptr->first = f1;
			z_ptr->second = cache[k_w(k - 1, w)].second;
			z_ptr->second.push_back(0);
			return f1;
		}
	}
	else {
		opt_z_f_x* z_ptr = &cache[k_w(k, w)];
		z_ptr->first = f1;
		z_ptr->second = cache[k_w(k - 1, w)].second;
		z_ptr->second.push_back(0);
		return f1;
	}
}

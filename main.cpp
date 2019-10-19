#include <iostream>
#include "Recursive_Knapsack_Task.h"
#include "Table_Knapsack_Task.h"
#include "Greedy_Knapsack_Task.h"
#include "Basic_Sort_Strategy.h"
#include <fstream>
#include <omp.h>

int main() {
	std::string dir = "Task3\\";
	std::vector<std::string> files = {
		"task_3_01_n5.txt",
		"task_3_02_n5.txt",
		"task_3_03_n10.txt",
		"task_3_04_n10.txt",
		"task_3_05_n50.txt",
		"task_3_06_n50.txt",
		"task_3_07_n100.txt",
		"task_3_08_n100.txt",
		"task_3_09_n1000.txt",
		"task_3_10_n1000.txt"
	};

	short int A;
	short int n;
	std::vector<short int> a;
	std::vector<short int> C;
	Basic_Sort_Strategy basic_strategy;

	std::ofstream time, basic, my;
	double average = 0;
	time.open("time.csv");
	if (time.is_open()/* && basic.is_open() && my.is_open()*/)
	{
		time << "№;Рекурсивный;Табличный;%;\n";
		for (size_t i = 0; i < files.size(); ++i) {
			//if (i == 8 || i == 9) continue;
			std::ifstream in(dir + files[i]);
			if (in.is_open()) {
				in >> A >> n;
				a.resize(n);
				C.resize(n);
				int value;
				for (int i = 0; i < n; ++i) {
					in >> value;
					a[i] = value;
				}
				for (int i = 0; i < n; ++i) {
					in >> value;
					C[i] = value;
				}
			}
			in.close();
			Recursive_Knapsack_Task r(A, n, a, C);
			Table_Knapsack_Task t(A, n, a, C);
			Greedy_Knapsack_Task greedy_basic(A, n, a, C, &basic_strategy);
			int result;
			double start, end, time_r, time_t;

			start = omp_get_wtime();
			result = r.solve();
			end = omp_get_wtime();
			time_r = end - start;
			std::cout << i + 1 << ")\nRecursive: " << result << '\n';
			for (auto x : r.get_x())
				std::cout << x << " ";
			std::cout << '\n';

			start = omp_get_wtime();
			result = t.solve();
			end = omp_get_wtime();
			time_t = end - start;
			std::cout << "Table: " << result << '\n';
			for (auto x : t.get_x())
				std::cout << x << " ";
			std::cout << '\n';

			for (auto p : { 0.1,0.3,0.5 }) {
				greedy_basic.set_percent(p);
				result = greedy_basic.solve();
				std::cout << "Greedy basic(p = " << p << "): " << result << '\n';
				for (auto x : greedy_basic.get_x())
					std::cout << x << " ";
				std::cout << '\n';
			}

			std::cout << '\n';

			double difference = (time_r - time_t) / (time_r + time_t) * 2;
			time
				<< i + 1 << ';'
				<< time_r << ';'
				<< time_t << ';'
				<< difference << ";\n";
			average += difference;
		}
	}
	time << ";;Среднее;" << average / 10 << ";\n";
	time.close();
	system("pause");
	return 0;
}
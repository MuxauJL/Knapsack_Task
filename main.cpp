#include <iostream>
#include "Recursive_Knapsack_Task.h"
#include "Table_Knapsack_Task.h"
#include "Partial_Knapsack_Task.h"
#include "Basic_Sort_Strategy.h"
#include "My_Sort_Strategy.h"
#include <fstream>
#include <chrono>

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
	My_Sort_Strategy my_strategy;

	std::ofstream time_file, basic_file, my_file;
	double average = 0;
	time_file.open("time.csv");
	basic_file.open("basic.csv");
	my_file.open("my.csv");
	if (time_file.is_open() && basic_file.is_open() && my_file.is_open())
	{
		time_file << "№;Рекурсивный;Табличный;%;\n";
		basic_file << "№;10%;30%;50%;\n";
		my_file << "№;10%;30%;50%;\n";
		for (size_t i = 0; i < files.size(); ++i) {
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
			std::unique_ptr<AKnapsack_Task> r = std::unique_ptr<AKnapsack_Task>(
				new Recursive_Knapsack_Task(A, n, a, C));
			std::unique_ptr<AKnapsack_Task> t = std::unique_ptr<AKnapsack_Task>(
				new Table_Knapsack_Task(A, n, a, C));
			std::unique_ptr<AKnapsack_Task> basic = std::unique_ptr<AKnapsack_Task>(
				new Partial_Knapsack_Task(A, n, a, C, &basic_strategy));
			std::unique_ptr<AKnapsack_Task> my = std::unique_ptr<AKnapsack_Task>(
				new Partial_Knapsack_Task(A, n, a, C, &my_strategy));
			int result;
			std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
			long long time_r, time_t;

			start = std::chrono::high_resolution_clock::now();
			result = r->solve();
			end = std::chrono::high_resolution_clock::now();
			time_r = std::chrono::duration_cast<std::chrono::microseconds>
				(end - start).count();
			std::cout << i + 1 << ")\nRecursive: " << result << '\n';
			for (auto x : r->get_x())
				std::cout << x << " ";
			std::cout << '\n';

			start = std::chrono::high_resolution_clock::now();
			result = t->solve();
			end = std::chrono::high_resolution_clock::now();
			time_t = std::chrono::duration_cast<std::chrono::microseconds>
				(end - start).count();
			std::cout << "Table: " << result << '\n';
			for (auto x : t->get_x())
				std::cout << x << " ";
			std::cout << '\n';

			basic_file << i + 1 << ';';
			my_file << i + 1 << ';';
			for (double p : { 0.1,0.3,0.5 }) {
				short int k = n * p > static_cast<short int>(n * p) ? n * p + 1 : n * p;
				auto basic_result = basic->solve(k);
				auto my_result = my->solve(k);
				std::cout << "Basic(p = " << p << "): " << basic_result << '\n';
				for (auto x : basic->get_x())
					std::cout << x << " ";
				std::cout << '\n';
				std::cout << "My(p = " << p << "): " << my_result << '\n';
				for (auto x : my->get_x())
					std::cout << x << " ";
				std::cout << '\n';
				basic_file
					<< static_cast<double>(result - basic_result) / result << ';';
				my_file
					<< static_cast<double>(result - my_result) / result << ';';
			}
			basic_file << '\n';
			my_file << '\n';
			std::cout << '\n';

			double difference = static_cast<double>((time_r - time_t)) / static_cast<double>((time_r + time_t)) * 2;
			time_file
				<< i + 1 << ';'
				<< time_r << ';'
				<< time_t << ';'
				<< difference << ";\n";
			average += difference;
		}
	}
	time_file << ";;Среднее;" << average / 10 << ";\n";
	time_file.close();
	basic_file.close();
	my_file.close();
	system("pause");
	return 0;
}
#include <iostream>
#include <fstream>
#include<vector>
#include <random>
#include <string>
#include <stdio.h>

void random_file_gen(const char* name, int& lim, int& size) {
	int l_lim = -lim;
	int r_lim = lim;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(l_lim, r_lim);
	std::ofstream file(name);
	for (int i = 0; i < size; i++) {
		int x = dist(gen);
		file << x << " ";
	}
	file.close();
}

void file_splitting_1(int* arr) {
	int count = 1;
	int i = 0;
	std::fstream f1("f1.txt");
	std::fstream f2("f2.txt");
	for (int j = 0; ;j++) {
		if (count == 1) {
			for (; i < sizeof(arr) - 1; i++) {
				if (arr[i] >= arr[i + 1])  f1 << arr[i] << " ";
				else {
					f1 << arr[i] << " ";
					count = 2;
					break;
				}
			}
		}
		else if (count == 2) {
			for (; i < sizeof(arr) - 1; i++) {
				if (arr[i] >= arr[i + 1])  f2 << arr[i] << " ";
				else {
					f2 << arr[i] << " ";
					count = 1;
					break;
				}
			}
		}
	}
	f1.close();
	f2.close();
}

void file_splitting_2(const std::string name1, const std::string name2, int* arr1, int* arr2) {

}

int main() {
	int size, lim;
	std::cin >> lim;
	puts("");
	std::cin >> size;
	puts("");
	int* arr = new int[size];
	FILE* f = fopen("f.txt", "rt");
	if (f == nullptr) {
		puts("File open error!");
		return -1;
	}
	for (int i = 1; i == 4; i++) {
		std::string name = "f" + std::to_string(i) + ".txt";
		FILE* name = fopen(name.c_str(), "wt");
		if (name.c_str() == nullptr) {
			puts("File open error!");
			return -1;
		}
	}
	//FILE* fa = fopen("f.txt", "wt");
	//if (fa == nullptr) {
	//	puts("File open error!");
	//	return -1;
	//}
	//FILE* fb = fopen("f.txt", "wt");
	//if (fb == nullptr) {
	//	puts("File open error!");
	//	return -1;
	//}
	//FILE* fc = fopen("f.txt", "wt");
	//if (fc == nullptr) {
	//	puts("File open error!");
	//	return -1;
	//}
	//FILE* fd = fopen("f.txt", "wt");
	//if (fd == nullptr) {
	//	puts("File open error!");
	//	return -1;
	//}
	random_file_gen("f.txt", lim, size);
	int* arr;
	arr = new int[size];
	while (!feof(f)) {
		std::ifstream file(f);
		for (int i = 0; i < size; i++) {
			file >> arr[i];
		}
	};
	std::string file_name = "f1";
	while ("f1.txt" != nullptr || "f2.txt" != nullptr || "f3.txt" != nullptr || "f4.txt" != nullptr) {

	}

}
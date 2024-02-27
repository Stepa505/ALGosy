#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <stdio.h>

bool random_file_gen(const std::string& name, int& lim, int& size) {
	int l_lim = -lim;
	int r_lim = lim;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(l_lim, r_lim);
	std::ofstream file;
	file.open(name);
	if (!file) {
		puts("File open error!");
		return false;
	}
	for (int i = 0; i < size; i++) {
		int x = dist(gen);
		file << x << " ";
	}
	file.close();
	return true;
}

int main() {
	int size, lim;
	std::cout << "Enter the size of range of numbers in file: ";
	std::cin >> lim;
	puts("");
	std::cout << "Enter the size of file: ";
	std::cin >> size;
	puts("");
	std::string name = "f.txt";
	random_file_gen(name, size, lim);
	//random_file_gen(name, lim, size);
	std::fstream f(name);
	if (!f) return -1;

	std::ofstream f1;
	f1.open("fa.txt");
	if (!f1) return -2;
	f1.close();
	std::fstream fa;
	fa.open("fa.txt");

	std::ofstream f2;
	f2.open("fb.txt");
	if (!f2) return -3;
	f2.close();
	std::fstream fb;
	fb.open("fb.txt");

	//firts splitting
	int a, b;
	f >> a;
	f >> b;
	int count = 1;
	while (f) {
		if (a < b && count == 1) {
			fa << a << " ";
			a = b;
			f >> b;
		}
		else if (a < b && count == 2) {
			fb << a << " ";
			a = b;
			f >> b;
		}
		else if (a >= b && count == 1) {
			fa << a << " " << INT_MIN << " ";
			a = b;
			f >> b;
			count = 2;
		}
		else if (a >= b && count == 2) {
			fb << a << " " << INT_MIN << " ";
			a = b;
			f >> b;
			count = 1;
		}
	}
	if (count == 1) fa << b << " " << INT_MIN;
	else if (count == 2) fb << b << " " << INT_MIN;

	std::ofstream f3;
	f3.open("fc.txt");
	if (!f3) return -4;
	f3.close();
	std::fstream fc;
	fc.open("fc.txt");

	std::ofstream f4;
	f4.open("fd.txt");
	if (!f4) return -5;
	f4.close();
	std::fstream fd;
	fd.open("fd.txt");

	f.close();
	fa.close();
	fb.close();
	fc.close();
	fd.close();
}
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <stdio.h>

void trade(std::string& a, std::string& b) {
	std::string c;
	c = a;
	a = b;
	b = c;
}

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

bool file_splitting(std::string& name1, std::string& name2, std::string& name3, std::string& name4, int& k) {
	std::ofstream f1;
	f1.open(name1);
	if (!f1) return false;
	f1.close();
	std::ifstream file1;
	file1.open(name1);

	std::ofstream f2;
	f2.open(name2);
	if (!f2) return false;
	f2.close();
	std::ifstream file2;
	file2.open(name2);

	std::ofstream file3;
	file3.open(name3);
	if (!file3) return false;

	std::ofstream file4;
	file4.open(name4);
	if (!file4) return false;

	int a, b;
	file1 >> a;
	file2 >> b;
	for (int i = 0; i < k/2 + 1; i++) {
		while (a != INT_MAX && b != INT_MAX) {
			if (a <= b) {
				file3 << a << " ";
				file1 >> a;

			}
			if (b <= a) {
				file3 << a << " ";
				file2 >> b;

			}
		}
		file1 >> a;
		file2 >> b;
		while (a != INT_MAX && b != INT_MAX) {
			if (a <= b) {
				file4 << a << " ";
				file1 >> a;

			}
			if (b <= a) {
				file4 << a << " ";
				file2 >> b;

			}
		}
		file1 >> a;
		file2 >> b;
	}
	file3.close();
	file4.close();
	std::ifstream f4;
	f4.open(name2);
	if (f4.peek() == EOF) return true;
	else return false;	 
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
	std::fstream f(name);
	if (!f) return -1;

	std::ofstream f1;
	f1.open("fa.txt");
	if (!f1) return -2;
	f1.close();
	std::fstream fa;
	fa.open("fa.txt");
	std::string name1 = "fa.txt";

	std::ofstream f2;
	f2.open("fb.txt");
	if (!f2) return -3;
	f2.close();
	std::fstream fb;
	fb.open("fb.txt");
	std::string name2 = "fb.txt";

	//firts splitting
	int a, b;
	f >> a;
	f >> b;
	int count = 1, k = 0;
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
			fa << a << " " << INT_MAX << " ";
			a = b;
			f >> b;
			count = 2;
			k += 1;
		}
		else if (a >= b && count == 2) {
			fb << a << " " << INT_MAX << " ";
			a = b;
			f >> b;
			count = 1;
			k += 1;
		}
	}
	if (count == 1) {
		fa << b << " " << INT_MAX;
		k += 1;
	}
	else if (count == 2) {
		fb << b << " " << INT_MAX;
		k += 1;
	}

	std::ofstream f3;
	f3.open("fc.txt");
	if (!f3) return -4;
	f3.close();
	std::fstream fc;
	fc.open("fc.txt");
	std::string name3 = "fc.txt";

	std::ofstream f4;
	f4.open("fd.txt");
	if (!f4) return -5;
	f4.close();
	std::fstream fd;
	fd.open("fd.txt");
	std::string name4 = "fd.txt";

	//other splittings
	bool res = false;
	while(!res){
		fa.open(name1);
		fb.open(name2);
		fc.open(name3);
		fd.open(name4);
		res = file_splitting(name1, name2, name3, name4, k);
		trade(name1, name3);
		trade(name2, name4);
	}

	f.close();
	fa.close();
	fb.close();
	fc.close();
	fd.close();
}
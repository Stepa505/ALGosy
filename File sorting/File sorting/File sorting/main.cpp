#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <stdio.h>

struct Element {
	int value = 0;
	bool isValid = false;
	void read(std::ifstream& file) {
		file >> value;
		isValid = bool(file);
	}
	bool operator <=(Element& b) const;
	bool operator >(Element& b) const;
};

bool Element::operator <=(Element& b) const {
	if (value <= b.value) return true;
	else return false;
}

bool Element::operator >(Element& b) const {
	if (value > b.value) return true;
	else return false;
}

bool readNext(std::ifstream& input, std::ofstream& output, Element& a, Element& b) {
	output << a.value << " ";
	bool ended = !(b.isValid && a <= b);
	a = b;
	b.read(input);
	return !ended;
}

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

bool file_merge(std::string& name1, std::string& name2, std::string& name3, std::string& name4) {
	std::ifstream fa(name1);
	if (!fa) return -1;
	std::ifstream fb(name2);
	if (!fb) return -1;
	std::ofstream fc(name3);
	if (!fc) return -1;
	std::ofstream fd(name4);
	if (!fd) return -1;
	Element a, b, c, d;
	a.read(fa);
	b.read(fa);
	c.read(fb);
	d.read(fb);
	while (fa || fb) {
		bool otherSequenceEnd1 = false;

		while (fa && a <= b && fb && c <= d) {
			if (a <= c) {
				readNext(fa, fc, a, b);
			}
			else {
				readNext(fb, fc, c, d);
			}
		}

		while (fa && a <= b) {
			if ((otherSequenceEnd1 || a <= c) && a.isValid) {
				readNext(fa, fc, a, b);
			}
			else if (c.isValid && !otherSequenceEnd1) {
				readNext(fb, fc, c, d);
				otherSequenceEnd1 = true;
			}
			if (!fa || a > b) {
				if (otherSequenceEnd1 && a.isValid) {
					readNext(fa, fc, a, b);
				}
				else {
					if (c <= a && a.isValid && c.isValid) {
						readNext(fb, fc, c, d);
						readNext(fa, fc, a, b);
						otherSequenceEnd1 = true;
					}
					else if (a.isValid && c.isValid) {
						readNext(fa, fc, a, b);
						readNext(fb, fc, c, d);
						otherSequenceEnd1 = true;
					}
					else if (a.isValid) {
						readNext(fa, fc, a, b);
						otherSequenceEnd1 = true;
					}
					else if (c.isValid) {
						readNext(fb, fc, c, d);
						otherSequenceEnd1 = true;
					}
				}
				break;
			}
		}
		if (!otherSequenceEnd1) {
			while (fb && c <= d) {
				if ((otherSequenceEnd1 || c <= a) && c.isValid) {
					readNext(fb, fc, c, d);
				}
				else if (a.isValid && !otherSequenceEnd1) {
					readNext(fa, fc, a, b);
					otherSequenceEnd1 = true;
				}
				if (!fb || c > d) {
					if (otherSequenceEnd1 && c.isValid) {
						readNext(fb, fc, c, d);
					}
					else {
						if (c <= a && a.isValid && c.isValid) {
							readNext(fb, fc, c, d);
							readNext(fa, fc, a, b);
						}
						else if (a.isValid && c.isValid) {
							readNext(fa, fc, a, b);
							readNext(fb, fc, c, d);
						}
						else if (a.isValid) {
							readNext(fa, fc, a, b);
						}
						else if (c.isValid) {
							readNext(fb, fc, c, d);
						}
					}
					break;
				}
			}
		}

		fc.swap(fd);

		if (!fa && !fb && a.isValid && c.isValid) {
			if (a <= c) {
				readNext(fa, fc, a, b);
				readNext(fb, fc, c, d);
			}
			else {
				readNext(fb, fc, c, d);
				readNext(fa, fc, a, b);
			}
		}
		else if (!fa && !fb && a.isValid) {
			readNext(fa, fc, a, b);
		}
		else if (!fb && !fa && c.isValid) {
			readNext(fb, fc, c, d);
		}
	}

	fa.close();
	fb.close();
	fc.close();
	fd.close();
	std::ifstream res(name4);

	if (res.peek() == EOF) {
		res.close();
		return true;
	}
	else {
		res.close();
		return false;
	}
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
	random_file_gen(name, lim, size);
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
	if (!f) return -1;
	f >> b;
	while (f) {
		fa << a << " ";
		if (a > b) {
			fa.swap(fb);
		}
		a = b;
		f >> b;
	}
	fa << a << " ";
	f.close();
	fa.close();
	fb.close();


	std::ofstream f3;
	f3.open("fc.txt");
	if (!f3) return -4;
	f3.close();
	std::string name3 = "fc.txt";

	std::ofstream f4;
	f4.open("fd.txt");
	if (!f4) return -5;
	f4.close();
	std::string name4 = "fd.txt";

	//other splittings
	bool res = false;
	while (!res) {
		res = file_merge(name1, name2, name3, name4);
		trade(name1, name3);
		trade(name2, name4);
	}
	std::cout << "Result in file " << name1;

	return 0;
}
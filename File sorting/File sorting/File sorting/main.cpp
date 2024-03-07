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

//bool file_splitting(std::string& name1, std::string& name2, std::string& name3, std::string& name4) {
//	std::ifstream fa(name1);
//	if (!fa) return -1;
//	std::ifstream fb(name2);
//	if (!fb) return -1;
//	std::ofstream fc(name3);
//	if (!fc) return -1;
//	std::ofstream fd(name4);
//	if (!fd) return -1;
//
//	int a, b, c, d;
//	fa >> a >> b;
//	fb >> c >> d;
//	while (fa && fb) {
//		while (a < b && c < d) {
//			if (a < c) {
//				fc << a << " ";
//				a = b;
//				fa >> b;
//			}
//			else {
//				fc << c << " ";
//				c = d;
//				fb >> d;
//			}
//		}
//		if (c >= d) {
//			while (a < b) {
//				if (c < a) {
//					fc << c << " ";
//					c = INT_MAX;
//				}
//				fc << a << " ";
//				a = b;
//				fa >> b;
//			}
//			if (c == INT_MAX) {
//				fc << a << " ";
//				a = b;
//				fa >> b;
//				c = d;
//				fb >> d;
//			}
//			else {
//				if (c < a) {
//					fc << c << " " << a << " ";
//					c = d;
//					fb >> d;
//					a = b;
//					fa >> b;
//				}
//				else {
//					fc << a << " " << c << " ";
//					c = d;
//					fb >> d;
//					a = b;
//					fa >> b;
//				}
//			}
//		}
//		else {
//			while (c < d) {
//				if (a < c) {
//					fc << a << " ";
//					a = INT_MAX;
//				}
//				fc << c << " ";
//				c = d;
//				fb >> d;
//			}
//			if (a == INT_MAX) {
//				fc << c << " ";
//				c = d;
//				fb >> d;
//				a = b;
//				fa >> b;
//			}
//			else {
//				if (a < c) {
//					fc << a << " " << c << " ";
//					c = d;
//					fb >> d;
//					a = b;
//					fa >> b;
//				}
//				else {
//					fc << c << " " << a << " ";
//					c = d;
//					fb >> d;
//					a = b;
//					fa >> b;
//				}
//			}
//		}
//		fc.swap(fd);
//	}
//	if (!fa) {
//		while (fb) {
//			while (c < d) {
//				//if (a < c) {
//				//	fc << a << " " << c << " ";
//				//	a = INT_MAX;
//				//	c = d;
//				//	fb >> d;
//				//}
//				fc << c << " ";
//				c = d;
//				fb >> d;
//			}
//			fc << c << " ";
//			c = d;
//			fb >> d;
//			//if (a != INT_MAX) {
//			//	if (a < c) {
//			//		fc << a << " " << c << " ";
//			//	}
//			//	else {
//			//		fc << c << " " << a << " ";
//			//	}
//			//}
//			//else {
//			//	fc << c << " ";
//			//}
//		}
//		fc << c << " ";
//	}
//	else if(!fb) {
//		while (fa) {
//			while (a < b) {
//				//if (c < a) {
//				//	fc << c << " " << a << " ";
//				//	c = INT_MAX;
//				//	a = b;
//				//	fa >> b;
//				//}
//				fc << a << " ";
//				a = b;
//				fa >> b;
//			}
//			fc << a << " ";
//			a = b;
//			fa >> b;
//			//if (c != INT_MAX) {
//			//	if (a < c) {
//			//		fc << a << " " << c << " ";
//			//	}
//			//	else {
//			//		fc << c << " " << a << " ";
//			//	}
//			//}
//			//else {
//			//	fc << a << " ";
//			//}
//		}
//		fc << a << " ";
//	}
//	fa.close();
//	fb.close();
//	fc.close();
//	fd.close();
//	std::ifstream res(name4);
//	if (res.peek() == EOF) {
//		res.close();
//		return 1;
//	}
//	else { 
//		res.close();
//		return -1; }
//}

bool file_splitting(std::string& name1, std::string& name2, std::string& name3, std::string& name4) {
	std::ifstream fa(name1);
	if (!fa) return -1;
	std::ifstream fb(name2);
	if (!fb) return -1;
	std::ofstream fc(name3);
	if (!fc) return -1;
	std::ofstream fd(name4);
	if (!fd) return -1;

	int a, b, c, d;
	fa >> a >> b;
	fb >> c >> d;

	while (fa || fb) {
		bool otherSequenceEnded = !fa || !fb;  //!fa || !fb;
		while ((fa && a <= b) && (fb && c <= d)) {
			if (a <= c) {
				fc << a << " ";
				a = b;
				fa >> b;
			}
			else {
				fc << c << " ";
				c = d;
				fb >> d;
			}
		}
		while (fa && a <= b) {
			if (otherSequenceEnded || a < c) {
				fc << a << " ";
				a = b;
				fa >> b;
			}
			else {
				fc << c << " ";
				//c = d;
				//fb >> d;
				otherSequenceEnded = true;
			}
		}
		if (!otherSequenceEnded) {
			if (a < c) {
				fc << a << " " << c << " ";
			}
			else if(c <= a){
				fc << c << " " << a << " ";
			}
			//c = d;
			//fb >> d;
			//a = b;
			//fa >> b;
			otherSequenceEnded = true;
		}
		else if(otherSequenceEnded){
			fc << a << " ";
			//a = b;
			//fa >> b;
		}
		while (fb && c <= d) {
			if (otherSequenceEnded || c < a) {
				fc << c << " ";
				c = d;
				fb >> d;
			}
			else {
				fc << a << " ";
				//a = b;
				//fa >> b;
				otherSequenceEnded = true;
			}
		}
		if (!otherSequenceEnded) {
			if (c < a) {
				fc << c << " " << a << " ";
			}
			else if(a <= c){
				fc << a << " " << c << " ";
			}
			otherSequenceEnded = true;
			//c = d;
			//fb >> d;
			//a = b;
			//fa >> b;
		}
		else if(otherSequenceEnded){
			fc << c << " ";
			//c = d;
			//fb >> d;
		}
		c = d;
		fb >> d;
		a = b;
		fa >> b;
		fc.swap(fd);
	}
	fa.close();
	fb.close();
	fc.close();
	fd.close();
	std::ifstream res(name4);
	if (res.peek() == EOF) {
		res.close();
		return 1;
	}
	else {
		res.close();
		return -1;
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
	/*random_file_gen(name, lim, size);*/
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
	file_splitting(name1, name2, name3, name4);
	//trade(name1, name3);
	//trade(name2, name4);
	//file_splitting(name1, name2, name3, name4);
	//trade(name1, name3);
	//trade(name2, name4);
	//file_splitting(name1, name2, name3, name4);
}
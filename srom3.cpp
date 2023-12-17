#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <functional>
#include <cmath>
using namespace std;

class LibrFunc
{
public:
	int m = 281;
	string px = "281 9 4 1 0";
	string a;
	string b;
	string n;
	string p;
	string null;
	string one;

	LibrFunc(string s1, string s2, string s3);

	string Input();

	string Switch(string s);

	void Print(string s);

	string Add(string a, string b);

	string Mod(string a);

	string Mul(string a, string b);

	string Square(string a);

	int Trace(string a);

	string Pow(string a, string b);

	string Inverse(string a);
};

LibrFunc::LibrFunc(string s1, string s2, string s3)
{
	p = Input();
	a = Switch(s1);
	b = Switch(s2);
	n = Switch(s3);
	null = "0";
	one = "1";
	for (int i = 1; i < m; i++)
	{
		null = null + "0";
		one = one + "0";
	}
};

string LibrFunc::Input()
{
	istringstream iss(px);
	vector<int> numbers;
	int num, ind = 0;
	while (iss >> num) {
		numbers.push_back(num);
	}
	string p = "";
	for (int i = numbers[0]; i >= 0; i--)
	{
		if (numbers[ind] == i)
		{
			p = p + "1";
			ind++;
		}
		else p = p + "0";
	}
	reverse(p.begin(), p.end());
	return p;
};

string LibrFunc::Switch(string s)
{
	reverse(s.begin(), s.end());
	return s;
};

void LibrFunc::Print(string s)
{
	reverse(s.begin(), s.end());
	cout << s << endl;
};

string LibrFunc::Add(string a, string b)
{
	string c = "";
	while (a.length() < b.length()) {
		a = a + "0";
	}
	while (a.length() > b.length()) {
		b = b + "0";
	}
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == b[i]) c = c + "0";
		else c = c + "1";
	}
	if (c.length() > m) c = Mod(c);
	return c;
};

string LibrFunc::Mod(string a)
{
	while (!a.empty() && a.back() == '0') {
		a.pop_back();
	}
	int a_len = a.length();
	int p_len = p.length();
	string temp;
	while (a_len >= p_len)
	{
		temp = p;
		while (a_len > temp.length()) {
			temp = "0" + temp;
		}
		a = Add(a, temp);
		while (!a.empty() && a.back() == '0') {
			a.pop_back();
		}
		a_len = a.length();
	}
	while (a.length() < m) {
		a = a + "0";
	}
	return a;
};

string LibrFunc::Mul(string a, string b)
{
	string c = "";
	string temp = b;
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == '1') c = Add(c, temp);
		temp = "0" + temp;
	}
	return c;
};

string LibrFunc::Square(string a)
{
	int size = 2 * (a.length() - 1);
	for (int i = 1; i < size; i += 2)
	{
		a = a.insert(i, "0");
	}
	a = Mod(a);
	return a;
};

int LibrFunc::Trace(string a)
{
	string str, temp;
	int T = 0;
	if (a[0] == '1') T++;
	for (int i = 1; i < m; i++)
	{
		if (a[i] == '1')
		{
			str[0] = '1';
			temp = str;
			for (int j = 1; j < m; j++)
			{
				temp = Square(temp);
				str = Add(str, temp);
			}
			if (str[0] == '1') T = (T + 1) & 1;
		}
	}
	return T;
};

string LibrFunc::Pow(string a, string b)
{
	string c = one;
	for (int i = m - 1; i >= 0; i--)
	{
		if (b[i] == '1') c = Mul(c, a);
		if (i != 0) c = Square(c);
	}
	return c;
};

string LibrFunc::Inverse(string a)
{
	string temp = a;
	for (int i = 1; i < m - 1; i++)
	{
		temp = Square(temp);
		a = Mul(a, temp);
	}
	a = Square(a);
	return a;
}

double MeasureTime(function<void()> operation) {
	auto start_time = chrono::high_resolution_clock::now();

	operation();

	auto end_time = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed_time = end_time - start_time;

	return elapsed_time.count();
}

int main()
{
	string s1, s2, s3, str;

	s1 = "10010001011000001110000010100010000111100010100010010101010110000100000100001111100101111101001001000111100001011111111011101001000010010010110011110011001111001111001101111001000111011010100110011100010100101101011101010100011110100011101011000111001101011110011110100001001101001";
	s2 = "10110101011010001011001010010010111010111100000000011011101010110111010001010011001101101000011111100010101100110101110000111110101101110110110010000111011010001111011011011011010010110010010101111001010110000000011001000011010001101001001000001110010011111101100100010100011101110";
	s3 = "11110001000101111100100110010111110000001001011110010010000111011011101101000110101100010010111011000010111111111011001110101000001100001000000101110110101110101011110100010000100110100100001111101100110001011110100010001110011101010101010101111111100000010000111100011010101100001";

	LibrFunc A(s1, s2, s3);

	double time_add = MeasureTime([&]() {
		cout << "\nA+B: ";
		A.Print(A.Add(A.a, A.b));
		});
	cout << "Time taken for addition: " << time_add << " seconds" << endl;

	double time_mul = MeasureTime([&]() {
		cout << "\nA*B: ";
		A.Print(A.Mul(A.a, A.b));
		});
	cout << "Time taken for multiplication: " << time_mul << " seconds" << endl;

	double time_trace = MeasureTime([&]() {
		cout << "\nTrace(A): ";
		cout << A.Trace(A.a) << endl;
		});
	cout << "Time taken to calculate the trace: " << time_trace << " seconds" << endl;

	double time_square = MeasureTime([&]() {
		cout << "\nA^2: ";
		A.Print(A.Square(A.a));
		});
	cout << "Time taken to calculate the square: " << time_square << " seconds" << endl;
	/*
	double time_power = MeasureTime([&]() {
		cout << "\nA^n: ";
		A.Print(A.Pow(A.a, A.n));
		});
	cout << "Time taken for exponentiation: " << time_power << " seconds" << endl;
	*/
	double time_inv = MeasureTime([&]() {
		cout << "\nA^(-1): ";
		A.Print(A.Inverse(A.a));
		});
	cout << "Time taken to calculate the inverse: " << time_inv << " seconds" << endl;

	cout << "\n(a + b) * c = a * c + b * c: ";
	string w = A.Mul(A.Add(A.a, A.b), A.n);
	string u = A.Add(A.Mul(A.a, A.n), A.Mul(A.b, A.n));

	if (u.compare(w) == 0) {
		cout << "True" << endl;
	}
	else {
		cout << "False" << endl;
	}

	cout << "\n a^(2^m - 1):";
	string h = A.null;
	replace(h.begin(), h.end(), '0', '1');
	A.Print(A.Pow(A.a, A.Switch(h)));
	if ((A.one).compare(A.Pow(A.a, A.Switch(h))) == 0) {
		cout << "True" << endl;
	}
	else {
		cout << "False" << endl;
	}
}

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace  std;
//Считывание алфавита
string ReadFileSequence(string path) {
	string stringMain;
	ifstream f;
	char c;
	f.open("input1.txt");
	if (f) {
		while (true){
			f >> c;
			if (f.eof()) break;
			stringMain.push_back(c);

		}
	}
	else
		cout << "Не удалось открыть файл";
	f.close();
	return stringMain;
}

//Считывание вероятности
vector<double> ReadFileProbability(string path) {
	vector<double> v;
	double d;
	ifstream f;
	f.open(path);
	if (f.is_open()) {
		while (!f.eof()) {
			f >> d;
			v.push_back(d);
		}
	}
	else
		cout << "Не удалось открыть файл";
	f.close();
	return v;
}

//Перевод дроби в двоичную систему счисления
vector<int> translate_float(double elem,vector<int> C) {
	int i = 0;
	int o = 2;
	double f = elem;
	bool flag = true;
	float c = 0;
	elem = f * o;
	f = modf(elem, &elem);
	C[i] = elem;
	i++;
	if (f > 0) {
		elem = f * o;
		f = modf(elem, &elem);
		C[i] = elem;
		i++;
		while (f > 0 && i < 6) {
			elem = f * o;
			f = modf(elem, &elem);
			C[i] = elem;
			i++;

		}
	}
	return C;
}

//Неравенство Крафта
double Craft(vector<int> l) {
	double sum = 0;
	for (int i = 0; i < l.size(); i++) {
		sum += pow(2, -l[i]);
	}
	return sum;
}

//Вычисление средней длины кодового слова
double MiddleCodeLength(vector<int> l, vector<double> v) {
	double sum = 0;
	for (int i = 0; i < l.size(); i++)
		sum += v[i] * l[i];
	return sum;
}

//Энтропия
double entropy(vector<double>v) {
	double sum = 0;
	for (int i = 0; i < v.size(); i++) {
		sum += v[i] * (log(v[i]) / log(2));
	}
	return -sum;
}

//Код Гильберта-Мура
vector<vector<int>> GilbertMoore(string alph,vector<double> v) {
	int size_alph = alph.size();
	vector<double> q(size_alph);
	vector<int> l(size_alph);
	vector<int>C(32);
	vector<vector<int>> code(size_alph);
	double pr = 0;
	double sr = 0;
	if (alph.size() != v.size()) {
		cout << "Не всем буквам алфавита записана вероятность появления";
		return code;
	}
	else {
		for (int i = 0; i < size_alph; i++) {
			q[i] = pr + v[i] / 2;
			pr = pr + v[i];
			l[i] = -(log(v[i]) / log(2)) + 1;
		}
			for (int i = 0; i <size_alph; i++) {
				C=translate_float(q[i],C);
				for (int j = 0; j < l[i]; j++) {
					code[i].push_back(C[j]);
				}
		}

	}
	for (int i = 0; i < code.size(); i++) {
		cout << alph[i]<<" ";
		for (int j = 0; j < code[i].size(); j++) {
			cout << code[i][j];
		}
		cout << endl;
	}
	pr = 0;
	pr=Craft(l);
	if (pr <= 1) {
		cout << "Неравенство Крафта выполняется " << pr << endl;
	}
	else {
		cout << "Неравенство Крафта не выполняется " << pr << endl;
	}
	pr = entropy(v);
	sr = MiddleCodeLength(l,v);
	cout << "Средняя длина кодового слова " << sr << endl;
	cout<<"Избыточность "<<sr-pr;
	return code;
}

//Поиск кода символа
vector<int> SearchCodeSymbol(char c, string alph, vector<vector<int>> v) {
	for (int i = 0; i < alph.size(); i++) {
		if (c == alph[i]) {
			return v[i];
		}
	}
	return { -1 };
}

//Кодирование последовательности
int Codding(string aphl, vector<vector<int>> v, string path){
	ifstream f;
	ofstream f1;
	char c;
	vector<int> code(32);
	f1.open("output.txt");
	f.open(path);
	if (!f.is_open()) {
		return 0;
	}
	else {
		while (true) {
			f >> c;
			if (f.eof()) break;
			code = SearchCodeSymbol(c, aphl, v);
			if (code[0] == -1) {
				return -1;
			}
			else {
				for (int i = 0; i < code.size(); i++)
					f1 << code[i];
			}
			//f1 << ' ';
		}
	}
	return 1;
}

//Поиск символа по коду
string SearchSymboleCode(string aphl,vector<vector<int>> v,string inputV) {
	int k = 0;
	string result;
	bool flag = true;
	bool flag_string = true;
	vector<int> a;
	while (flag) {
		if (inputV[k] == 48)
			a.push_back(0);
		else
			a.push_back(1);
		k++;
		for (int i = 0; i < v.size(); i++) {
			if (a.size() == v[i].size()) {
				for (int j = 0; j < v[i].size(); j++) {
					if (a[j] != v[i][j])
						flag_string = false;
				}

				if (flag_string == true) {
					a.clear();
					result.push_back(aphl[i]);
				}
				flag_string = true;

			}
		}
		if (k == inputV.size())
			flag = false;
	}
	return result;
}

//Декодирование последовательности
int Decodding(string aphl, vector<vector<int>> v, string path) {
	int help;
	string pox;
	string c;
	vector<int> inputV;
	ifstream f(path, std::ios::in);
	ofstream f1("outputS.txt", std::ios::in);
	if (f.is_open()) {
		f >> pox;
		c=SearchSymboleCode(aphl,v,pox);
		if (c.size() != 0) {
			f1 << c;
			return 1;
		}
	}
	else
		return 0;
}
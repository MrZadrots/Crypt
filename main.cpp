#include "Header.h"

void main() {
	setlocale(LC_CTYPE, "Russian");
	bool t = true;
	string stringMain;
	string path;
	vector<double> v;
	vector<vector<int>> G_M_code(stringMain.size());
	int c = 1;
	int flag=0;
	cout << "Введите путь к файлу с алфавитом: ";
	cin >> path;
	stringMain = ReadFileSequence(path);
	cout << "Введите путь к файлу с вероятностями: ";
	cin >> path;
	v = ReadFileProbability(path);
	G_M_code=GilbertMoore(stringMain, v);
	while (t) {
		cout << endl;
		cout << "Выберите из меню:" << endl;
		cout << "1.Закодировать последовательность" << endl;
		cout << "2.Декодироватать последовательность" << endl;
		cout << "3.Изменить алфавит" << endl;
		cout << "4.Изменить вероятности для текущего алфавита" << endl;
		cout << "0.Выход" << endl;
		cin >> c;
		switch (c)
		{
		case 1:
			cout << "Введите путь к файлу с последовательностью: ";
			cin >> path;
			flag = Codding(stringMain, G_M_code, path);
			if (flag == 1)
				cout << "Успешно! Результат записан в файл output.txt";
			else if (flag == 0)
				cout << "Не удалось открыть файл";
			else
				cout << "В последовательности есть символы, не входящие в алфавит.";
			break;
		case 2:
			cout << "Введите путь к файлу с последовательностью: ";
			cin >> path;
			flag = Decodding(stringMain, G_M_code, path);
			if (flag == 1)
				cout << "Успешно! Результат записан в файл outputS.txt";
			else
				cout << "Неудалось недокодировать последовательность!";
			break;
		case 3:
			cout << "Введите путь к файлу с алфавитом: ";
			cin >> path;
			stringMain = ReadFileSequence(path);
			cout << "Введите путь к файлу с вероятностями: ";
			cin >> path;
			v = ReadFileProbability(path);
			G_M_code = GilbertMoore(stringMain, v);
		case 4:
			cout << "Введите путь к файлу с вероятностями: ";
			cin >> path;
			v = ReadFileProbability(path);
			G_M_code = GilbertMoore(stringMain, v);
		case 0:
			t = false;
			break;
		default:
			break;
		}
	}
}
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
	cout << "������� ���� � ����� � ���������: ";
	cin >> path;
	stringMain = ReadFileSequence(path);
	cout << "������� ���� � ����� � �������������: ";
	cin >> path;
	v = ReadFileProbability(path);
	G_M_code=GilbertMoore(stringMain, v);
	while (t) {
		cout << endl;
		cout << "�������� �� ����:" << endl;
		cout << "1.������������ ������������������" << endl;
		cout << "2.�������������� ������������������" << endl;
		cout << "3.�������� �������" << endl;
		cout << "4.�������� ����������� ��� �������� ��������" << endl;
		cout << "0.�����" << endl;
		cin >> c;
		switch (c)
		{
		case 1:
			cout << "������� ���� � ����� � �������������������: ";
			cin >> path;
			flag = Codding(stringMain, G_M_code, path);
			if (flag == 1)
				cout << "�������! ��������� ������� � ���� output.txt";
			else if (flag == 0)
				cout << "�� ������� ������� ����";
			else
				cout << "� ������������������ ���� �������, �� �������� � �������.";
			break;
		case 2:
			cout << "������� ���� � ����� � �������������������: ";
			cin >> path;
			flag = Decodding(stringMain, G_M_code, path);
			if (flag == 1)
				cout << "�������! ��������� ������� � ���� outputS.txt";
			else
				cout << "��������� �������������� ������������������!";
			break;
		case 3:
			cout << "������� ���� � ����� � ���������: ";
			cin >> path;
			stringMain = ReadFileSequence(path);
			cout << "������� ���� � ����� � �������������: ";
			cin >> path;
			v = ReadFileProbability(path);
			G_M_code = GilbertMoore(stringMain, v);
		case 4:
			cout << "������� ���� � ����� � �������������: ";
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
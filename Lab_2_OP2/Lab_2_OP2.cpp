#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <filesystem>
//#include <vector>

using namespace std;

void input_data();


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	input_data();


	//delete "database.csv"
	return 0;
}

void input_data()
{
	namespace fs = filesystem;
	string dir;
	string extension = ".csv";
	int group_num;

	cout << "enter files directory:" << endl;
	cin >> dir;

	for (auto& p : fs::directory_iterator(dir)) // ��� ���� ������ � �����
	{
		if (!fs::is_regular_file(p.status()))	// ����������, ���� ��� �� ������� ����, � ����� ��� ���-�� ������
			continue;

		if (p.path().extension().string() == extension) // �������� ����� � ����������� .csv
		{
			ifstream inf(p.path());

			if (!inf.is_open())							// ��������� ������������ ������ ������
			{
				cerr << "some troubles with file" << endl;
				exit(1);
			}
			inf >> group_num;

			string student;
			string str;
			for (int i = 0; i < group_num; i++)
			{
				getline(inf, student, ',');
				float mark = 0;
				for (int j = 0; j < 5; j++)
				{
					getline(inf, str, ',');
					mark = mark + stoi(str);
				}
				mark = mark / 5;
				getline(inf, str);
				if (str == "FALSE")
				{
					ofstream outf("database.csv", ios::app);

					if (!outf)									// ���� ���� �� ������
					{
						cerr << "ofstream trouble" << endl;
						exit(1);
					}
					outf << student << "," << fixed << setprecision(3) << mark << endl;
				}

			}

		}

	}

}
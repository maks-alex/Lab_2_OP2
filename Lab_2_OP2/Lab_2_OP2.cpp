#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>						//for method SetConsoleCP
#include <filesystem>
//#include <vector>

using namespace std;

void input_data(int&, int&, float&);
void processing();
//void input_data(string*, float*, bool*);
//int output_data(int ,string*, float*, bool*);
//void sorting(string* name, float* rating, bool* result, int sum);
//void output_data(string* name, float* rating, bool* result, int number_of_students);


class Stud
{
public:
	Stud()
	{
		Budg = "";
		Rating = 0;										//�� ������ ����� ��������� string , � ��� ����� float
	}
	Stud(string name, float averrate)
	{
		this->Budg = name;
		this->Rating = averrate;						//�� ������ ����� ��������� string , � ��� ����� float
	}
	string Budg;
	float Rating;
};
ostream& operator<<(ostream& fout, const Stud& stud)	//�� ���������� � ����
{
	fout << stud.Budg << "," << stud.Rating << endl;
	return fout;
}
istream& operator>>(istream& fin, Stud& stud)			//�� ����� � ����������
{
	fin >> stud.Budg >> stud.Rating;						//����� ����� �� ����� while (!inf1.eof()) cin >> s;
	return fin;
}



int main()
{
	//	SetConsoleCP(1251);
	//	SetConsoleOutputCP(1251);

	int count,										//����� ��������� � �������
		count_total;								//����� ��������� � �������
	float	average;								//����� ��������� � �������

	input_data(count, count_total, average);
	//	cout << "count_total:" << count_total << "    count:" << count << "    average:" << average;

	Stud stud("Ivan", 88.6);
	cout << stud;

	processing();


	//delete "database.csv"
	return 0;
}


void processing()
{
	vector<Stud> Group;


	ifstream inf1;						//�� ����� � ����������
	inf1.open("database.csv");
	if (!inf1.is_open())
	{
		cerr << "some troubles with file" << endl;
		exit(1);
	}
	Stud s;
	while (!inf1.eof())						//��-�� �������� break ����� ��������� true
	{
		inf1 >> s;
		if (inf1.eof())						//�������� ��� ������������ ��������� ������ �������
		{
			break;
		}
		cout << s << endl;

		//		getline(inf1, str, ',');
		//		s.Budg = str;
		//		getline(inf1, str, ',');
		//		s.Rating = stoi(str);

		//		inf1 >> s;							//�� ����� � ����������

					//Group.push_back(stud);
	}										//����� ���������� ���������� ���� �� ������ ���������� �����
	cout << "hello world";
	inf1.close();
}

/*

	ofstream outf1;					//�� ���������� � ����
	outf1.open("rating.csv");
	if (!outf1.is_open())
	{
		cerr << "some troubles with file" << endl;
		exit(1);
	}
									//������� ������ �� �������
	outf1 << s << endl;				//�� ���������� � ���� (endl ��� "\n"?)
	outf1.close();
}
*/
void input_data(int& count, int& count_total, float& average)
{
	namespace fs = filesystem;
	string dir;
	string extension = ".csv";
	int group_num;
	count = 0;
	average = 0;
	count_total = 0;
	cout << "enter files directory:" << endl;
	cin >> dir;

	for (auto& p : fs::directory_iterator(dir)) // ��� ���� ������ � �����
	{
		if (!fs::is_regular_file(p.status()))	// ����������, ���� ��� �� ������� ����, � ����� ��� ���-�� ������
			continue;

		if (p.path().extension().string() == extension) // �������� ����� � ����������� .csv
		{
			ifstream inf;
			inf.open((p.path()));
			if (!inf.is_open())							// ��������� ������������ ������ ������
			{
				cerr << "some troubles with file" << endl;
				exit(1);
			}
			inf >> group_num;

			string student;
			string str;
			//			while (!inf.eof());
			for (int i = 0; i < group_num; i++)			//����� while (!inf.eof()), �� ������-�� �� ����������
			{
				SetConsoleCP(1251);
				getline(inf, student, ',');
				float mark = 0;
				for (int j = 0; j < 5; j++)
				{
					getline(inf, str, ',');
					mark = mark + stoi(str);
				}
				mark = mark / 5;
				average = +mark;
				count_total++;
				getline(inf, str);
				if (str == "FALSE")
				{
					ofstream outf;
					outf.open("database.csv", ofstream::app);

					if (!outf.is_open())									// ���� ���� �� ������
					{
						cerr << "ofstream trouble" << endl;
						exit(1);
					}
					outf << student << " " << fixed << setprecision(3) << mark << endl;
					count++;
					outf.close();
				}
				SetConsoleCP(866);

			}
			inf.close();

		}

	}

}
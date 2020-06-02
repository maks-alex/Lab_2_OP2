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
		Rating = 0;										//из потока будет выводится string , а мне нужно float
	}
	Stud(string name, float averrate)
	{
		this->Budg = name;
		this->Rating = averrate;						//из потока будет выводится string , а мне нужно float
	}
	string Budg;
	float Rating;
};
ostream& operator<<(ostream& fout, const Stud& stud)	//из переменной в файл
{
	fout << stud.Budg << "," << stud.Rating << endl;
	return fout;
}
istream& operator>>(istream& fin, Stud& stud)			//из файла в переменную
{
	fin >> stud.Budg >> stud.Rating;						//завис здесь из цикла while (!inf1.eof()) cin >> s;
	return fin;
}



int main()
{
	//	SetConsoleCP(1251);
	//	SetConsoleOutputCP(1251);

	int count,										//потом поубирать в функцию
		count_total;								//потом поубирать в функцию
	float	average;								//потом поубирать в функцию

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


	ifstream inf1;						//из файла в переменную
	inf1.open("database.csv");
	if (!inf1.is_open())
	{
		cerr << "some troubles with file" << endl;
		exit(1);
	}
	Stud s;
	while (!inf1.eof())						//из-за проверки break можно поставить true
	{
		inf1 >> s;
		if (inf1.eof())						//проверка для несчитывания последней пустой строчки
		{
			break;
		}
		cout << s << endl;

		//		getline(inf1, str, ',');
		//		s.Budg = str;
		//		getline(inf1, str, ',');
		//		s.Rating = stoi(str);

		//		inf1 >> s;							//из файла в переменную

					//Group.push_back(stud);
	}										//здесь получается бесконечній цикл на первую переменную файла
	cout << "hello world";
	inf1.close();
}

/*

	ofstream outf1;					//из переменной в файл
	outf1.open("rating.csv");
	if (!outf1.is_open())
	{
		cerr << "some troubles with file" << endl;
		exit(1);
	}
									//достать данные из вектора
	outf1 << s << endl;				//из переменной в файл (endl или "\n"?)
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

	for (auto& p : fs::directory_iterator(dir)) // Для всех файлов в папке
	{
		if (!fs::is_regular_file(p.status()))	// Пропускаем, если это не простой файл, а папка или что-то другое
			continue;

		if (p.path().extension().string() == extension) // Выбираем файлы с расширением .csv
		{
			ifstream inf;
			inf.open((p.path()));
			if (!inf.is_open())							// Проверяем корректность работы потока
			{
				cerr << "some troubles with file" << endl;
				exit(1);
			}
			inf >> group_num;

			string student;
			string str;
			//			while (!inf.eof());
			for (int i = 0; i < group_num; i++)			//можно while (!inf.eof()), но почему-то не заработало
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

					if (!outf.is_open())									// Если файл не открыт
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
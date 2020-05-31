#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <filesystem>

using namespace std;

void extracting_list_of_students();



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	extracting_list_of_students();
	return 0;
}

void extracting_list_of_students()
{

	namespace fs = filesystem;
	string dir;
	string extension = ".csv";
	int group_num,
		stud_num = 0;

	cout << "enter files directory:" << endl;
	cin >> dir;

	for (auto& p : fs::directory_iterator(dir)) // Для всех файлов в папке
	{
		if (!fs::is_regular_file(p.status()))	// Пропускаем, если это не простой файл, а папка или что-то другое
			continue;

		if (p.path().extension().string() == extension) // Выбираем файлы с расширением .csv
		{
			ifstream inf(p.path());

			if (!inf.is_open())							// Проверяемость корректность работы потока
			{
				cerr << "some troubles with file" << endl;
				exit(1);
			}
			inf >> group_num;
			stud_num = stud_num + static_cast<int>(group_num);

			inf.seekg(4);
			while (inf)
			{

														// То перемещаем эти данные в строку, которую затем выводим на экран
				string strInput;
				getline(inf, strInput);
				cout << strInput << endl;
			}

		}

	}

}
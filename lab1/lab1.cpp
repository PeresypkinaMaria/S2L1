/*1A. Прибавить к каждому числу корень квадратный из произведения максимума и последнего числа.*/

#include "stdafx.h"

#include <vector>
#include <fstream>
#include <math.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;

//заполнение текстового файла рандомными числами
fstream RndFileFilling(string FileName, int N, int M)
{
	fstream file(FileName, ios::out);
	if (!file.is_open())
	{
		throw "Не удалось открыть файл";
	}

	if (N < 1)
	{
		throw "Количество элементов должно быть положительным";
	}

	if (M < 1)
	{
		throw "Число М должно быть положительным";
	}

	for (int i = 0; i < N; ++i)
	{
		int r = rand() % (2 * M + 1) - M;
		file << r << " ";
	}
	file.close();
	return file;
}

//заполнение текстового файла рандомными числами с использованием алгоритма std::generate
fstream RndFileGenerate(string FileName, int N, int M)
{
	fstream file(FileName, ios::out);
	if (!file.is_open())
	{
		throw "Не удалось открыть файл";
	}

	if (N < 1)
	{
		throw "Количество элементов должно быть положительным";
	}

	if (M < 1)
	{
		throw "Число М должно быть положительным";
	}

	vector<int> vect = vector<int>(N);
	generate(vect.begin(), vect.end(), rand);
	vector<int>::iterator iter = vect.begin();
	while (iter != vect.end())
	{
		file << ' ' << (*iter % (M * 2) + 1) - M;
		++iter;
	}
	return file;
}

//формирование контейнера на основе файла
vector<double> VectorFromFile(fstream &file)
{
	vector<double> vect;

	int a;

	while (!file.eof())
	{
		if ((file >> a))
		{
			vect.push_back(a);
		}
	}
	return vect;
}

//прибавить к каждому числу корень квадратный из произведения максимума и последнего числа
vector<double> Modify(vector<double> &vect)
{
	if (vect.empty())
		return vect;
	vector<double> vect1;
	vector<double>::iterator max;
	max = max_element(vect.begin(), vect.end());
	double ch = sqrt(abs(*max * vect.back()));
	for (auto iter = vect.begin(); iter != vect.end(); iter++)
	{
		*iter += ch;
		vect1.push_back(*iter);
	}
	return vect1;
}

//преобразование части контейнера
void Modify(vector<double> &vect, vector<double>::iterator head, vector<double>::iterator last)
{
	vector<double>::iterator iter = head;
	vector<double>::iterator max = max_element(head, last);
	double ch = sqrt(abs(*max * *last));
	for (auto iter = vect.begin(); iter != vect.end(); iter++)
		*iter += ch;
}

double Change(vector<double> vect)
{
	double max = *vect.begin();
	double last = vect.back();
	for_each(vect.begin(), vect.end(), [&max](double i) {if (i > max) max = i; });
	return  sqrt(abs(max * last));
}

//преобразование с помощью алгоритма transform
vector<double> TransformVector(vector<double> vect)
{
	double ch = Change(vect);
	transform(vect.begin(), vect.end(), vect.begin(), [&ch](double &i) { return i = i + ch; });
	return vect;
}

//преобразование с помощщью алгоритма for_each
vector<double> for_each_Vector(vector<double> vect)
{
	vector<double> v2;
	for_each(vect.begin(), vect.end(), [&vect, &v2](double &i) { v2.push_back(i + Change(vect)); });
	return v2;
}

//сумма всех чисел в контейнере
double SumInVector(vector<double> &vect)
{
	double s = 0;
	if (vect.empty())
	{
		throw "Невозможно вычислить сумму: контейнер пуст";
	}
	else
	{
		vector<double>::iterator iter = vect.begin();
		while (iter != vect.end())
		{
			s += *iter;
			++iter;
		}
	}
	return s;
}

//среднее арифметическое всех чисел контейнера
double AverageInVector(vector<double> &vect)
{
	double av = 0.0;
	if (vect.empty())
	{
		throw "Невозможно вычислить среднее арифметическое: контейнер пуст";
	}
	else
	{
		vector<double>::iterator iter = vect.begin();
		while (iter != vect.end())
		{
			av += *iter;
			++iter;
		}
		av /= (double)vect.size();
	}
	return av;
}

//вывод всех элементов контейнера в файл
void PrintToFile(string FileName, vector<double> &vect)
{
	fstream file;
	file.open(FileName, ios::out);
	if (!file.is_open())
	{
		throw "Не удалось открыть файл!";
	}
	else
	{
		if (vect.empty())
		{
			file << "Контейнер пуст" << endl;
		}
		else
		{
			vector<double>::iterator iter = vect.begin();
			while (iter != vect.end())
			{
				file << *iter << ' ';
				++iter;
			}
			file << endl;
		}
	}
}

//вывод всех элементов контейнера на экран
void PrintVector(vector<double> &vect)
{
	if (vect.empty())
	{
		throw "Контейнер пуст";
	}
	else
	{
		vector<double>::iterator iter = vect.begin();
		while (iter != vect.end())
		{
			cout << *iter << ' ';
			++iter;
		}
		cout << endl;
	}
}

//получение итератора по числу
vector<double>::iterator getIter(vector<double> &vect, int n)
{
	if ((n < 1) || (n > vect.size() + 1))
	{
		throw "Невозможно найти элемент с данным номером";
	}
	vector<double>::iterator iter = vect.begin();
	int i = 1;
	while (i < n)
	{
		++iter;
		++i;
	}
	return iter;
}

//печать меню
void PrintMenu()
{
	cout << "Введите номер необходимого действия:" << endl;
	cout << "1 - заполнить файл случайными числами с помощью цикла" << endl;
	cout << "2 - заполнить файл случайными числами с помощью алгоритма generate" << endl;
	cout << "3 - сформировать контейнер на основе файла" << endl;
	cout << "4 - преобразовать контейнер" << endl;
	cout << "5 - преобразовать часть контейнера" << endl;
	cout << "6 - преобразовать контейнер с помощью алгоритма transform" << endl;
	cout << "7 - преобразовать контейнер с помощью алгоритма for_each" << endl;
	cout << "8 - вычислить сумму всех элементов контейнера" << endl;
	cout << "9 - вычислить среднее арифметическое всех элементов контейнера" << endl;
	cout << "10 - вывести все элементы контейнера в файл" << endl;
	cout << "11 - вывести все элементы контейнера на экран" << endl;
	cout << "0 - завершить работу программы" << endl;
	cout << endl;
}

string fname;
fstream file;
vector<double> vect;
vector<double>::iterator head, last;
int N, M;

//меню
void Menu(int key)
{
	switch (key)
	{
	case 1:
		cout << "Введите имя файла" << endl;
		cin.clear();
		cin >> fname;
		cout << "Введите количество случайных чисел" << endl;
		while (!(cin >> N))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Введите число" << endl;
		}
		cout << "Введите границу диапазона случайных чисел (-M; M)" << endl;
		while (!(cin >> M))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Введите число" << endl;
		}
		try
		{
			file = RndFileFilling(fname, N, M);
			file.close();
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		cout << endl;
		break;

	case 2:
		cout << "Введите имя файла" << endl;
		cin.clear();
		cin >> fname;
		cout << "Введите количество случайных чисел" << endl;
		while (!(cin >> N))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Введите число" << endl;
		}
		cout << "Введите границу диапазона случайных чисел (-M; M)" << endl;
		while (!(cin >> M))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Введите число" << endl;
		}
		try
		{
			file = RndFileGenerate(fname, N, M);
			file.close();
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		cout << endl;
		break;

	case 3:
		cout << "Введите имя файла, из которого будет считана последовательность" << endl;
		cin >> fname;
		file.open(fname);
		if (!file.is_open())
		{
			throw "Не удалось открыть файл";
		}
		try
		{
			vect = VectorFromFile(file);
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		cout << endl;
		break;

	case 4:
		try
		{
			if (vect.empty())
				cout << "Контейнер пуст" << endl;
			else
				vect = Modify(vect);
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		cout << endl;
		break;

	case 5:
		cout << "Введите нижнюю из границ, в пределах которых будет преобразование" << endl;
		while (!(cin >> N))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Введите число" << endl;
		}
		cout << "Введите верхнюю из границ, в пределах которых будет преобразование" << endl;
		while (!(cin >> M))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Введите число" << endl;
		}
		while ((N <= 0) || (M <= 0) || (N > (int)(vect.size() + 1)) || (M > (int)(vect.size() + 1)))
		{
			cout << "Неверно введены номера(допустимы значения от 1 до " << vect.size() + 1 << "). Повторите ввод!" << endl;
			try
			{
				cout << "Введите нижнюю из границ, в пределах которых будет преобразование" << endl;
				while (!(cin >> N))
				{
					cin.clear();
					while (cin.get() != '\n');
					cout << "Введите число" << endl;
				}
				cout << "Введите верхнюю из границ, в пределах которых будет преобразование" << endl;
				while (!(cin >> M))
				{
					cin.clear();
					while (cin.get() != '\n');
					cout << "Введите число" << endl;
				}
			}
			catch (char *s)
			{
				cout << s << endl;
			}
		}

		try
		{
			head = getIter(vect, N);
			last = getIter(vect, M);
			Modify(vect, head, last);
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		cout << endl;
		break;

	case 6:
		try
		{
			vect = TransformVector(vect);
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		cout << endl;
		break;

	case 7:
		try
		{
			vect = for_each_Vector(vect);
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		cout << endl;
		break;

	case 8:
		try
		{
			cout << "Сумма всех чисел контейнера равна " << SumInVector(vect) << endl;
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		cout << endl;
		break;

	case 9:
		try
		{
			cout << "Среднее арифметическое всех элементов контейнера равно " << AverageInVector(vect) << endl;
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		cout << endl;
		break;

	case 10:
		cout << "Введите имя файла" << endl;
		cin.clear();
		cin >> fname;
		try
		{
			PrintToFile(fname, vect);
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		cout << endl;
		break;

	case 11:
		try
		{
			PrintVector(vect);
		}
		catch (char *s)
		{
			std::cout << s << std::endl;
		}
		cout << endl;
		break;

	case 0:
		break;

	default:
		cout << "Такой команды не существует! Повторите ввод" << endl;
		break;
	}
}

int main()
{
	//автоматическая рандомизация
	srand((unsigned int)(time(0)));

	setlocale(LC_ALL, "Russian");

	int key;
	do
	{
		PrintMenu();
		while (!(cin >> key))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Команда вводится в форме числа" << endl;
		}
		Menu(key);
	} while (key != 0);
	return 0;
}



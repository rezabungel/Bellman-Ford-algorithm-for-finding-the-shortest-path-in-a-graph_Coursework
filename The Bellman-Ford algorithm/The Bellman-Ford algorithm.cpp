// The Bellman-Ford algorithm.cpp
// Bellman-Ford algorithm for finding the shortest path in a graph | Алгоритм Беллмана-Форда для поиска кратчайшего пути в графе
// Курсовая работа за 3 семестр по методам программирования

#include <iostream>
#include <string>
#include <fstream> //библиотека для работы с файлами.
#include "Bellman_Ford.h"
#include "Timer.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	//Взятие матрицы из файла

	//Работа с графом

	//Вывод результата в файл и консоль.

	/*!Различные тесты!*/

	string namefile = "Weighted graph.txt";  //Переменная, хранящая путь до файла.
	Bellman_Ford Filetest(namefile);
	Filetest.print_Matrix();

	/*Timer t;
	Bellman_Ford AAA(10);
	AAA.print_Matrix();
	cout << t.elapsed();*/

	//vector<int> test = AAA.get_row(10);
	//for (int i = 0; i < 10; i++)
	//{
	//	cout << test[i] << "\t";
	//}

	//vector<int> test1 = AAA.get_column(10);
	//for (int i = 0; i < 10; i++)
	//{
	//	cout << test1[i] << "\t";
	//}

	//test.pop_back();
	//test.push_back(12);

	//cout << endl;
	//AAA.set_row(1, test);
	//AAA.print();

	//cout << endl << endl << endl;

	//test1.pop_back();
	//test1.push_back(12);

	//AAA.set_column(1, test1);
	//AAA.print_Matrix();

	//vector<vector<int>> Matrix1;
	//int size_Matrix1 = 5;
	//for (int i = 0; i < size_Matrix1; i++)
	//{
	//	vector<int> temp;//Времменный вектор, который необходим для заполнения матрицы смежности.
	//	for (int j = 0; j < size_Matrix1; j++)
	//	{
	//		temp.push_back(rand() % 100 - 5);
	//	}
	//	Matrix1.push_back(temp);
	//}
	//Bellman_Ford qwe(Matrix1);
	//qwe.print_Matrix();

	////Для рассчета времени.
	// Timer t; 
	//cout << t.elapsed();
	//t.reset();
	return 0;
}
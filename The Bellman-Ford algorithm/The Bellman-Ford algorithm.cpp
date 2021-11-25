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
	Bellman_Ford mat(namefile);
	mat.print_Matrix();
	mat.Algoritm_Bellman_Ford();
	//mat.print_Result();
	//mat.print_Result();






	//bool a = mat.get_Negative_cycle();



	vector<vector<int>> qqq;
	qqq = mat.get_Matrix();
	//Timer t;
	//qqq= mat.Algoritm_Bellman_Ford();
	//cout << t.elapsed(); 
	//cout << "-------------------------------------------Result Matrix-------------------------------------------" << endl;
	//for (int i = 0; i < qqq.size(); i++)
	//{
	//	for (int j = 0; j < qqq[i].size(); j++)
	//	{
	//		cout << qqq[i][j] << "\t";
	//	}
	//	cout << endl;
	//}
	cout << "---------------------------------------------------------------------------------------------------" << endl;



	/*Timer t;
	Bellman_Ford AAA(10);
	AAA.print_Matrix();
	cout << t.elapsed();*/

	//	vector<int> test = mat.get_row(4);
		//for (int i = 0; i < 4; i++)
		//{
		//	cout << test[i] << "\t";
		//}

	//	vector<int> test1 = mat.get_column(4);
		//for (int i = 0; i < 4; i++)
		//{
		//	cout << test1[i] << "\t";
		//}

	//	test.pop_back();
		//test.push_back(12);

		//cout << endl;
	//	mat.set_row(1, test);

		//AAA.print();

		//cout << endl << endl << endl;

		//test1.pop_back();
		//test1.push_back(12);

		//mat.set_column(1, test1);
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
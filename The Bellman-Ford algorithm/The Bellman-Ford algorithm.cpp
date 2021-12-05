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
	Timer time;//Объявления таймера.

	string name_data_file = "Weighted graph.txt"; //Переменная, хранящая путь до файла с данными.
	string name_save_file = "Result of work.txt"; //Переменная хранящая путь до файла с результатом работы.

	Bellman_Ford Graph(name_data_file);//Взвешенный граф берётся из файла.
	Graph.print_Matrix();//Вывод взвешенного графа в консоль. Взвешенный граф представлен в виде таблицы NxN, где N - кол-во вершин.

	Graph.Algoritm_Bellman_Ford_based_on_the_list();//Применение алгоритма Беллмана-Форда. (Результат будет сохранен во внутреннюю переменную класса, также результат можно присвоить матрице 'vector<vector<int>> {имя_матрицы}').

	vector<vector<int>> matrix_min_routes = Graph.Algoritm_Bellman_Ford_based_on_the_list();//Применение алгоритма Беллмана-Форда. (Результат будет сохранен во внутреннюю переменную класса и присвоен матрице 'vector<vector<int>> {имя_матрицы}').

	Graph.print_Result();//Вывод матрицы минимальных маршрутов в консоль для взвешенного графа.

	////Тест геттеров.
	//vector<vector<int>> test_mat;
	//test_mat = Graph.get_Matrix();
	//test_mat = Graph.get_Result();
	//vector<int> test;
	//test = Graph.get_Matrix_row(1);
	//test = Graph.get_Matrix_column(1);
	//bool test_info;
	//test_info = Graph.get_Application_of_the_algorithm();
	//test_info = Graph.get_Negative_cycle();
	//
	////Тест сеттеров. (После сеттеров, нужно будет применить алгоритм Беллмана-Форда ещё раз, так как матрица изменилась).
	//Graph.set_Matrix_row(3, test);
	//Graph.set_Matrix_column(3, test);

	//cout << endl << endl << endl << "Тест потокового вывода." << endl;
	//cout << Graph;
	//cout << "Конец теста потокового вывода." << endl << endl << endl;

	Graph.save_work_to_file(name_save_file);

	cout << "Время затраченное на тест методов класса: " << time.elapsed() << endl;//Вывод времени. (Алгоритм Беллмана-Форда применялся два раза).
	time.reset();//Сброс таймера.

	//Проверка времени работы алгоритма.
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl; //Пропускает строчки в консоле для наглядности.
	cout << "-------------------Тест времени работы алгоритма (граф без отрицательных циклов)-------------------" << endl;
	double sred_time = 0;
	time.reset();//Сброс таймера.

	Graph.Algoritm_Bellman_Ford_based_on_the_matrix();
	cout << "Тест 1 (based_on_the_matrix): " << time.elapsed() << endl;//Вывод времени.
	sred_time = sred_time + time.elapsed();
	time.reset();//Сброс таймера.

	Graph.Algoritm_Bellman_Ford_based_on_the_matrix();
	cout << "Тест 2 (based_on_the_matrix): " << time.elapsed() << endl;//Вывод времени.
	sred_time = sred_time + time.elapsed();
	time.reset();//Сброс таймера.

	Graph.Algoritm_Bellman_Ford_based_on_the_matrix();
	cout << "Тест 3 (based_on_the_matrix): " << time.elapsed() << endl;//Вывод времени.
	sred_time = sred_time + time.elapsed();
	time.reset();//Сброс таймера.

	Graph.Algoritm_Bellman_Ford_based_on_the_matrix();
	cout << "Тест 4 (based_on_the_matrix): " << time.elapsed() << endl;//Вывод времени.
	sred_time = sred_time + time.elapsed();
	time.reset();//Сброс таймера.

	Graph.Algoritm_Bellman_Ford_based_on_the_matrix();
	cout << "Тест 5 (based_on_the_matrix): " << time.elapsed() << endl;//Вывод времени.
	sred_time = sred_time + time.elapsed();
	time.reset();//Сброс таймера.

	cout << "Среднее время работы алгоритма (based_on_the_matrix): " << sred_time / 5 << endl;//Вывод времени.
	sred_time = 0;
	time.reset();//Сброс таймера.

	Graph.Algoritm_Bellman_Ford_based_on_the_list();
	cout << "Тест 1 (based_on_the_list): " << time.elapsed() << endl;//Вывод времени.
	sred_time = sred_time + time.elapsed();
	time.reset();//Сброс таймера.

	Graph.Algoritm_Bellman_Ford_based_on_the_list();
	cout << "Тест 2 (based_on_the_list): " << time.elapsed() << endl;//Вывод времени.
	sred_time = sred_time + time.elapsed();
	time.reset();//Сброс таймера.

	Graph.Algoritm_Bellman_Ford_based_on_the_list();
	cout << "Тест 3 (based_on_the_list): " << time.elapsed() << endl;//Вывод времени.
	sred_time = sred_time + time.elapsed();
	time.reset();//Сброс таймера.

	Graph.Algoritm_Bellman_Ford_based_on_the_list();
	cout << "Тест 4 (based_on_the_list): " << time.elapsed() << endl;//Вывод времени.
	sred_time = sred_time + time.elapsed();
	time.reset();//Сброс таймера.

	Graph.Algoritm_Bellman_Ford_based_on_the_list();
	cout << "Тест 5 (based_on_the_list): " << time.elapsed() << endl;//Вывод времени.
	sred_time = sred_time + time.elapsed();
	time.reset();//Сброс таймера.

	cout << "Среднее время работы алгоритма (based_on_the_list): " << sred_time / 5 << endl;//Вывод времени.

	return 0;
}
#pragma once
#include <iostream>
#include <string>
#include <fstream> //библиотека для работы с файлами.
#include <vector>

using namespace std;

class Bellman_Ford
{
private:
	//Matrix - хранит информацию о взвешенном графе.
	vector<vector<int>> Matrix;
	//Result - хранит кратчайшие пути от одной вершины до всех остальных. 
	vector<vector<int>> Result;
	//Negative cycle - хранит инфомацию о наличии отрицательного цикла в графе. (true - есть отрицательный цикл; false - нет отрицательного цикла).
	bool Negative_cycle = false;
	//Application_of_the_algorithm - хранит информацию о применеии алгоритма Беллмана-Форда. (true - алгоритм применялся; false - алгоритм не применялся).  
	bool Application_of_the_algorithm = false;

	/*
	Application_of_the_algorithm = false - когда алгоритм не применялся, или значения в матрице были измененны, например set_row или set_column.
	Значение false говорит о том, что матрица кратчайших путей не соответствует матрице взешанного графа.
	*/

protected:
	int find_min(vector<int> result_of_addition);

public:

	//Конструктор 1 - Взятие матрицы графа из файла.
	Bellman_Ford(string namefile);

	/*
	Правила записи графа в файл:
	1)Матрица должна быть целочисленной и квадратной;
	2)Числа отделяются друг от друга пробелом;
	3)В конце строки - переход на новую строку (enter);
	4)В конце последней строки ничего не ставится.
	*/

	//Конструктор 2 - Задание матрицы в программе (ввод одного числа, создатся матрица NxN и начнется заполение случайными числами).
	Bellman_Ford(int size_matrix);

	//Конструктор 3 - Матрица будет скопированна из основной программы. (Передаваемая матрица должна быть квадратной).
	Bellman_Ford(vector<vector<int>> mat);

	//Деструктор.
	~Bellman_Ford() {};

	//Геттеры.
	vector<vector<int>> get_Matrix();//Получить Matrix (хранит информацию о взвешенном графе).
	vector<vector<int>> get_Result();//Получить Result (хранит кратчайшие пути от одной вершины до всех остальных).
	vector<int> get_row(int number_row);//Получить строку.
	vector<int> get_column(int number_column);//Получить столбец.
	bool get_Negative_cycle();//Получить информацию о наличии отрицательного цикла.
	bool get_Application_of_the_algorithm();//Получить инфомацию о применении алгоритма Беллмана-Форда
	//Сеттеры.
	void set_row(int number_row, vector<int> row);//Параметр 1 - номер строки. Параметр 2 - строка, которая заменит страую строку.
	void set_column(int number_column, vector<int> column);//Параметр 1 - номер столбца. Параметр 2 - столбец, который заменит страый столбец.

	//Метод, реализующий алгоритм.
	vector<vector<int>> Algoritm_Bellman_Ford();

	//Вывод матрицы смежности.
	void print_Matrix();

	//Вывод матрици минимальных маршрутов.
	void print_Result();

	//Переопределение операции << для вывода 
};
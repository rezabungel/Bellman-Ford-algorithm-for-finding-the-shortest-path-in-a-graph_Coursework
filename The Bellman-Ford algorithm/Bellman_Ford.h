#pragma once
#include <iostream>
#include <string>
#include <fstream> //библиотека для работы с файлами.
#include <vector>

using namespace std;

//Класс ребро. Используется для построения списков смежности.
class Edge
{
private:
	int from, to, weight;
public:
	//Конструктор.
	Edge(int from = -1, int to = -1, int weight = 0) : from(from), to(to), weight(weight) {}
	Edge(const Edge& E);

	//Деструктор.
	~Edge() {};

	//Геттеры.
	int get_from();
	int get_to();
	int get_weight();

	//Сеттеры.
	void set_from(int a);
	void set_to(int a);
	void set_weight(int a);

	//Операции сравнения.
	bool operator<(const Edge& E);
	bool operator>(const Edge& E);

	friend ostream& operator<<(ostream& s, Edge& e);
};

class Bellman_Ford
{
private:
	//Matrix - хранит информацию о взвешенном графе.
	vector<vector<int>> Matrix;
	//Result - хранит кратчайшие пути от одной вершины до всех остальных. 
	vector<vector<int>> Result;
	//Negative cycle - хранит информацию о наличии отрицательного цикла в графе. (true - есть отрицательный цикл; false - нет отрицательного цикла).
	bool Negative_cycle = false;
	//Application_of_the_algorithm - хранит информацию о применении алгоритма Беллмана-Форда. (true - алгоритм применялся; false - алгоритм не применялся).  
	bool Application_of_the_algorithm = false;

	/*
	Application_of_the_algorithm = false - когда алгоритм не применялся, или значения в матрице были изменены, например set_row или set_column.
	Значение false говорит о том, что матрица кратчайших путей не соответствует матрице взвешенного графа.
	*/

protected:
	int find_min(const vector<int>& result_of_addition);

	inline bool relax(const int& old_weight, const int& new_way, const int& weight); //inline просьба компилятору заменить вызов функции на её тело в точке вызова. Компилятор может этого и не сделать, использовать обычный вызов.

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

	//Конструктор 2 - Задание матрицы в программе (ввод одного числа, создастся матрица NxN и начнется заполнение случайными числами).
	Bellman_Ford(int size_matrix);

	//Конструктор 3 - Матрица будет скопирована из основной программы. (Передаваемая матрица должна быть квадратной).
	Bellman_Ford(vector<vector<int>> mat);

	//Деструктор.
	~Bellman_Ford() {};

	//Геттеры.
	vector<vector<int>> get_Matrix();//Получить Matrix (хранит информацию о взвешенном графе).
	vector<vector<int>> get_Result();//Получить Result (хранит кратчайшие пути от одной вершины до всех остальных).
	vector<int> get_Matrix_row(int number_row);//Получить строку матрицы, хранящий взвешенный граф.
	vector<int> get_Matrix_column(int number_column);//Получить столбец матрицы, хранящий взвешенный граф.
	bool get_Negative_cycle();//Получить информацию о наличии отрицательного цикла.
	bool get_Application_of_the_algorithm();//Получить информацию о применении алгоритма Беллмана-Форда
	//Сеттеры. (Если изменить значения в матрице, хранящий взвешенный граф, то алгоритм Беллмана-Форда нужно будет применить ещё раз для новых данных).
	void set_Matrix_row(int number_row, vector<int> row);//Параметр 1 - номер строки. Параметр 2 - строка, которая заменит старую строку.
	void set_Matrix_column(int number_column, vector<int> column);//Параметр 1 - номер столбца. Параметр 2 - столбец, который заменит старый столбец.

	//Метод, реализующий алгоритм. Работает на основе матрицы смежности.
	vector<vector<int>> Algoritm_Bellman_Ford_based_on_the_matrix();

	//Метод, реализующий алгоритм. Работает на основе списка смежности. (Работает быстрее).
	vector<vector<int>> Algoritm_Bellman_Ford_based_on_the_list(); //Этот метод и будем оптимизировать по производительности.

	//Вывод матрицы смежности.
	void print_Matrix();

	//Вывод матрицы минимальных маршрутов.
	void print_Result();

	//Сохранение матриц в файл.
	void save_work_to_file(string namefile);

	//Переопределение операции << для вывода в консоль и вывода в файл.
	friend ostream& operator<< (ostream& ustream, Bellman_Ford& obj);
};
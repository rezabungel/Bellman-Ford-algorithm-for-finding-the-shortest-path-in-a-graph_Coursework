#pragma once
#include <iostream>
#include <string>
#include <fstream> //библиотека для работы с файлами.
#include <vector>

using namespace std;

class Bellman_Ford
{
private:
	//Matrix - хранит информацию о взвешенном графе
	vector<vector<int>> Matrix;

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
	vector<int> get_row(int number_row);//Получить строку.
	vector<int> get_column(int number_column);//Получить столбец.
	//Сеттеры.
	void set_row(int number_row, vector<int> row);//Параметр 1 - номер строки. Параметр 2 - строка, которая заменит страую строку.
	void set_column(int number_column, vector<int> column);//Параметр 1 - номер столбца. Параметр 2 - столбец, который заменит страый столбец.

	//Метод, описывающий алгоритм.

	//Вывод матрицы смежности.
	void print_Matrix();

	//Переопределение операции << для вывода 
};
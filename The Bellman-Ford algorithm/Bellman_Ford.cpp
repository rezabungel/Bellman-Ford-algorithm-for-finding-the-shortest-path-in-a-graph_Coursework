﻿#include "Bellman_Ford.h"

//Конструктор 1 - Взятие матрицы графа из файла.
Bellman_Ford::Bellman_Ford(string namefile)
{
	ifstream fin;
	fin.open(namefile); //Открываем файл.
	if (!fin.is_open()) //Проверка на то, смогли ли мы открыть наш файл.
	{
		cout << "***************************************************************************************************" << endl;
		cout << "Ошибка открытия файла." << endl;
		cout << "Программа завершает работу. Пожалуйста, создайте файл ''Weighted graph.txt''." << endl;
		cout << "***************************************************************************************************" << endl;
		exit(1);//Завершаем работу программы.
	}
	else
	{
		cout << "***************************************************************************************************" << endl;
		cout << "Файл открыт." << endl;
		vector<int> temp;//Временный вектор, который необходим для заполнения матрицы смежности.
		while (!fin.eof())//Цикл работает до тех пор, пока не дойдет до конца файла.
		{
			char end_line;
			string str;
			fin >> str;
			int weight = stoi(str);//Преобразование типа строки в целочисленынй тип. (В строке хранится вес ребра).
			temp.push_back(weight);
			fin.get(end_line);
			if (end_line == '\n') //10 - код перехода на новую строку. 10 = '\n'. (вместо '\n' можно исполькозовать код 10)
			{
				Matrix.push_back(temp);
				temp.clear();
			}
		}
		Matrix.push_back(temp);
		temp.clear();
		cout << "Матрица смежности успешно считана из файла." << endl;
	};
	cout << "Файл закрыт." << endl;
	fin.close();//закрываем файл.
	cout << "***************************************************************************************************" << endl;
}

//Конструктор 2 - Задание матрицы в программе (ввод одного числа, создатся матрица NxN и начнется заполение случайными числами).
Bellman_Ford::Bellman_Ford(int size_matrix)
{
	for (int i = 0; i < size_matrix; i++)
	{
		vector<int> temp;//Временный вектор, который необходим для заполнения матрицы смежности.
		for (int j = 0; j < size_matrix; j++)
		{
			temp.push_back(rand() % 100 - 5);
		}
		Matrix.push_back(temp);
	}
}

//Конструктор 3 - Матрица будет скопированна из основной программы. (Передаваемая матрица должна быть квадратной).
Bellman_Ford::Bellman_Ford(vector<vector<int>> mat)
{
	Matrix = mat;
}

vector<vector<int>> Bellman_Ford::get_Matrix()
{
	return Matrix;
}

vector<vector<int>> Bellman_Ford::get_Result()
{
	if (Application_of_the_algorithm == true)
	{
		if (Negative_cycle == true)
		{
			cout << "Граф содержит отрицательный цикл." << endl;
			cout << "Матрица, хранящая информацию о кратчайших путях - будет хранить нули." << endl;
		}
	}
	else
	{
		cout << endl << endl << endl << "***************************************************************************************************" << endl;
		cout << "Алгоритм Беллмана-Форда не применялся или матрица, хранящая инфомацию о графе, была изменена." << endl;
		cout << "Сейчас будет применён алгоритм и выдан результат." << endl;
		cout << "***************************************************************************************************" << endl << endl << endl;
		Algoritm_Bellman_Ford();
	}
	return Result;
}

vector<int> Bellman_Ford::get_row(int number_row)
{
	vector<int> row;
	if (number_row > 0 && number_row <= Matrix.size())
	{
		row = Matrix[number_row - 1];
	}
	else
	{
		cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		cout << "Строки c номером " << number_row << " нету в матрице. Будет возвращенна 1-ая строка.";
		cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		row = Matrix[0];
	}
	return row;
}

vector<int> Bellman_Ford::get_column(int number_column)
{
	vector<int> column;
	if (number_column > 0 && number_column <= Matrix.size())
	{
		for (int i = 0; i < Matrix.size(); i++)
		{
			column.push_back(Matrix[i][number_column - 1]);
		}
	}
	else
	{
		cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		cout << "Столбца c номером " << number_column << " нету в матрице. Будет возвращен 1-ый столбец.";
		cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		for (int i = 0; i < Matrix.size(); i++)
		{
			column.push_back(Matrix[i][0]);
		}
	}
	return column;
}

bool Bellman_Ford::get_Negative_cycle()
{
	if (Application_of_the_algorithm != true)
	{
		cout << endl << endl << endl << "***************************************************************************************************" << endl;
		cout << "Алгоритм Беллмана-Форда не применялся или матрица, хранящая инфомацию о графе, была изменена." << endl;
		cout << "Сейчас будет применён алгоритм и выдан результат." << endl;
		cout << "***************************************************************************************************" << endl << endl << endl;
		Algoritm_Bellman_Ford();
		return Negative_cycle;
	}
	return Negative_cycle;
}

bool Bellman_Ford::get_Application_of_the_algorithm()
{
	return Application_of_the_algorithm;
}

void Bellman_Ford::set_row(int number_row, vector<int> row)
{
	if (row.size() > Matrix.size())
	{
		cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		cout << "В передаваемой строке есть проблема. Она больше, чем строки в матрице. Из передоваемой строки, будут взяты только первые N элементов (N-размерность матрицы).";
		cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		for (int i = row.size(); i > Matrix.size(); i--)
		{
			row.pop_back();
		}
	}
	else
	{
		if (row.size() < Matrix.size())
		{
			cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
			cout << "В передаваемой строке есть проблема. Она меньше, чем строки в матрице. Передаваемая строка будет дополнена нулями.";
			cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
			for (int i = row.size(); i < Matrix.size(); i++)
			{
				row.push_back(0);
			}
		}
	}
	if (number_row > 0 && number_row <= Matrix.size())
	{
		Matrix[number_row - 1] = row;
	}
	else
	{
		cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		cout << "В матрице нет строки c номером " << number_row << ". Будет заменена 1-ая строка.";
		cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		Matrix[0] = row;
	}
	Application_of_the_algorithm = false;
}

void Bellman_Ford::set_column(int number_column, vector<int> column)
{
	if (column.size() > Matrix.size())
	{
		cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		cout << "В передаваемом столбце есть проблема. Он больше, чем столбцы в матрице. Из передоваемого столбца, будут взяты только первые N элементов (N-размерность матрицы).";
		cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		for (int i = column.size(); i > Matrix.size(); i--)
		{
			column.pop_back();
		}
	}
	else
	{
		if (column.size() < Matrix.size())
		{
			cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
			cout << "В передаваемом столбце есть проблема. Он меньше, чем столбцы в матрице. Передаваемый столбец будет дополнен нулями.";
			cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
			for (int i = column.size(); i < Matrix.size(); i++)
			{
				column.push_back(0);
			}
		}
	}
	if (number_column > 0 && number_column <= Matrix.size())
	{
		for (int i = 0; i < Matrix.size(); i++)
		{
			Matrix[i][number_column - 1] = column[i];
		}
	}
	else
	{
		cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		cout << "В матрице нет столбца c номером " << number_column << ". Будет заменён 1-ый столбец.";
		cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		for (int i = 0; i < Matrix.size(); i++)
		{
			Matrix[i][0] = column[i];
		}
	}
	Application_of_the_algorithm = false;
}

vector<vector<int>> Bellman_Ford::Algoritm_Bellman_Ford()
{
	//Обнуляем матруцу кратчайших путей. Это обнуление будет выполняться, когда мы повторно применяем алгорит (больше 1 раза). 
	if (Result.size() > 0)
	{
		for (int i = 0; i < Result.size(); i++)
		{
			Result[i].clear();
		}
		Result.clear();
	}

	vector<vector<int>> help_matrix;
	vector<vector<int>> intermediate_matrix;
	vector<int> temp;//Временный вектор, который необходим для заполнения матрицы.
	//Инициализируем Result.
	for (int i = 0; i < Matrix.size(); i++)
	{
		for (int j = 0; j < Matrix.size(); j++)
		{
			if (Matrix[i][j] == 0)
			{
				temp.push_back(9999999); //9999999 - наша бесконечность, которая говорит об отсутствии пути.
			}
			else
			{
				temp.push_back(Matrix[i][j]);
			}
		}
		Result.push_back(temp);
		help_matrix.push_back(temp);
		intermediate_matrix.push_back(temp);
		temp.clear();
	}
	for (int i = 0; i < Matrix.size(); i++)//Если у вершины нет петли, то в ней устанавливается 0.
	{
		if (Result[i][i] == 9999999)
		{
			Result[i][i] = 0;
			help_matrix[i][i] = 0;
			intermediate_matrix[i][i] = 0;
		}
	}

	for (int i = 0; i < Matrix.size() - 1; i++) //Алгоритм находит кратчайший путь до всех вершин за N-1 итерацию, где N - кол-во вершин в графе.
	{
		for (int j = 0; j < Matrix.size(); j++)
		{
			for (int count_column = 0; count_column < Matrix.size(); count_column++)
			{
				for (int k = 0; k < Matrix.size(); k++)
				{
					temp.push_back(intermediate_matrix[j][k] + help_matrix[k][count_column]);
				}
				temp.push_back(intermediate_matrix[j][count_column]);//Взятие элемента, который был раньше.
				int min = find_min(temp);
				Result[j][count_column] = min;
				temp.clear();
			}
		}
		intermediate_matrix = Result;
	}

	//N-ная итерация, которая определит наличие отрицательного цикла.
	for (int j = 0; j < Matrix.size(); j++)
	{
		for (int count_column = 0; count_column < Matrix.size(); count_column++)
		{
			for (int k = 0; k < Matrix.size(); k++)
			{
				temp.push_back(intermediate_matrix[j][k] + help_matrix[k][count_column]);
			}
			temp.push_back(intermediate_matrix[j][count_column]);//Взятие элемента, который был раньше.
			int min = find_min(temp);
			Result[j][count_column] = min;
			temp.clear();
		}
	}

	if (intermediate_matrix == Result)
	{
		cout << endl << endl << endl << "***************************************************************************************************" << endl;
		cout << "Отрицательного цикла в графе - нет.";
		cout << endl << "***************************************************************************************************" << endl << endl << endl;
		Negative_cycle = false;
	}
	else
	{
		cout << endl << endl << endl << "***************************************************************************************************" << endl;
		cout << "Граф содержит отрицательный цикл." << endl;
		cout << "Матрица, хранящая информацию о кратчайших путях - будет хранить нули.";
		for (int i = 0; i < Matrix.size(); i++)
		{
			for (int j = 0; j < Matrix.size(); j++)
			{
				Result[i][j] = 0;
			}
		}
		cout << endl << "***************************************************************************************************" << endl << endl << endl;
		Negative_cycle = true;
	}
	Application_of_the_algorithm = true;
	return Result;
}

void Bellman_Ford::print_Matrix()
{
	cout << "--------------------------------------------Data Matrix--------------------------------------------" << endl;
	for (int i = 0; i < Matrix.size(); i++)
	{
		for (int j = 0; j < Matrix[i].size(); j++)
		{
			cout << Matrix[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "---------------------------------------------------------------------------------------------------" << endl;
}

void Bellman_Ford::print_Result()
{
	if (Application_of_the_algorithm == true)
	{
		if (Negative_cycle == true)
		{
			cout << endl << "***************************************************************************************************" << endl;
			cout << "Граф содержит отрицательный цикл." << endl;
			cout << "Матрица, хранящая информацию о кратчайших путях - будет хранить нули." << endl;
			cout << "-------------------------------------------Result Matrix-------------------------------------------" << endl;
			for (int i = 0; i < Result.size(); i++)
			{
				for (int j = 0; j < Result[i].size(); j++)
				{
					cout << Result[i][j] << "\t";
				}
				cout << endl;
			}
			cout << "---------------------------------------------------------------------------------------------------" << endl;
			cout << endl << "***************************************************************************************************" << endl;

		}
		else
		{
			cout << "Отрицательного цикла в графе - нет." << endl;
			cout << "-------------------------------------------Result Matrix-------------------------------------------" << endl;
			for (int i = 0; i < Result.size(); i++)
			{
				for (int j = 0; j < Result[i].size(); j++)
				{
					cout << Result[i][j] << "\t";
				}
				cout << endl;
			}
			cout << "---------------------------------------------------------------------------------------------------" << endl;
		}
	}
	else
	{
		cout << endl << "***************************************************************************************************" << endl;
		cout << "Алгорит Беллмана-Форда не применялся или матрица, хранящая инфомацию о графе, была изменена.";
		cout << endl << "***************************************************************************************************" << endl;
	}
}

int Bellman_Ford::find_min(vector<int> result_of_addition)
{
	int min = result_of_addition[0];
	for (int i = 1; i < result_of_addition.size(); i++)
	{
		if (min > result_of_addition[i])
		{
			min = result_of_addition[i];
		}
	}
	return min;
}
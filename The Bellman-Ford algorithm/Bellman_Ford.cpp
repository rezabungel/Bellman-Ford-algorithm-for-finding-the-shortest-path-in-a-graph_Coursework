#include "Bellman_Ford.h"

//Конструктор.
Edge::Edge(const Edge& E)
{
	from = E.from;
	to = E.to;
	weight = E.weight;
}

//Геттеры.
int Edge::get_from()
{
	return from;
}
int Edge::get_to()
{
	return to;
}
int Edge::get_weight()
{
	return weight;
}

//Сеттеры.
void Edge::set_from(int a)
{
	from = a;
}
void Edge::set_to(int a)
{
	to = a;
}
void Edge::set_weight(int a)
{
	weight = a;
}

//Операции сравнения.
bool Edge::operator<(const Edge& E)
{
	if (weight < E.weight)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Edge::operator>(const Edge& E)
{
	if (weight > E.weight)
	{
		return true;
	}
	else
	{
		return false;
	}
}


ostream& operator<<(ostream& s, Edge& e)
{
	s << "From: " << e.from << ", to: " << e.to << ", weight: " << e.weight;
	return s;
}

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

		char end1;//Чтобы консоль вывода не закрылась.
		cin >> end1;

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
			int weight = stoi(str);//Преобразование типа строки в целочисленный тип. (В строке хранится вес ребра).
			temp.push_back(weight);
			fin.get(end_line);
			if (end_line == '\n') //10 - код перехода на новую строку. 10 = '\n'. (вместо '\n' можно использовать код 10)
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

//Конструктор 2 - Задание матрицы в программе (ввод одного числа, создастся матрица NxN и начнется заполнение случайными числами).
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

//Конструктор 3 - Матрица будет скопирована из основной программы. (Передаваемая матрица должна быть квадратной).
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
		cout << "Алгоритм Беллмана-Форда не применялся или матрица, хранящая информацию о графе, была изменена." << endl;
		cout << "Сейчас будет применён алгоритм и выдан результат." << endl;
		cout << "***************************************************************************************************" << endl << endl << endl;
		Algoritm_Bellman_Ford_based_on_the_list();
	}
	return Result;
}

vector<int> Bellman_Ford::get_Matrix_row(int number_row)
{
	vector<int> row;
	if (number_row > 0 && number_row <= Matrix.size())
	{
		row = Matrix[number_row - 1];
	}
	else
	{
		cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		cout << "Строки c номером " << number_row << " нету в матрице. Будет возвращена 1-ая строка.";
		cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		row = Matrix[0];
	}
	return row;
}

vector<int> Bellman_Ford::get_Matrix_column(int number_column)
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
		cout << "Алгоритм Беллмана-Форда не применялся или матрица, хранящая информацию о графе, была изменена." << endl;
		cout << "Сейчас будет применён алгоритм и выдан результат." << endl;
		cout << "***************************************************************************************************" << endl << endl << endl;
		Algoritm_Bellman_Ford_based_on_the_list();
		return Negative_cycle;
	}
	return Negative_cycle;
}

bool Bellman_Ford::get_Application_of_the_algorithm()
{
	return Application_of_the_algorithm;
}

void Bellman_Ford::set_Matrix_row(int number_row, vector<int> row)
{
	if (row.size() > Matrix.size())
	{
		cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		cout << "В передаваемой строке есть проблема. Она больше, чем строки в матрице. Из передаваемой строки, будут взяты только первые N элементов (N-размерность матрицы).";
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
	Negative_cycle = false;
	Application_of_the_algorithm = false;
}

void Bellman_Ford::set_Matrix_column(int number_column, vector<int> column)
{
	if (column.size() > Matrix.size())
	{
		cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		cout << "В передаваемом столбце есть проблема. Он больше, чем столбцы в матрице. Из передаваемого столбца, будут взяты только первые N элементов (N-размерность матрицы).";
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
	Negative_cycle = false;
	Application_of_the_algorithm = false;
}

vector<vector<int>> Bellman_Ford::Algoritm_Bellman_Ford_based_on_the_matrix()
{
	//Обнуляем матрицу кратчайших путей. Это обнуление будет выполняться, когда мы повторно применяем алгоритм (больше 1 раза). 
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
			if (Matrix[i][j] == 0 && i != j)
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
		//cout << endl << endl << endl << "***************************************************************************************************" << endl;
		//cout << "Отрицательного цикла в графе - нет.";
		//cout << endl << "***************************************************************************************************" << endl << endl << endl;
		for (int i = 0; i < Matrix.size(); i++) //Заменяем нашу бесконечность на ноль. (пути нет).
		{
			for (int j = 0; j < Matrix.size(); j++)
			{
				if (Result[i][j] == 9999999)
				{
					Result[i][j] = 0;
				}
			}
		}
		Negative_cycle = false;
	}
	else
	{
		//cout << endl << endl << endl << "***************************************************************************************************" << endl;
		//cout << "Граф содержит отрицательный цикл." << endl;
		//cout << "Матрица, хранящая информацию о кратчайших путях - будет хранить нули.";
		for (int i = 0; i < Matrix.size(); i++)
		{
			for (int j = 0; j < Matrix.size(); j++)
			{
				Result[i][j] = 0;
			}
		}
		//cout << endl << "***************************************************************************************************" << endl << endl << endl;
		Negative_cycle = true;
	}
	Application_of_the_algorithm = true;
	return Result;
}

vector<vector<int>> Bellman_Ford::Algoritm_Bellman_Ford_based_on_the_list()
{
	//Обнуляем матрицу кратчайших путей. Это обнуление будет выполняться, когда мы повторно применяем алгоритм (больше 1 раза). 
	if (Result.size() > 0)
	{
		for (int i = 0; i < Result.size(); i++)
		{
			Result[i].clear();
		}
		Result.clear();
	}

	vector<Edge> adjacency_list;//Список смежности.
	for (int i = 0; i < Matrix.size(); i++)//Записывает все вершины матрицы смежности в виде списка смежности.
	{
		for (int j = 0; j < Matrix.size(); j++)
		{
			if (Matrix[i][j] != 0 && i != j)
			{
				Edge for_push(i, j, Matrix[i][j]);
				adjacency_list.push_back(for_push);
			}
		}
	}

	//Итерация для первой (нулевой) вершины, для определения наличия отрицательного цикла.
	vector<int> dist(Matrix.size(), 9999999);//Минимальные расстояния от стартовой вершины до всех остальных. (9999999 - наша бесконечность).
	dist[0] = 0; //Стартовая вершина инициализируется 0.
	vector<int> past = dist;

	for (int i = 0; i < Matrix.size() - 1; i++) //Алгоритм находит кратчайший путь от стартовой вершины до всех остальных за N-1 итерацию, где N - кол-во вершин в графе.
	{
		for (int j = 0; j < adjacency_list.size(); j++)
		{
			//if (relax(dist[adjacency_list[j].get_to()], dist[adjacency_list[j].get_from()], adjacency_list[j].get_weight())) //Отказываемся от вызова функции (метода) relax. Применяем этот код сразу в алгоритме, для уменьшения времени работы.
			if (dist[adjacency_list[j].get_to()] > dist[adjacency_list[j].get_from()] + adjacency_list[j].get_weight())
			{
				dist[adjacency_list[j].get_to()] = dist[adjacency_list[j].get_from()] + adjacency_list[j].get_weight();
			}
		}
		if (past != dist)
		{//Минимальные пути ещё не найдены.
			past = dist;
		}
		else
		{//Минимальные пути найдены, можно досрочно завершить цикл.
			break;
		}
	}

	//Проверяем отрицательный цикл только для первой вершины, если он будет, то досрочно завершаем алгоритм, если его не будет, то нет смысла проверять наличие отрицательного цикла для других вершин.
	vector<int> change_dist = dist;
	for (int j = 0; j < adjacency_list.size(); j++) //N-ная итерация, которая определит наличие отрицательного цикла.
	{
		//if (relax(change_dist[adjacency_list[j].get_to()], change_dist[adjacency_list[j].get_from()], adjacency_list[j].get_weight())) //Отказываемся от вызова функции (метода) relax. Применяем этот код сразу в алгоритме, для уменьшения времени работы.
		if (change_dist[adjacency_list[j].get_to()] > change_dist[adjacency_list[j].get_from()] + adjacency_list[j].get_weight())
		{
			change_dist[adjacency_list[j].get_to()] = change_dist[adjacency_list[j].get_from()] + adjacency_list[j].get_weight();
		}
	}

	//Если на N-ной итерации изменилось минимальное расстояние, то граф имеет отрицательный цикл, поэтому говорить о минимальном пути не имеет смысла.
	if (change_dist == dist)
	{
		//cout << endl << endl << endl << "***************************************************************************************************" << endl;
		//cout << "Отрицательного цикла в графе - нет.";
		//cout << endl << "***************************************************************************************************" << endl << endl << endl;
		Negative_cycle = false;
	}
	else
	{
		//cout << endl << endl << endl << "***************************************************************************************************" << endl;
		//cout << "Граф содержит отрицательный цикл." << endl;
		//cout << "Матрица, хранящая информацию о кратчайших путях - будет хранить нули.";
		//cout << endl << "***************************************************************************************************" << endl << endl << endl;

		//Записываем нули.	
		vector<vector<int>> for_result(Matrix.size(), vector<int>(Matrix.size(), 0));
		Result = for_result;

		Negative_cycle = true;
		Application_of_the_algorithm = true;
		return Result;
	}
	Result.push_back(dist);//Выполнится если в графе нет отрицательного цикла.

	//Начинаем с первой вершины, т.к. для нулевой вершины минимальные пути уже найдены. (Проверку на отрицательный цикл, не выполняем, т.к. дошли этого момента, значит его точно нет).
	for (int vertex = 1; vertex < Matrix.size(); vertex++)
	{
		vector<int> dist(Matrix.size(), 9999999);//Минимальные расстояния от стартовой вершины до всех остальных. (9999999 - наша бесконечность).
		dist[vertex] = 0; //Стартовая вершина инициализируется 0.
		vector<int> past = dist;

		for (int i = 0; i < Matrix.size() - 1; i++) //Алгоритм находит кратчайший путь от стартовой вершины до всех остальных за N-1 итерацию, где N - кол-во вершин в графе.
		{
			for (int j = 0; j < adjacency_list.size(); j++)
			{
				//if (relax(dist[adjacency_list[j].get_to()], dist[adjacency_list[j].get_from()], adjacency_list[j].get_weight())) //Отказываемся от вызова функции (метода) relax. Применяем этот код сразу в алгоритме, для уменьшения времени работы.
				if (dist[adjacency_list[j].get_to()] > dist[adjacency_list[j].get_from()] + adjacency_list[j].get_weight())
				{
					dist[adjacency_list[j].get_to()] = dist[adjacency_list[j].get_from()] + adjacency_list[j].get_weight();
				}
			}
			if (past != dist)
			{//Минимальные пути ещё не найдены.
				past = dist;
			}
			else
			{//Минимальные пути найдены, можно досрочно завершить цикл.
				break;
			}
		}
		Result.push_back(dist);
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
		cout << "Алгоритм Беллмана-Форда не применялся или матрица, хранящая информацию о графе, была изменена.";
		cout << endl << "***************************************************************************************************" << endl;
	}
}

int Bellman_Ford::find_min(const vector<int>& result_of_addition)
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

inline bool Bellman_Ford::relax(const int& old_weight, const int& new_way, const int& weight)
{
	//Тернарный оператор.
	return (old_weight > new_way + weight) ? (true) : (false);
}

void Bellman_Ford::save_work_to_file(string namefile)
{
	ofstream fout;
	fout.open(namefile);//Если файла нет, то он будет создан.

	if (!fout.is_open())
	{
		cout << "***************************************************************************************************" << endl;
		cout << "Ошибка открытия файла для сохранения данных!" << endl;
		cout << "***************************************************************************************************" << endl;
	}
	else
	{
		cout << "***************************************************************************************************" << endl;
		cout << "Файл для сохранения данных открыт." << endl;
		fout << *this;
		cout << "Данные успешно записаны в файл." << endl;
		cout << "Файл закрыт." << endl;
		fout.close();//закрываем файл.
		cout << "***************************************************************************************************" << endl;
	}
}

ostream& operator<<(ostream& ustream, Bellman_Ford& obj)
{
	string str;
	str = "Матрица, которая хранит информацию о взвешенном графе.";
	ustream << str << endl;
	ustream << "--------------------------------------------Data Matrix--------------------------------------------" << endl;
	for (int i = 0; i < obj.Matrix.size(); i++)
	{
		for (int j = 0; j < obj.Matrix[i].size(); j++)
		{
			ustream << obj.Matrix[i][j] << "\t";
		}
		ustream << endl;
	}
	ustream << "---------------------------------------------------------------------------------------------------" << endl << endl << endl;

	if (obj.Application_of_the_algorithm == true)
	{
		if (obj.Negative_cycle == true)
		{
			str = "Взвешенный граф имеет отрицательный цикл.";
			ustream << str << endl;
		}
		else
		{
			str = "Взвешенный граф не имеет отрицательного цикла.";
			ustream << str << endl << endl << endl;
			str = "Матрица кратчайших путей от одной вершины до всех остальных.";
			ustream << str << endl;
			ustream << "-------------------------------------------Result Matrix-------------------------------------------" << endl;
			for (int i = 0; i < obj.Result.size(); i++)
			{
				for (int j = 0; j < obj.Result[i].size(); j++)
				{
					ustream << obj.Result[i][j] << "\t";
				}
				ustream << endl;
			}
			ustream << "---------------------------------------------------------------------------------------------------" << endl;
		}
	}
	else
	{
		str = "Алгоритм Беллмана-Форда не был применён.";
		ustream << str << endl;
	}

	return ustream;
}
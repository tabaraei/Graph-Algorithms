//In the name of God
//Programmed by Ali Tabaraei
#include <iostream>
#include <conio.h>
#include <Windows.h>
#define max 100000
using namespace std;

//Local variable
bool first = true;

class Graph
{
public:

	//Input methods
	void input(int size);
	void directed_graph();
	void undirected_graph();
	void simple_graph();

	//Algorithms
	void dijkstra(int position);
	void bfs(int position);
	void dfs(int position);
	void kruskal();
	void prim(int position);
	void floydwarshal();

private:

	//variables
	int **graph;
	int length;

	//Supporting functions
	int min_distance(int vertice[], bool check[]);
	bool no_path(bool *check, int position);
	bool no_cycle(int **result, int position1, int position2);
};

void Graph::input(int size)
{
	length = size;
	first = false;

	system("cls");

	cout << "Please enter type of graph!" << endl << endl;
	cout << "1) Weighted directed graph" << endl << "2) Weighted undirected graph" << endl << "3) Simple graph" << endl;

	switch (_getch())
	{
	case '1':
		directed_graph();
		break;

	case '2':
		undirected_graph();
		break;

	case '3':
		simple_graph();
		break;

	default:
		break;
	}
}

void Graph::directed_graph()
{
	system("cls");

	graph = new int*[length];

	cout << "The selected graph includes " << length << " vertices, named <a> to <" << (char)(96 + length) << ">" << endl << endl;
	cout << "Now, to figure out edges of your graph:" << endl;
	cout << "-if there is a relationship between selected vertices, insert weight" << endl;
	cout << "-if there is no relationship between selected vertices, insert zero" << endl << endl;

	for (int i = 0; i < length; i++)
	{
		graph[i] = new int[length];

		for (int j = 0; j < length; j++)
		{
			cout << "Edge " << (char)(97 + i) << " - " << (char)(97 + j) << ":" << endl;
			cin >> graph[i][j];
		}
	}
}

void Graph::undirected_graph()
{
	system("cls");

	graph = new int*[length];

	cout << "The selected graph includes " << length << " vertices, named <a> to <" << (char)(96 + length) << ">" << endl << endl;
	cout << "Now, to figure out edges of your graph:" << endl;
	cout << "-if there is a relationship between selected vertices, insert weight" << endl;
	cout << "-if there is no relationship between selected vertices, insert zero" << endl << endl;

	for (int i = 0; i < length; i++)
	{
		graph[i] = new int[length];

		for (int j = 0; j < length; j++)
		{
			if (j > i)
			{
				cout << "Edge " << (char)(97 + i) << " - " << (char)(97 + j) << ":" << endl;
				cin >> graph[i][j];
			}

			else
				graph[i][j] = 0;
		}
	}
}

void Graph::simple_graph()
{
	system("cls");

	graph = new int*[length];

	cout << "The selected graph includes " << length << " vertices, named <a> to <" << (char)(96 + length) << ">" << endl << endl;
	cout << "Now, to figure out edges of your graph:" << endl;
	cout << "-if there is a relationship between selected vertices, insert 1" << endl;
	cout << "-if there is no relationship between selected vertices, insert zero" << endl << endl;

	for (int i = 0; i < length; i++)
	{
		graph[i] = new int[length];

		for (int j = 0; j < length; j++)
		{
			if (j > i)
			{
				cout << "Edge " << (char)(97 + i) << " - " << (char)(97 + j) << ":" << endl;
				cin >> graph[i][j];
			}
		}
	}

	for (int i = 0; i < length; i++)
		for (int j = 0; j < length; j++)
			if (j > i)
				graph[j][i] = graph[i][j];
}

int Graph::min_distance(int vertice[], bool check[])
{
	int min = INT_MAX;
	int min_index;

	for (int i = 0; i<length; i++)
		if (check[i] == false && vertice[i] <= min)
		{
			min = vertice[i];
			min_index = i;
		}
	return min_index;
}

void Graph::dijkstra(int position)
{
	bool *check;
	int *vertice;

	check = new bool[length];
	vertice = new int[length];


	for (int i = 0; i < length; i++)
	{
		check[i] = false;
		vertice[i] = INT_MAX;
	}

	vertice[position] = 0;

	for (int i = 0; i < length - 1; i++)
	{
		int processed = min_distance(vertice, check);
		check[processed] = true;

		for (int j = 0; j < length; j++)
			if (!check[j] && graph[processed][j] && vertice[processed] + graph[processed][j] < vertice[j])
				vertice[j] = vertice[processed] + graph[processed][j];
	}

	cout << "Distance:" << endl << endl;

	for (int i = 0; i < length; i++)
	{
		cout << (char)(97 + position) << " - " << (char)(97 + i) << " : " << vertice[i] << endl;
	}

	cout << endl << "Press any key to go Back..." << endl;
	_getch();

	delete[] check;
	delete[] vertice;

	system("cls");

	cout << "If you need previous graph, insert <y>; else if you want new one, insert <n>" << endl;
	switch (_getch())
	{
	case 'y':
		first = false;
		break;

	case 'n':
		delete[] graph;
		first = true;
		break;

	default:
		break;
	}

	system("cls");
}

void Graph::bfs(int position)
{
	bool *check;
	int *breadth;
	int vertice = position;
	int counter = 1;

	check = new bool[length];
	breadth = new int[length];

	for (int i = 0; i < length; i++)
	{
		check[i] = false;
	}

	check[position] = true;
	breadth[0] = position;

	for (int i = 0; i < length - 1;)
	{
		for (int j = 0; j < length; j++)
		{
			if (!check[j] && graph[position][j])
			{
				check[j] = true;
				breadth[i + 1] = j;
				i++;
			}
		}

		position = breadth[counter];
		counter++;
	}

	cout << "BFS from <" << (char)(97 + vertice) << "> to other vertices is:" << endl;

	for (int i = 0; i < length; i++)
	{
		cout << (char)(97 + breadth[i]);

		if (i < length - 1)
			cout << " - ";
	}

	cout << endl << endl << "Press any key to go Back..." << endl;
	_getch();

	delete[] check;
	delete[] breadth;

	system("cls");

	cout << "If you need previous graph, insert <y>; else if you want new one, insert <n>" << endl;
	switch (_getch())
	{
	case 'y':
		first = false;
		break;

	case 'n':
		delete[] graph;
		first = true;
		break;

	default:
		break;
	}

	system("cls");
}

bool Graph::no_path(bool *check, int position)
{
	bool x = true;

	for (int j = 0; j < length; j++)
		if (!check[j] && graph[position][j] != 0)
			x = false;

	return x;
}

void Graph::dfs(int position)
{
	bool *check;
	int *depth;
	int vertice = position;
	int counter = 1;

	check = new bool[length];
	depth = new int[length];

	for (int i = 0; i < length; i++)
	{
		check[i] = false;
	}

	check[position] = true;
	depth[0] = position;

	for (int i = 0; i < length - 1;)
	{
		for (int j = 0; j < length; j++)
		{
			while (no_path(check, position))
			{
				position--;
			}

			if (!check[j] && graph[position][j])
			{
				check[j] = true;
				depth[i + 1] = j;
				position = j;
				i++;
				break;
			}
		}
	}

	cout << "DFS from <" << (char)(97 + vertice) << "> to other vertices is:" << endl;

	for (int i = 0; i < length; i++)
	{
		cout << (char)(97 + depth[i]);

		if (i < length - 1)
			cout << " - ";
	}

	cout << endl << endl << "Press any key to go Back..." << endl;
	_getch();

	delete[] check;
	delete[] depth;

	system("cls");

	cout << "If you need previous graph, insert <y>; else if you want new one, insert <n>" << endl;
	switch (_getch())
	{
	case 'y':
		first = false;
		break;

	case 'n':
		delete[] graph;
		first = true;
		break;

	default:
		break;
	}

	system("cls");
}

bool Graph::no_cycle(int **result, int position1, int position2)
{
	int counter = 1;
	int *breadth;
	bool *cycle;
	bool processed;
	bool answer = true;

	breadth = new int[length];
	cycle = new bool[length];

	for (int i = 0; i < length; i++)
		cycle[i] = false;

	breadth[0] = position1;
	cycle[position1] = true;

	for (int i = 0; i < length - 1;)
	{
		processed = false;

		for (int j = 0; j < length; j++)
		{

			if (!cycle[j] && result[position1][j])
			{
				processed = true;
				cycle[j] = true;
				breadth[i + 1] = j;
				i++;

				if (result[j][position2] || result[position2][j])
				{
					answer = false;
					break;
				}
			}
		}

		for (int j = 0; j < length; j++)
		{
			if (!cycle[j] && result[j][position1])
			{
				processed = true;
				cycle[j] = true;
				breadth[i + 1] = j;
				i++;

				if (result[j][position2] || result[position2][j])
				{
					answer = false;
					break;
				}
			}
		}

		if (!processed)
			break;

		position1 = breadth[counter];
		counter++;
	}

	delete[] breadth;
	delete[] cycle;

	return answer;
}

void Graph::kruskal()
{
	int position1, position2, min;
	int sum = 0;
	bool exit;

	int **result;
	bool **check;

	result = new int*[length];
	check = new bool*[length];

	for (int i = 0; i < length; i++)
	{
		result[i] = new int[length];
		check[i] = new bool[length];

		for (int j = 0; j < length; j++)
		{
			result[i][j] = 0;
			check[i][j] = false;
		}
	}

	for (int i = 0; i < length - 1;)
	{
		exit = false;

		for (int j = 0; j < length; j++)
		{
			for (int k = 0; k < length; k++)
				if (!check[j][k] && !exit && graph[j][k])
				{
					min = graph[j][k];
					position1 = j;
					position2 = k;
					exit = true;
					break;
				}

			if (exit == true)
				break;
		}

		for (int j = 0; j < length; j++)
			for (int k = 0; k < length; k++)
				if (!check[j][k] && graph[j][k] && graph[j][k] < min)
				{
					min = graph[j][k];
					position1 = j;
					position2 = k;
				}

		check[position1][position2] = true;

		if (no_cycle(result, position1, position2))
		{
			result[position1][position2] = min;
			i++;
		}
	}

	cout << "Kruskal's Minimum Spanning Tree contains this edges:" << endl;
	for (int i = 0; i < length; i++)
		for (int j = 0; j < length; j++)
			if (result[i][j])
				cout << (char)(97 + i) << " - " << (char)(97 + j) << endl;

	cout << endl;
	cout << "MST = ";
	for (int i = 0; i < length; i++)
		for (int j = 0; j < length; j++)
			sum += result[i][j];
	cout << sum << endl;

	cout << endl << "Press any key to go Back..." << endl;
	_getch();

	delete[] check;
	delete[] result;

	system("cls");

	cout << "If you need previous graph, insert <y>; else if you want new one, insert <n>" << endl;
	switch (_getch())
	{
	case 'y':
		first = false;
		break;

	case 'n':
		delete[] graph;
		first = true;
		break;

	default:
		break;
	}

	system("cls");
}

void Graph::prim(int position)
{
	bool **check;
	int **result;
	bool *processed;
	int *dfs;
	int vertice = position;
	int counter = 1;
	int sum = 0;

	check = new bool*[length];
	result = new int*[length];
	processed = new bool[length];
	dfs = new int[length];

	for (int i = 0; i < length; i++)
	{
		result[i] = new int[length];
		check[i] = new bool[length];

		for (int j = 0; j < length; j++)
		{
			result[i][j] = 0;
			check[i][j] = false;
		}
	}

	for (int i = 0; i < length; i++)
	{
		processed[i] = false;
	}

	processed[position] = true;
	dfs[0] = position;

	for (int i = 0; i < length - 1;)
	{
		for (int j = 0; j < length; j++)
		{
			while (no_path(processed, position))
			{
				position--;
			}

			if (!check[j] && graph[position][j])
			{

				check[position][j] = true;

				if (no_cycle(result, position, j))
				{
					result[position][j] = graph[position][j];
					processed[j] = true;
					dfs[i + 1] = j;
					position = j;
					i++;
					break;
				}
			}
		}
	}

	cout << "Prim's Minimum Spanning Tree from <" << (char)(97 + vertice) << "> to other vertices contains this edges:" << endl;
	for (int i = 0; i < length; i++)
		for (int j = 0; j < length; j++)
			if (result[i][j])
				cout << (char)(97 + i) << " - " << (char)(97 + j) << endl;

	cout << endl;
	cout << "MST = ";
	for (int i = 0; i < length; i++)
		for (int j = 0; j < length; j++)
			sum += result[i][j];
	cout << sum << endl;

	cout << endl << "Press any key to go Back..." << endl;
	_getch();

	delete[] processed;
	delete[] dfs;
	delete[] check;
	delete[] result;

	system("cls");

	cout << "If you need previous graph, insert <y>; else if you want new one, insert <n>" << endl;
	switch (_getch())
	{
	case 'y':
		first = false;
		break;

	case 'n':
		delete[] graph;
		first = true;
		break;

	default:
		break;
	}

	system("cls");
}

void Graph::floydwarshal()
{
	int **result;

	result = new int*[length];

	for (int i = 0; i < length; i++)
	{
		result[i] = new int[length];

		for (int j = 0; j < length; j++)
		{
			if (graph[i][j] == 0)
				result[i][j] = max;
			else
				result[i][j] = graph[i][j];
		}
	}

	for (int i = 0; i < length; i++)
		for (int j = 0; j < length; j++)
			result[j][i] = result[i][j];

	for (int k = 0; k < length; k++)
		for (int i = 0; i < length; i++)
			for (int j = 0; j < length; j++)
				if (result[i][k] + result[k][j] < result[i][j])
					result[i][j] = result[i][k] + result[k][j];

	cout << "Following matrix shows the shortest distances between every pair of vertices:" << endl << endl;
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (result[i][j] == max)
				cout << (char)(97 + i) << " - " << (char)(97 + j) << ": " << "INF" << "     ";
			else
				cout << (char)(97 + i) << " - " << (char)(97 + j) << ": " << result[i][j] << "       ";
		}
		cout << endl;
	}

	cout << endl << "Press any key to go Back..." << endl;
	_getch();

	delete[] result;

	system("cls");

	cout << "If you need previous graph, insert <y>; else if you want new one, insert <n>" << endl;
	switch (_getch())
	{
	case 'y':
		first = false;
		break;

	case 'n':
		delete[] graph;
		first = true;
		break;

	default:
		break;
	}

	system("cls");
}

void run()
{
	while (true)
	{
		system("color 3b");

		cout << endl << endl << endl << endl;
		cout << "               *******************************************************************************************" << endl;
		cout << "               *                                        <welcome>                                        *" << endl;
		cout << "               *                                   Discrete Algorithms                                   *" << endl;
		cout << "               *                                Please enter your option!                                *" << endl;
		cout << "               *                                                                                         *" << endl;
		cout << "               *                                                                                         *" << endl;
		cout << "               *  1) Insert a graph                                                                      *" << endl;
		cout << "               *  2) Dijkstra                                                                            *" << endl;
		cout << "               *  3) BFS (breadth first search)                                                          *" << endl;
		cout << "               *  4) DFS (depth first search)                                                            *" << endl;
		cout << "               *  5) Kruskal's Minimum Spanning Tree                                                     *" << endl;
		cout << "               *  6) Prim's Minimum Spanning Tree                                                        *" << endl;
		cout << "               *  7) Floyd warshal                                                                       *" << endl;
		cout << "               *  8) About programmer                                                                    *" << endl;
		cout << "               *  9) Exit                                                                                *" << endl;
		cout << "               *                                                                                         *" << endl;
		cout << "               *******************************************************************************************" << endl;

		switch (_getch())
		{
		case '1':

			system("color 5e");
			system("cls");

			Graph chart;
			int Size;

			cout << "How many vertices your graph includes?" << endl;
			cin >> Size;

			if (Size > 1)
			{
				chart.input(Size);

				system("cls");

				cout << "Graph provided! " << endl;
				Sleep(1200);
				system("cls");
			}

			else
			{
				system("cls");
				cout << "Sorry, the selected graph doesn't exist!" << endl;
				Sleep(1200);
				system("cls");
			}

			break;

		case '2':

			system("color 47");
			system("cls");

			if (first)
			{
				cout << "Sorry, you didn't enter graph!" << endl;
				cout << "Press any key to go back..." << endl;

				_getch();

				system("cls");
			}

			else
			{
				cout << "Insert name of vertice that you want to go <dijkstra>!" << endl;
				char x;
				int y;

				x = _getch();
				y = ((int)x) - 97;

				system("cls");

				chart.dijkstra(y);
			}

			break;

		case '3':

			system("color 61");
			system("cls");

			if (first)
			{
				cout << "Sorry, you didn't enter graph!" << endl;
				cout << "Press any key to go back..." << endl;

				_getch();

				system("cls");
			}

			else
			{
				cout << "Insert name of vertice that you want to go <BFS>!" << endl;
				char x;
				int y;

				x = _getch();
				y = ((int)x) - 97;

				system("cls");

				chart.bfs(y);
			}

			break;

		case '4':

			system("color 8f");
			system("cls");

			if (first)
			{
				cout << "Sorry, you didn't enter graph!" << endl;
				cout << "Press any key to go back..." << endl;

				_getch();

				system("cls");
			}

			else
			{
				cout << "Insert name of vertice that you want to go <DFS>!" << endl;
				char x;
				int y;

				x = _getch();
				y = ((int)x) - 97;

				system("cls");

				chart.dfs(y);
			}

			break;

		case '5':

			system("color ce");
			system("cls");

			if (first)
			{
				cout << "Sorry, you didn't enter graph!" << endl;
				cout << "Press any key to go back..." << endl;

				_getch();

				system("cls");
			}

			else
				chart.kruskal();

			break;

		case '6':

			system("color e0");
			system("cls");

			if (first)
			{
				cout << "Sorry, you didn't enter graph!" << endl;
				cout << "Press any key to go back..." << endl;

				_getch();

				system("cls");
			}

			else
			{
				cout << "Do you want to find MST from specific vertice or not? (y/n)" << endl;

				switch (_getch())
				{
				case 'y':

					system("cls");
					cout << "Insert name of vertice that you want to go <Prim>!" << endl;
					char x;
					int y;

					x = _getch();
					y = ((int)x) - 97;

					system("cls");

					chart.prim(y);

				case 'n':

					system("cls");
					chart.prim(0);

				default:
					break;
				}
			}

			break;

		case '7':

			system("color f1");
			system("cls");

			if (first)
			{
				cout << "Sorry, you didn't enter graph!" << endl;
				cout << "Press any key to go back..." << endl;

				_getch();

				system("cls");
			}

			else
				chart.floydwarshal();

			break;

		case '8':
			system("color 2e");
			system("cls");

			cout << endl;
			cout << "                                                 ********************" << endl;
			cout << "                                             ****************************" << endl;
			cout << "                                          *******                    *******" << endl;
			cout << "                                       *******   Discrete  Algorithms   *******" << endl;
			cout << "                                    *******   Programmed by Ali Tabaraei   *******" << endl;
			cout << "                                   ******    Collegiate Number: 95440185    *******" << endl;
			cout << "                                    *******      Telegram ID: a1i_tab      *******" << endl;
			cout << "                                      ********                          ********" << endl;
			cout << "                                         ************************************" << endl;
			cout << "                                            ******************************" << endl;
			cout << endl;
			cout << "                                               Thanks for attention...!" << endl;
			cout << "                                               Press any key to go Back" << endl;

			_getch();
			system("cls");

			break;

		case '9':
			system("color 07");
			system("cls");

			cout << "                                                      _____________" << endl;
			cout << "                                                     |  Good Luck  |" << endl;
			cout << "                                                     |  Have fun!  |" << endl;
			cout << "                                                      ------------- " << endl;

			Sleep(1000);
			exit(0);
			break;

		default:
			system("cls");

			cout << "Sorry! you entered wrong number..." << endl;
			cout << "try using 1 to 4 numbers for your option!" << endl;
			cout << endl;
			cout << "Press any key to go Back..." << endl;

			_getch();
			system("cls");

			break;
		}
	}
}

int main()
{
	run();
}
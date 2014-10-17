#include <list>
using namespace std;

#ifndef Graph_H
#define Graph_H

class Edges;

class NodeData
{
public:
	NodeData();
	NodeData(char el)
	{
		data = el;
	}
	char data;
	list<Edges> edges;
};

class Edges
{
public:
	Edges();
	Edges(int w)
	{
		weight = w;
	}
	int weight = 0;
	NodeData *edge = NULL;
};

class Graph
{
public:
	Graph();
	Graph(int num)
	{
		numNode = num;
	}
	void init()
	{
		for (int i = 0; i < numNode; i++)
		{
			graph.push_back(char_ascii++); // push the 'NodeData' into the graph
			arrPtr[i] = &graph.back(); // keep its address to a temporary array called 'arrPtr'
		}
	}
	void create_matrix()
	{
		for (int i = 0; i < numNode; i++)
		{
			matrix[i] = new int[numNode];
			for (int j = 0; j < numNode; j++)
			{
				cout << "Input matrix[" << i << "][" << j << "]: "; // ask user to input a data in 'matrix[i][j]'
				cin >> matrix[i][j]; // user have to input a weight in (numNode*numNode) times
			}
			cout << endl;
		}
	}
	void create_list()
	{
		int i = 0;
		for (list<NodeData>::iterator it = graph.begin(); it != graph.end(); it++) // iterate the graph
		{
			for (int j = 0; j < numNode; j++)
			{
				if (matrix[i][j] != 0) // just push a weighted 'Edges' into its list 'edge' EXCEPT: 0 (zero)
				{
					it->edges.push_back(matrix[i][j]);
					it->edges.back().edge = arrPtr[j]; // point that 'Edges' toward to the 'NodeData' that it connected with
				}
			}
			i++;
		}
	}
	void print_matrix()
	{
		cout << "-------------------------------\n\n";
		cout << "#### Adjacency matrix (array)\n\n";
		cout << "\t  ";
		for (int i = 0; i < numNode; i++)
		{
			cout << arrPtr[i]->data << " "; // print the first row headline: A B C ...
		}
		cout << endl;
		for (int i = 0; i < numNode; i++)
		{
			cout << "\t" << arrPtr[i]->data << " "; // print the first column: A B C ...
			for (int j = 0; j < numNode; j++)
			{
				cout << matrix[i][j]; // print all data in the adjacency matrix
				cout << " ";
			}
			cout << endl;
		}
	}
	void print_list()
	{
		cout << "\n-------------------------------\n\n";
		cout << "#### Adjacency linked list\n\n";
		for (int i = 0; i < numNode; i++) // iterate the graph
		{
			cout << "\t" << arrPtr[i]->data << " "; // print the name of each 'NodeData'
			for (list<Edges>::iterator it = arrPtr[i]->edges.begin(); it != arrPtr[i]->edges.end(); it++) // iterate the list 'edges'
			{
				cout << "[" << it->weight << "->" << it->edge->data << "] -> "; // print the list 'edges' of each 'NodeData'
			}
			cout << "|NULL|\n"; // the last node must point toward to NULL
		}
	}
	void check_graph()
	{
		status = false; // reset defalut 'status' to FALSE
		cout << "\n-------------------------------\n\n";
		cout << "#### Check the graph to answer;" << endl;

		cout << "\t1. Is it a multigraph?\t\t";
		cout << isMultigraph() << endl;

		cout << "\t2. Is it a pseudograph?\t\t";
		cout << isPseudograph() << endl;

		cout << "\t3. Is it a digraph?\t\t";
		cout << isDigraph() << endl;

		cout << "\t4. Is it a weighted graph?\t";
		cout << isWeightedgraph() << endl;

		cout << "\t5. Is it a complete graph?\t";
		cout << isCompletegraph() << endl;
	}
	bool isMultigraph()
	{
		status = false; // reset defalut 'status' to FALSE
		for (int i = 0; i < numNode; i++) // iterate the graph
		{
			for (list<Edges>::iterator it = arrPtr[i]->edges.begin(); it != arrPtr[i]->edges.end(); it++) // iterate the list 'edges'
			{
				list<Edges>::iterator tmp = it;
				for (list<Edges>::iterator it2 = ++tmp; it2 != arrPtr[i]->edges.end(); it2++)
				{
					if (it->edge == it2->edge)
					{
						status = true;
						break;
					}
				}
				if (status)
					break;
			}
			if (status)
				break;
		}
		return status;
	}
	bool isPseudograph()
	{
		status = false; // reset defalut 'status' to FALSE
		if (isMultigraph())
		{
			for (int i = 0; i < numNode; i++)
			{
				if (matrix[i][i] != 0)
				{
					status = true;
					break;
				}
			}
		}
		return status;
	}
	bool isDigraph()
	{
		status = false; // reset defalut 'status' to FALSE
		for (int i = 0; i < numNode; i++)
		{
			for (int j = 0; j < numNode; j++)
			{
				if (matrix[i][j] != matrix[j][i])
				{
					status = true;
					break;
				}
			}
			if (status)
				break;
		}
		return status;
	}
	bool isWeightedgraph()
	{
		status = false; // reset defalut 'status' to FALSE
		for (int i = 0; i < numNode; i++)
		{
			for (int j = 0; j < numNode; j++)
			{
				if (matrix[i][j] != 0)
				{
					status = true;
					break;
				}
			}
			if (status)
				break;
		}
		return status;
	}
	bool isCompletegraph()
	{
		status = true; // reset defalut 'status' to TURE
		for (int i = 0; i < numNode; i++)
		{
			for (int j = 0; j < numNode; j++)
			{
				if (matrix[i][j] == 0)
				{
					status = false;
					break;
				}
			}
			if (!status)
				break;
		}
		return status;
	}
	
	int numNode;
	list<NodeData> graph;
	int char_ascii = 65; // ini tialize char 'A' using ASCII = 65
	NodeData **arrPtr = new NodeData*[numNode]; // create an array to store pointers of each 'NodeData' i.e. A, B, C, ...
	int **matrix = new int*[numNode]; // create two dimentional dynamic array of adjacency matrix (SIZE = numNode*numNode)
	bool status = false; // a 'status' to check & answer questions
};

#endif // Graph_H

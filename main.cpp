#include <iostream>
#include <list>
#include "graph.h"
using namespace std;

void main()
{
	int numNode;
	cout << "How many nodes: ";
	cin >> numNode;

	cout << endl;

	Graph mygraph(numNode); // create a Graph's object called 'mygraph'
	mygraph.init(); // initialize a graph
	mygraph.create_matrix(); // ask user to input the whole weight, then create an adjacency matrix
	mygraph.create_list(); // convert the matrix to an adjacency linked list
	mygraph.print_matrix(); // print the matrix
	mygraph.print_list(); // print the linked list
	mygraph.check_graph(); // check the graph to answer questions including output results

	cout << endl;
}

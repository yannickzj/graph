#include <iostream>
#include "graph.h"

using namespace std;

int main(int argc, char** argv) {

	Graph m1;
	m1.retrieve("test1.txt");
	//Vertex* a = m1.getVertex("C1");
	//a->print();
	//int num = Graph::getNumRoad();
	//cout << num << endl;
	m1.store("output.txt");

	return 0;
}
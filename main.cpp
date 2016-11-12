#include <iostream>
#include "graph.h"
#include <queue>

using namespace std;


int main(int argc, char** argv) {

	Graph m1;
	m1.retrieve("test3.txt");

	//m1.trip("50/BearingerRd1231232", "AlbertSt/8", "shortest_path");
	//Vertex* a = m1.getVertex("C1");
	//a->print();
	//a = m1.getVertex("DC");
	//a->print();
	//a = m1.getVertex("C2");
	//a->print();
	//a = m1.getVertex("C3");
	//a->print();
	//a = m1.getVertex("58Cardill");
	//a->print();
	//Vertex* b = m1.getVertex("C2");
	//b->setPriority(150);
	//b->print();
	//int num = Graph::getNumRoad();
	//cout << num << endl;
	//vector<string>* r1 = m1.getRoad("goHome");
	//strPrint(*r1);
	//r1->push_back("hello");
	//vector<string>* r2 = m1.getRoad("goHome");
	//strPrint(*r2);
	//strPrint(*r1);
	m1.store("output.txt");

	return 0;
}
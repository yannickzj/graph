#include <iostream>
#include "graph.h"
#include <queue>

using namespace std;


int main(int argc, char** argv) {

	Graph m1;
	m1.retrieve("test2.txt");

	m1.trip("CLV", "340", "path1", SHORTEST);
	m1.trip("CLV", "340", "path1", FASTEST);
	m1.store("output.txt");

	return 0;
}
#include <iostream>
#include "graph.h"
#include <queue>

using namespace std;


int main(int argc, char** argv) {

	Graph m1;
	m1.retrieve("./test cases/test2.txt");
	m1.vertex("djfkdjfj");
	//m1.getV2("djfkd", "djfkdjl");
	m1.trip("CLV", "340", "path1", SHORTEST);
	m1.trip("CLV", "340", "path1", FASTEST);
	m1.store("output1.txt");

	return 0;
}
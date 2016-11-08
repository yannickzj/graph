#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "vertex_edge.h"
using namespace std;

class Graph {
private:
	string name;

	map<Vertex, vector<Edge>> adj_list;

	static int numVertex;

	static int numEdge;

public:
	Graph() {}

	~Graph() {}



	

};



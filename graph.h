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

		void addVertex(vertex_type type, string label) {}

		void addEdge(Vertex v1, Vertex v2, direction dir, int speed, double length) {}

		void edgeEvent(Edge edge, edge_event_type eventType) {}

		Path road(Edge edges[], string name) {}

		Path trip(Vertex fromVertex, Vertex toVertex) {}

		bool vertex(string label) {}

		void store(string filename) {}

		void retrieve(string filename) {}
		
};



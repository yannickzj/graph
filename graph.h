#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include "vertex_edge.h"
#include "stdlib.h"

#define BUFFERSIZE 256
#define VERTEX_STR "#vertex"
#define EDGE_STR "#edge"
#define PATH_STR "#path"
#define END_STR "#path"
#define PREV_DEFAULT ""

using namespace std;

struct Node
{
	Vertex* p;
	bool operator < (const Node& n) const {
		return this->p->getPriority() > n.p->getPriority();
	}
};



class Graph {
private:
	string name;

	map<string, vector<string> > adjOutList;

	map<string, vector<string> > adjInList;

	map<string, Vertex> vertexMap;

	map<string, Edge> edgeMap;

	map<string, vector<string> > roadMap;

	static int numVertex;

	static int numEdge;

	static int numRoad;

	vector<string> split(string str, string pattern) {
		
		string::size_type start = 0;
		string::size_type end;
		vector<string> result;
		str += pattern;
		string::size_type size = str.size();

		while (start < size) {
			end = str.find(pattern, start);
			if (end > start) {
				string substr = str.substr(start, end - start);
				result.push_back(substr);
			}
			start = end + pattern.size();
		}

		return result;
	}

	//void strPrint(vector<string> strList) {
	//	if (strList.size() == 0) {
	//		return;
	//	}
	//	cout << "(";
	//	for (int i = 0; i < strList.size() - 1; i++) {
	//		cout << strList[i] << ",";
	//	}
	//	cout << strList[strList.size() - 1] << ")" << endl;
	//}

	void retrieveVertex(string str) {
		//cout << str << endl;
		vector<string> strSplit = split(str, " ");
		string name = strSplit[0];
		int typeInt = atoi(strSplit[1].c_str());
		int x = atoi(strSplit[2].c_str());
		int y = atoi(strSplit[3].c_str());

		vertexType type;
		if (typeInt == 0 || typeInt == 1) {
			type = (vertexType)typeInt;
		}
		else {
			cout << "vertexType does not match in \"" << str << "\"!" << endl;
		}
		
		//cout << "name = " << name << "; type = " << type << "; x = " << x << "; y = " << y << endl;
		addVertex(name, type, x, y);
	}

	void retrieveEdge(string str) {
		//cout << str << endl;
		vector<string> strSplit = split(str, " ");
		string name = strSplit[0];
		string v1 = strSplit[1];
		string v2 = strSplit[2];
		int dirInt = atoi(strSplit[3].c_str());
		int speed = atoi(strSplit[4].c_str());
		int length = atoi(strSplit[5].c_str());
		int eventTypeInt = atoi(strSplit[6].c_str());

		dirType dir;
		if (dirInt == 0 || dirInt == 1 || dirInt == 2) {
			dir = (dirType)dirInt;
		}
		else {
			cout << "dirType does not match in \"" << str << "\"!" << endl;
		}

		eventType type;
		if (eventTypeInt == 0 || eventTypeInt == 1) {
			type = (eventType) eventTypeInt;
		}
		else {
			cout << "eventType does not match in \"" << str << "\"!" << endl;
		}

		//cout << "name = " << name << "; v1 = " << v1 << "; v2 = " << v2 << "; dir = " << dir << "; speed = " << speed << "; length = " << length << "; type = " << type << endl;
		addEdge(name, v1, v2, dir, speed, length, type);
	}

	void retrievePath(string str) {
		//cout << str << endl;
		vector<string> strSplit = split(str, " ");
		string name = strSplit[0];
		vector<string> edges;
		int len = strSplit.size();
		for (int i = 1; i < len; i++) {
			edges.push_back(strSplit[i]);
		}

		//cout << "name = " << name;
		//int num = edges.size();
		//for (int i = 0; i < num; i++) {
		//	cout << "; edge" << i << " = " << edges[i];
		//}

		//cout << endl;

		road(name, edges);
	}


public:
	Graph() {}

	Graph(string _name) : name(_name) {}

	~Graph() {}

	string getName() {
			return name;
	}

	Vertex* getVertex(string name) {
		if (containsVertex(name)) {
			return &vertexMap.at(name);
		}
		else {
			cout << "The graph does not contain the vertex \"" << name << "\"!" << endl;
			exit(1);
		}
	}

	Edge* getEdge(string name) {
		if (containsEdge(name)) {
			return &edgeMap.at(name);
		}
		else {
			cout << "The graph does not contain the edge \"" << name << "\"!" << endl;
			exit(1);
		}
	}

	vector<string> getAdjOutVertex(string v) {
		map<string, vector<string> >::iterator iter = adjOutList.find(v);
		vector<string> vertices;

		if (iter != adjOutList.end()) {
			int num = iter->second.size();
			for (int i = 0; i < num; i++) {
				vertices.push_back(findV2(v, iter->second[i]));
			}
		}
		return vertices;
	}

	vector<string> getAdjInVertex(string v) {
		map<string, vector<string> >::iterator iter = adjInList.find(v);
		vector<string> vertices;

		if (iter != adjInList.end()) {
			int num = iter->second.size();
			for (int i = 0; i < num; i++) {
				vertices.push_back(findV2(v, iter->second[i]));
			}
		}
		return vertices;
	}

	vector<string>* getRoad(string name) {
		if (containsRoad(name)) {
			return &roadMap.at(name);
		}
		else {
			cout << "The graph does not contain the road \"" << name << "\"!" << endl;
			exit(1);
		}
	}

	string findV2(string v1, string edge) {
		Edge* p = getEdge(edge);
		if (p->getV1() == v1) {
			return p->getV2();
		}
		else if (p->getV2() == v1) {
			return p->getV1();
		}
		else {
			cout << "the edge " << edge << " does not contain the vertex " << v1 << " !" << endl;
			exit(1);
		}
	}

	string findEdgeByVertex(string v1, string v2) {
		map<string, vector<string> >::iterator iter = adjOutList.find(v1);
		string edge;
		if (iter != adjOutList.end()) {
			int num = iter->second.size();
			for (int i = 0; i < num; i++) {
				string e = iter->second[i];
				if (findV2(v1, e) == v2) {
					edge = e;
				}
			}
		}
		return edge;
	}

	int getVertexPriority(string label) {
		Vertex* p = getVertex(label);
		return p->getPriority();
	}

	int getEdgeLength(string label) {
		Edge* p = getEdge(label);
		return p->getLength();
	}

	int getEdgeSpeed(string label) {
		Edge* p = getEdge(label);
		return p->getSpeed();
	}

	eventType getEdgeEvent(string label) {
		Edge* p = getEdge(label);
		return p->getType();
	}

	void addVertex(string label, vertexType type, int x, int y)
	{
		Vertex newVertex(label, type, x, y);
		vertexMap.insert(make_pair(label, newVertex));
		vector <string> newList1;
		vector <string> newList2;
		adjOutList.insert(make_pair(label, newList1));
		adjInList.insert(make_pair(label, newList2));
		numVertex++;
	}

	void addEdge(string label, string v1, string v2, dirType dir, int speed, int length, eventType type)
	{
		if (!containsVertex(v1) || !containsVertex(v2)) {
			cout << "error: edge vertex does not exist!" << endl;
			exit(1);
		}

		Edge newEdge(v1, v2, dir, speed, length, type);
		edgeMap.insert(make_pair(label, newEdge));

		if (dir == V1_TO_V2) {
			adjOutList[v1].push_back(label); 
			adjInList[v2].push_back(label);
		}
			
		if (dir == V2_TO_V1) {
			adjOutList[v2].push_back(label);
			adjInList[v1].push_back(label);
		}
			
		if (dir == BI_DIRECTIONAL)
		{
			adjOutList[v1].push_back(label);
			adjOutList[v2].push_back(label);
			adjInList[v1].push_back(label);
			adjInList[v2].push_back(label);
		}
		numEdge++;
	}

	void road(string name, vector<string> edges) {
		roadMap.insert(make_pair(name, edges));
		numRoad++;
	}

	void edgeEvent(string label, eventType type)
	{
		Edge* e = getEdge(label);
		e->setEventType(type);
	}

	void setVertexPriority(string label, int priority) {
		Vertex* p = getVertex(label);
		p->setPriority(priority);
	}

	void setVertexPrev(string label, string prev) {
		Vertex* p = getVertex(label);
		p->setPrev(prev);
	}

	bool trip(string fromVertex, string toVertex, string label) {
		// declaration
		priority_queue<Node> queue;
		vector<string> source;
		Node n;
		
		//initialize all the vertex priority values
		map<string, Vertex>::iterator iterVertex;
		for (iterVertex = vertexMap.begin(); iterVertex != vertexMap.end(); iterVertex++) {
			setVertexPriority(iterVertex->first, INT_MAX);
			setVertexPrev(iterVertex->first, PREV_DEFAULT);
		}

		//dijkstra algorithm
		setVertexPriority(fromVertex, 0);
		n.p = getVertex(fromVertex);
		queue.push(n);

		while (!queue.empty()) {
			string u = queue.top().p->getName();
			source.push_back(u);
			queue.pop();
			map<string, vector<string> >::iterator iter = adjOutList.find(u);
			vector<string> list = iter->second;
			int num = list.size();
			int priorityU = getVertexPriority(u);

			for (int i = 0; i < num; i++) {
				int length = getEdgeLength(list[i]);
				string v = findV2(u, list[i]);
				int priorityV = getVertexPriority(v);
				if (priorityV > priorityU + length) {
					setVertexPriority(v, priorityU + length);
					setVertexPrev(v, u);
					n.p = getVertex(v);
					queue.push(n);
				}
			}
		}

		// trace the path from fromVertex to toVertex
		vector<string> edges;
		vector<string>::iterator iterEdge;
		Vertex* trace = getVertex(toVertex);
		while (trace->getPrev() != PREV_DEFAULT) {
			string prev = trace->getPrev();
			string cur = trace->getName();
			string edge = findEdgeByVertex(prev, cur);

			iterEdge = edges.begin();
			edges.insert(iterEdge, edge);
			trace = getVertex(prev);
		}
		
		if (trace->getName() == fromVertex) {
			road(label, edges);
			return true;
		}

		return false;
	}

	bool vertex(string label) {}

	bool containsVertex(string label)
	{
		map<string, Vertex>::iterator it1;
		it1 = vertexMap.find(label);
		if (it1 != vertexMap.end())
		{
			return true;
		}
		return false;
	}

	bool containsEdge(string label)
	{
		map<string, Edge>::iterator it1;
		it1 = edgeMap.find(label);
		if (it1 != edgeMap.end())
		{
			return true;
		}
		return false;
	}

	bool containsRoad(string label) {
		map<string, vector<string> >::iterator it1;
		it1 = roadMap.find(label);
		if (it1 != roadMap.end())
		{
			return true;
		}
		return false;
	}

	void store(string filename) {
		ofstream outfile;
		outfile.open(filename.c_str());

		//store the vertex information
		outfile << "#vertex: name; vertex_type; x; y" << endl;
		map<string, Vertex>::iterator iterVertex;
		for (iterVertex = vertexMap.begin(); iterVertex != vertexMap.end(); iterVertex++) {
			outfile << iterVertex->first << " " << iterVertex->second.getType() << " " << iterVertex->second.getX() << " " << iterVertex->second.getY() << endl;
		}
		outfile << endl;

		//store the edge information
		outfile << "#edge: name; v1_name; v2_name; directional; speed; length; eventType" << endl;
		map<string, Edge>::iterator iterEdge;
		for (iterEdge = edgeMap.begin(); iterEdge != edgeMap.end(); iterEdge++) {
			outfile << iterEdge->first << " " << iterEdge->second.getV1() << " " << iterEdge->second.getV2() << " " << iterEdge->second.getDirection() << " " << iterEdge->second.getSpeed() << " " << iterEdge->second.getLength() << " " << iterEdge->second.getType() << endl;
		}
		outfile << endl;

		//store the path information
		outfile << "#path: name; edge1_name; edge2_name; ...; edgeN_name" << endl;
		map<string, vector<string> >::iterator iterRoad;
		for (iterRoad = roadMap.begin(); iterRoad != roadMap.end(); iterRoad++) {
			outfile << iterRoad->first;
			vector<string> edges = iterRoad->second;
			int num = edges.size();
			for (int i = 0; i < num; i++) {
				outfile << " " << edges[i];
			}
			outfile << endl;
		}
		outfile << endl;
		outfile << "#end" << endl;
		outfile.close();

	}

	void retrieve(string filename) {
		ifstream infile;
		infile.open(filename.c_str());

		if (!infile.good()) {
			cout << "cannot open the input file!" << endl;
		}

		char* buffer = new char[BUFFERSIZE];
		infile.getline(buffer, BUFFERSIZE);
		string s = buffer;

		while (!infile.eof() && s.find(END_STR) == string::npos) {

			if (s.find(VERTEX_STR) != string::npos) {
				infile.getline(buffer, BUFFERSIZE);
				s = buffer;

				while (s.find("#") == string::npos && !infile.eof()) {
					if (!s.empty()) {
						retrieveVertex(s);
					}
					infile.getline(buffer, BUFFERSIZE);
					s = buffer;
				}
				cout << endl;
			}

			if (s.find(EDGE_STR) != string::npos) {
				infile.getline(buffer, BUFFERSIZE);
				s = buffer;

				while (s.find("#") == string::npos && !infile.eof()) {
					if (!s.empty()) {
						retrieveEdge(s);
					}
					infile.getline(buffer, BUFFERSIZE);
					s = buffer;
				}
				cout << endl;
			}

			if (s.find(PATH_STR) != string::npos) {
				infile.getline(buffer, BUFFERSIZE);
				s = buffer;

				while (s.find("#") == string::npos && !infile.eof()) {
					if (!s.empty()) {
						retrievePath(s);
					}
					infile.getline(buffer, BUFFERSIZE);
					s = buffer;
				}
				cout << endl;
			}

			infile.getline(buffer, BUFFERSIZE);
			s = buffer;
				
		}

		delete buffer;

		infile.close();
	}
		
	static int getNumVertex() {
		return numVertex;
	}

	static int getNumEdge() {
		return numEdge;
	}

	static int getNumRoad() {
		return numRoad;
	}

};

int Graph::numEdge = 0;

int Graph::numVertex = 0;

int Graph::numRoad = 0;

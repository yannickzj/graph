#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "vertex_edge.h"

#define BUFFERSIZE 256
#define VERTEX_STR "#vertex"
#define EDGE_STR "#edge"
#define PATH_STR "#path"
#define END_STR "#path"

using namespace std;

class Graph {
private:
	string name;

	map<string, vector<string> > adjList;

	map<string, Vertex> vertexMap;

	map<string, Edge> edgeMap;

	map<string, vector<string>> roadMap;

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
		double x = atof(strSplit[2].c_str());
		double y = atof(strSplit[3].c_str());

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
		double length = atof(strSplit[5].c_str());
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

	void addVertex(string label, vertexType type, double x, double y)
	{
		Vertex newVertex(label, type, x, y);
		vertexMap.insert(make_pair(label, newVertex));
		vector <string> newList;
		adjList.insert(make_pair(label, newList));
		numVertex++;
	}

	void addEdge(string label, string v1, string v2, dirType dir, int speed, double length, eventType type)
	{
		if (!containsVertex(v1) || !containsVertex(v2)) {
			cout << "error: edge vertex does not exist!" << endl;
			exit(1);
		}

		Edge newEdge(v1, v2, dir, speed, length, type);
		edgeMap.insert(make_pair(label, newEdge));

		if (dir == V1_TO_V2)
			adjList[v1].push_back(label);
		if (dir == V2_TO_V1)
			adjList[v2].push_back(label);
		if (dir == BI_DIRECTIONAL)
		{
			adjList[v1].push_back(label);
			adjList[v2].push_back(label);
		}
		numEdge++;
	}

	void edgeEvent(string label, eventType type)
	{
		Edge* e = getEdge(label);
		e->setEventType(type);
	}

	void road(string name, vector<string> edges) {
		roadMap.insert(make_pair(name, edges));
		numRoad++;
	}

	void trip(string fromVertex, string toVertex, string label) {}

	bool vertex(string label)
	{
		std::map<string, vector<string> >::iterator it1;
		it1 = adjList.find(label);
		if (it1 != adjList.end())
		{
			return true;
		}
		return false;
	}

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

	void store(string filename) {
		ofstream outfile;
		outfile.open(filename);

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
		map<string, vector<string>>::iterator iterRoad;
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
		infile.open(filename);

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

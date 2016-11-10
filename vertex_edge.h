#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum vertexType { POINT_OF_INTEREST = 0, INTERSECTION = 1 };
enum dirType { BI_DIRECTIONAL = 0, V1_TO_V2 = 1, V2_TO_V1 = 2 };
enum eventType { OPEN = 0, CLOSE = 1 };

class Vertex
{

private:
	string name;

	vertexType type;

	double x;

	double y;

public:


	//Vertex(string _name = "unnamed", vertexType _type = POINT_OF_INTEREST) :name(_name), type(_type) {}

	Vertex(string _name = "unnamed", vertexType _type = POINT_OF_INTEREST, double _x = 0, double _y = 0) :name(_name), type(_type), x(_x), y(_y) {}

	~Vertex() {}

	//Vertex(const Vertex& p)  // copy constructor
	//{
	//	*this = p;
	//}

	//Vertex & operator = (const Vertex& p)    //operator =
	//{
	//	if (this == &p) return(*this);
	//	name = p.name;
	//	type = p.type;
	//	x = p.x;
	//	y = p.y;
	//	return (*this);
	//}

	string getName()
	{
		return name;
	}

	vertexType getType()
	{
		return type;
	}

	void setType(vertexType _type) {
		type = _type;
	}

	void print() {
		cout << "vertex: name = " << name << ", type = " << type << ", x = " << x << ", y = " << y << endl;
	}


};

class Edge
{
private:
	string v1;

	string v2;

	dirType dir;

	int speed;

	double length;

	eventType type;

public:
	Edge(string _v1, string _v2, dirType _dir = BI_DIRECTIONAL, int _speed = 30, double _length = 10, eventType _type = OPEN) :
		v1(_v1), v2(_v2), dir(_dir), speed(_speed), length(_length), type(_type) {}

	~Edge() {}

	//Edge(const Edge& p)  // copy constructor
	//{
	//	*this = p;
	//}

	//Edge & operator = (const Edge& p)    //operator =
	//{
	//	if (this == &p) return(*this);
	//	v1 = p.v1;
	//	v2 = p.v2;
	//	dir = p.dir;
	//	speed = p.speed;
	//	length = p.length;
	//	type = p.type;
	//	return (*this);
	//}

	void setEventType(eventType _type)
	{
		type = _type;
	}

	void setSpeed(int _speed)
	{
		speed = _speed;
	}

	string getV1(void)
	{
		return v1;
	}

	string getV2(void)
	{
		return v2;
	}

	dirType getDirection(void)
	{
		return dir;
	}

	int getSpeed(void)
	{
		return speed;
	}

	double getLength(void)
	{
		return length;
	}

	eventType getType(void)
	{
		return type;
	}

	void print() {
		cout << "edge: v1 = " << v1 << ", v2 = " << v2 << ", dir = " << dir << ", speed = " << speed << ", length = " << length << ", eventType = " << type << endl;
	}
};


class Path {

private:
	vector<Edge> path;

	double distance;

public:

	Path() {}

	Path(Edge edges[]) {
		int len = sizeof(edges) / sizeof(Edge);
		for (int i = 0; i < len; i++) {
			path.push_back(edges[i]);
		}
	}

	~Path() {}

};
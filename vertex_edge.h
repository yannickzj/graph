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

	int x;

	int y;

	int priority;

	string prev;

public:

	Vertex(string _name = "unnamed", vertexType _type = POINT_OF_INTEREST, int _x = 0, int _y = 0, int _priority = INT_MAX, string _prev = "") :name(_name), type(_type), x(_x), y(_y), priority(_priority), prev(_prev) {}

	~Vertex() {}

	Vertex(const Vertex& p)  // copy constructor
	{
		*this = p;
	}

	Vertex & operator = (const Vertex& p)    //operator =
	{
		if (this == &p) return(*this);
		name = p.name;
		type = p.type;
		x = p.x;
		y = p.y;
		priority = p.priority;
		prev = p.prev;
		return (*this);
	}

	bool operator < (Vertex& v2) {     // operator <
		return this->priority < v2.priority;
	}

	string getName()
	{
		return name;
	}

	vertexType getType()
	{
		return type;
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	int getPriority() {
		return priority;
	}

	string getPrev() {
		return prev;
	}

	void setPriority(int _priority) {
		priority = _priority;
	}

	void setType(vertexType _type) {
		type = _type;
	}

	void setPrev(string _prev) {
		prev = _prev;
	}

	void print() {
		cout << "vertex: name = " << name << ", type = " << type << ", x = " << x << ", y = " << y << ", priority = " << priority << endl;
	}


};

class Edge
{
private:
	string v1;

	string v2;

	dirType dir;

	int speed;

	int length;

	eventType type;

public:
	Edge(string _v1, string _v2, dirType _dir = BI_DIRECTIONAL, int _speed = 30, int _length = 10, eventType _type = OPEN) :
		v1(_v1), v2(_v2), dir(_dir), speed(_speed), length(_length), type(_type) {}

	~Edge() {}

	Edge(const Edge& p)  // copy constructor
	{
		*this = p;
	}

	Edge & operator = (const Edge& p)    //operator =
	{
		if (this == &p) return(*this);
		v1 = p.v1;
		v2 = p.v2;
		dir = p.dir;
		speed = p.speed;
		length = p.length;
		type = p.type;
		return (*this);
	}

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

	int getLength(void)
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


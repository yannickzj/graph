#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum vertex_type {POINT_OF_INTEREST = 0, INTERSECTION = 1};
enum direction {BI_DIRECTIONAL = 0, V1_TO_V2 = 1, V2_TO_V1 = 2};
enum edge_event_type{OPEN = 0, CLOSE = 1};

class Vertex
{

private:
        string name;

        vertex_type type;


public:
        double x;

        double y;

        Vertex(string _name = "unnamed" , vertex_type _type = POINT_OF_INTEREST):name(_name),type(_type){}

        ~Vertex(){}

        Vertex(const Vertex& p)  // copy constructor
        {
            *this = p;
        }

        Vertex & operator = (const Vertex& p)    //operator =
        {
            if(this == &p) return(*this);
            name = p.name;
            type = p.type;
            return (*this);
        }

        string getName(void)
        {
            return name;
        }

        vertex_type getType(void)
        {
            return type;
        }



};

class Edge
{
private:
        Vertex v1;

        Vertex v2;

        direction dir;

        int speed;

        double length;

        edge_event_type type;

public:
        Edge(Vertex _v1 , Vertex _v2, direction _dir = BI_DIRECTIONAL, int _speed = 50, double _length = 0, edge_event_type _type = OPEN):
        v1(_v1),v2(_v2),dir(_dir),speed(_speed),length(_length),type(_type){}

        ~Edge(){}

        Edge(const Edge& p)  // copy constructor
        {
            *this = p;
        }

        Edge & operator = (const Edge& p)    //operator =
        {
            if(this == &p) return(*this);
            v1 = p.v1;
            v2 = p.v2;
            dir = p.dir;
            speed = p.speed;
            length = p.length;
            type = p.type;
            return (*this);
        }

        void setEventType (edge_event_type _type)
        {
           type = _type;
        }

        void setSpeed(int _speed)
        {
            speed = _speed;
        }

        Vertex getV1(void)
        {
            return v1;
        }

        Vertex getV2(void)
        {
            return v2;
        }

        direction getDirection(void)
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

        edge_event_type getType(void)
        {
            return type;
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
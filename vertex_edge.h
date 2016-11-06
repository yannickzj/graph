#include <iostream>
#include <string>
using namespace std;

enum vertex_type {point_of_interest = 0, intersection = 1};
enum direction {bi_directional = 0, v1_to_v2 = 1, v2_to_v1 = 2};
enum edge_event_type{open = 0, close = 1};

class vertex
{

private:
        string name;

        vertex_type type;

        double x;

        double y;
public:
        vertex(string _name = "unnamed" , vertex_type _type = point_of_interest, double _x = 0, double _y = 0):name(_name),type(_type),x(_x),y(_y){}

        ~vertex(){}

        vertex(const vertex& p)  // copy constructor
        {
            *this = p;
        }

        vertex & operator = (const vertex& p)    //operator =
        {
            if(this == &p) return(*this);
            name = p.name;
            type = p.type;
            x = p.x;
            y = p.y;
            return (*this);
        }

};

class edge
{
private:
        vertex v1;

        vertex v2;

        direction dir;

        int speed;

        double length;

        edge_event_type type;

public:

};

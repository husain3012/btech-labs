#include <iostream>
#include <math.h>
using namespace std;

class Point
{
    int x, y;

public:
    friend void getLength(Point p1, Point p2);
    friend class Line;
    Point(){
        x = 0;
        y = 0;
    }
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    void setX(int x)
    {
        this->x = x;
    }
    void setY(int y)
    {
        this->y = y;
    }
};

class Line
{
    Point p1, p2;
    public:
    Line(Point p1, Point p2)
    {
        this->p1 = p1;
        this->p2 = p2;
    }
    void setP1(Point p1)
    {
        this->p1 = p1;
    }
    void setP2(Point p2)
    {
        this->p2 = p2;
    }
    double getLength(Point p1, Point p2)
    {
        int x = p1.x - p2.x;
        int y = p1.y - p2.y;
        return sqrt(x*x + y*y);
    }

};


int main(){
    Point p1(1, 1);
    Point p2(2, 2);
    Line l(p1, p2);
    cout << l.getLength(p1, p2);
    return 0;
}
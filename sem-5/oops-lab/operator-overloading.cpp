#include <bits/stdc++.h>
using namespace std;

class Point
{
    int x;
    int y;

public:
    Point(int x1, int y1) : x(x1), y(y1) {}
    Point() : x(INT8_MAX), y(INT8_MAX) {}
    bool operator&&(Point p)
    {
        return (x && p.x) && (y && p.y);
    }
    bool operator||(Point p)
    {
        return (x || p.x) || (y || p.y);
    }
    bool operator!()
    {
        return !x && !y;
    }
    friend ostream &operator<<(ostream &out, const Point &c);
    friend istream &operator>>(istream &in, Point &c);
};

class Points
{
    vector<Point> points;

public:
    Points(vector<Point> points) : points(points) {}
    Points() {}
    Point operator[](int i)
    {
        if (i < 0 || i >= points.size())
        {
            cout << "Index out of bounds" << endl;
            return Point();
        }
        return points[i];
    }
    void *operator new(size_t size)
    {
        cout << "Allocating " << size << " bytes" << endl;
        void *p = malloc(size);
        return p;
    }
    void operator delete(void *p)
    {
        cout << "Freeing memory" << endl;
        free(p);
    }
    void push_back(Point p)
    {
        points.push_back(p);
    }
    friend ostream &operator<<(ostream &out, const Points &c);
};

ostream &operator<<(ostream &out, const Point &c)
{
    out << "(" << c.x << ", " << c.y << ")";
    return out;
}
ostream &operator<<(ostream &out, const Points &p)
{
    for (auto i : p.points)
    {
        out << i << " ";
    }
    return out;
}
istream &operator>>(istream &in, Point &c)
{
    in >> c.x >> c.y;
    return in;
}

int main()
{
    // menu based program to demonstrate operator overloading
    Points *p = new Points();
    int choice;
    while (true)
    {
        cout << "1. Add point" << endl;
        cout << "2. Get point" << endl;
        cout << "3. Logical AND" << endl;
        cout << "4. Logical OR" << endl;
        cout << "5. Logical NOT" << endl;
        cout << "6. Display all points" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            Point point;
            cout << "Enter point: ";
            cin >> point;
            p->push_back(point);
            break;
        }
        case 2:
        {
            int index;
            cout << "Enter index: ";
            cin >> index;
            cout << p->operator[](index) << endl;
            break;
        }
        case 3:
        {
            int index1, index2;
            cout << "Enter index1: ";
            cin >> index1;
            cout << "Enter index2: ";
            cin >> index2;
            cout << (p->operator[](index1) && p->operator[](index2)) << endl;
            break;
        }
        case 4:
        {
            int index1, index2;
            cout << "Enter index1: ";
            cin >> index1;
            cout << "Enter index2: ";
            cin >> index2;
            cout << (p->operator[](index1) || p->operator[](index2)) << endl;
            break;
        }
        case 5:
        {
            int index;
            cout << "Enter index: ";
            cin >> index;
            cout << (!p->operator[](index)) << endl;
            break;
        }
        case 6:
        {
            cout << *p << endl;
            break;
        }
        case 7:
        {
            delete p;
            exit(0);
        }
        default:
            cout << "Invalid choice" << endl;
        }
    }
    return 0;
}
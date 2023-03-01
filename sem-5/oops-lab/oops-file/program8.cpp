#include <bits/stdc++.h>
using namespace std;
class Base
{
public:
    Base()
    {

        cout << "//Base Class Constructor" << endl;
    }
    virtual ~Base()
    {
        cout << "//Base Class Destructor" << endl;
    }
    virtual void pureVirtual() = 0;
};
class Derived : public Base
{
public:
    Derived()
    {
        cout << "//Derived Class Constructor" << endl;
    }
    virtual ~Derived()
    {
        cout << "//Derived Class Destructor" << endl;
    }
    void pureVirtual() override
    {
        cout << "//Pure Virtual Function, overriden in base class." << endl;
    }
    friend ostream &operator<<(ostream &os, const Derived &d);
};
ostream &operator<<(ostream &out, const Derived &d)
{

    out << "//This function is overloaded using friend function." << endl;
    return out;
}
int main()
{
    cout << "Creating Derived Class Object, with Base class pointer:" << endl;
    Base *b1 = new Derived();
    cout << "-----------------------------------------------" << endl
         << endl;
    cout << "Calling Pure Virtual Function" << endl;
    b1->pureVirtual();
    cout << "-----------------------------------------------" << endl
         << endl;
    cout << "Creating Derived Class Object, with Derived class pointer:" << endl;
    Derived *d1 = new Derived();
    cout << "-----------------------------------------------" << endl
         << endl;
    cout << "Calling Pure Virtual Function" << endl;
    d1->pureVirtual();
    cout << "-----------------------------------------------" << endl
         << endl;
    Derived *d2 = new Derived();
    Base *b2 = d2;
    cout << "Deleting object:" << endl;
    delete b2;
    cout << "-----------------------------------------------" << endl;
    cout << "Overloading << operator using friend function:" << endl;
    Derived d3;
    cout << d3 << endl;
    cout << "-----------------------------------------------" << endl;
}
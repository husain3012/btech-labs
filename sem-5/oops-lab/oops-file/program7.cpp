#include <bits/stdc++.h>
using namespace std;

int conversion_rate = 70;

class Rupee
{

public:
    double value;
    Rupee(double value)
    {
        this->value = value;
    }
    void display(ostream &out = cout)
    {
        out << "Rs. " << value;
    }
};

class Dollar
{

public:
    double value;
    Dollar(double value)
    {
        this->value = value;
    }
    Dollar(Rupee r)
    {
        this->value = r.value / conversion_rate;
    }
    operator Rupee()
    {
        return Rupee(value * conversion_rate);
    }

    void display(ostream &out = cout)
    {
        out << "$ " << value;
    }
};

ostream &operator<<(ostream &stream, Dollar m)
{
    m.display(stream);
    return stream;
}
ostream &operator<<(ostream &stream, Rupee m)
{
    m.display(stream);
    return stream;
}

int main()
{
    Rupee r1(100);
    Dollar d1 = r1;
    cout << "Rupee: " << r1 << ", Dollar: " << d1 << endl;
    Dollar d2(2.5);
    Rupee r2 = d2;
    cout << "Dollar: " << d2 << ", Rupee: " << r2 << endl;
}
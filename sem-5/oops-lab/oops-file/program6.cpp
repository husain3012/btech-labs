#include <bits/stdc++.h>
using namespace std;

class Complex
{
    int x;
    int y;

public:
    Complex(int r, int i)
    {
        x = r;
        y = i;
    }
    Complex()
    {
        x = 0;
        y = 0;
    }
    Complex operator+(Complex c)
    {
        Complex temp;
        temp.x = x + c.x;
        temp.y = y + c.y;
        return temp;
    }
    Complex operator-(Complex c)
    {
        Complex temp;
        temp.x = x - c.x;
        temp.y = y - c.y;
        return temp;
    }
    Complex operator*(Complex c)
    {
        Complex temp;
        temp.x = x * c.x - y * c.y;
        temp.y = x * c.y + y * c.x;
        return temp;
    }

    Complex operator+=(Complex c)
    {
        x += c.x;
        y += c.y;
        return *this;
    }
    Complex operator-=(Complex c)
    {
        x -= c.x;
        y -= c.y;
        return *this;
    }
    Complex operator*=(Complex c)
    {
        int temp = x;
        x = x * c.x - y * c.y;
        y = temp * c.y + y * c.x;
        return *this;
    }
    Complex operator/=(Complex c)
    {
        int temp = x;
        x = (x * c.x + y * c.y) / (c.x * c.x + c.y * c.y);
        y = (y * c.x - temp * c.y) / (c.x * c.x + c.y * c.y);
        return *this;
    }
    void display(ostream &out = cout)
    {
        out << "(" << x << " + i" << y << ")";
    }
    void read(istream &in = cin)
    {
        in >> x >> y;
    }
};
ostream &operator<<(ostream &stream, Complex m)
{
    m.display(stream);
    return stream;
}
istream &operator>>(istream &stream, Complex &m)
{
    m.read(stream);
    return stream;
}
int main()
{
    Complex c1;
    Complex c2;
    Complex c3;
    cout << "Enter complex number 1 (a b): ";
    cin >> c1;
    cout << "Enter complex number 2 (a b): ";
    cin >> c2;
    c3 = c1 + c2;
    cout << c1 << " + " << c2 << " = " << c3 << endl;
    c3 = c1 - c2;
    cout << c1 << " - " << c2 << " = " << c3 << endl;
    c3 = c1 * c2;
    cout << c1 << " * " << c2 << " = " << c3 << endl;
    c3 += c1;
    cout << c3 << " += " << c1 << " = " << c3 << endl;
    c3 -= c1;
    cout << c3 << " -= " << c1 << " = " << c3 << endl;
    c3 *= c1;
    cout << c3 << " *= " << c1 << " = " << c3 << endl;
    c3 /= c1;
    cout << c3 << " /= " << c1 << " = " << c3 << endl;

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

class Time
{
    int hour;
    int minute;

public:
    Time()
    {
        hour = 0;
        minute = 0;
    }
    Time(int hour, int minute)
    {
        this->hour = hour;
        this->minute = minute;
    }
    Time operator+(Time t)
    {
        Time temp;
        temp.hour = hour + t.hour;
        temp.minute = minute + t.minute;
        if (temp.minute >= 60)
        {
            temp.hour++;
            temp.minute -= 60;
        }
        return temp;
    }
    void display(ostream &out = cout)
    {
        out << hour << ":" << minute;
    }
    void read(istream &in = cin)
    {

        in >> hour >> minute;
    }
};

ostream &operator<<(ostream &stream, Time m)
{
    m.display(stream);
    return stream;
}
istream &operator>>(istream &stream, Time &m)
{
    m.read(stream);
    return stream;
}

int main()
{
    Time t1;
    Time t2;
    cout << "Enter time 1 (hh mm): ";
    cin >> t1;
    cout << "Enter time 2 (hh mm): ";
    cin >> t2;
    Time t3 = t1 + t2;
    cout << t1 << " + " << t2 << " = " << t3 << endl;
    return 0;
}
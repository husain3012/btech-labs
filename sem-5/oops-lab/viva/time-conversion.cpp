#include <bits/stdc++.h>

using namespace std;

class Clock12;

class Clock24
{
    int hh;
    int mm;
    int ss;

public:
    Clock24(int h, int m, int s)
    {
        hh = h % 24;
        mm = m % 60;
        ss = s % 60;
    }
    operator Clock12();
    void display()
    {
        cout << hh << " : " << mm << " : " << ss;
    }
};

class Clock12
{
    int hh;
    int mm;
    int ss;
    bool isAM;

public:
    Clock12(int h, int m, int s, string half = "am")
    {
        hh = h % 12;
        mm = m % 60;
        ss = s % 60;
        isAM = half == "am";
    }
    operator Clock24();
    void display()
    {
        cout << hh << " : " << mm << " : " << ss << (isAM ? " am" : " pm");
    }
};

Clock24::operator Clock12()
{
    int hh = ((this->hh - 12) % 12 + 12) % 12;
    return Clock12(hh, this->mm, this->ss, this->hh < 12 ? "am" : "pm");
}
Clock12::operator Clock24()
{
    int hh = this->hh + (this->isAM ? 0 : 12);
    hh = hh % 24;
    return Clock24(hh, this->mm, this->ss);
}

ostream &operator<<(ostream &out, Clock12 t)
{
    t.display();
    return out;
}
ostream &operator<<(ostream &out, Clock24 t)
{
    t.display();
    return out;
}

int main()
{
    Clock24 t1(15, 36, 50);
    Clock12 t2 = t1;
    Clock12 t3(10, 36, 40, "am");
    Clock24 t4 = t3;
    cout << "24 to 12\t" << t1 << "\t => \t" << t2 << endl
         << endl;
    cout << "12 to 24\t" << t3 << "\t => \t" << t4 << endl
         << endl;
    // MENU BASED
    while (true)
    {
        cout << "1. 24 to 12" << endl
             << "2. 12 to 24" << endl
             << "3. Exit" << endl;
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1)
        {
            int hh, mm, ss;
            cout << "Enter time (hh mm ss) ";
            cin >> hh >> mm >> ss;
            Clock24 t1(hh, mm, ss);
            Clock12 t2 = t1;
            cout << t1 << " => " << t2 << endl;
        }
        else if (choice == 2)
        {
            int hh, mm, ss;
            string half;
            cout << "Enter time (hh mm ss am) ";
            cin >> hh >> mm >> ss >> half;
            Clock12 t1(hh, mm, ss, half);
            Clock24 t2 = t1;
            cout << t1 << " => " << t2 << endl;
        }
        else
        {
            break;
        }
    }
}
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

class Figure
{
private:
    int size;
    string ch;
    string result;

public:
    friend class Animate;
    Figure(int size)
    {
        this->size = size;
        this->ch = "*";
        result = "";
    }
    Figure(int size, string ch)
    {
        this->size = size;
        this->ch = ch;
        result = "";
    }
    inline void setSize(int size)
    {
        this->size = size - 2;
    }
    inline void setSymbol(string symb)
    {
        this->ch = symb;
    }

    void print()
    {

        // for (int i = 0; i < 2 * size; i++)
        //     cout << "==";
        cout << "\n";
        result = "\n";

        for (int i = -1; i < size; i++)
        {

            for (int j = 0; j < (size - i); j++)
            {

                cout << " ";
                result += " ";
            }
            cout << ch;

            for (int j = 0; j <= 2 * i; j++)
            {
                cout << " ";
                result += " ";
            }
            if (i != -1)
            {
                cout << ch;
                result += ch;
            }

            cout << "\n";
            result += "\n";
        }

        for (int i = 0; i <= size + 1; i++)
        {

            for (int j = 0; j < i; j++)
            {
                cout << " ";
                result += " ";
            }
            cout << ch;
            result += ch;

            for (int j = 0; j <= 2 * (size - i); j++)
            {
                cout << " ";
                result += " ";
            }
            if (i != size + 1)
                cout << ch;
                result += ch;


            cout << "\n";
        }
        // for (int i = 0; i < 2 * size; i++)
        //     cout << "==";
        cout << "\n";
    }
};

class Animate : public Figure
{
    int iterations;
    int minSize;
    int maxSize;

public:
    Animate(int iterations, int minSize, int maxSize) : Figure(maxSize)
    {
        this->iterations = iterations;
        this->minSize = minSize;
        this->maxSize = maxSize;
    }
    void animate()
    {
        for (int i = 0; i < iterations; i++)
        {
            for (int sz = minSize; sz <= maxSize; sz++)
            {
                this->size = sz;
                system("cls");
                this->print();
            }
            for (int sz = maxSize; sz >= minSize; sz--)
            {
                this->size = sz;
                system("cls");
                this->print();
            }
        }
    }
};

void animateDemo(int minS = 5, int maxS = 10)
{
    int itr;
    cout<<"Enter iterations: ";
    cin>>itr;
    Animate a(itr, minS, maxS);
    a.animate();
}

int main()
{
    Figure fig(9);
    int choice = 0, size;
    string s;
    while (choice != 5)
    {
        cout << "\n1. Set Size\n2. Set Symbol\n3. Print\n4. Play Animation\n5. Exit\nEnter: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter size: ";
            cin >> size;
            fig.setSize(size);
            break;
        case 2:
            cout << "Enter Symbol: ";
            cin >> s;
            fig.setSymbol(s);
            break;
        case 3:
            fig.print();
            break;

        case 4:
            animateDemo();
            break;
        case 5:
            return 0;

        default:
            break;
        }
    }
    return 0;
}
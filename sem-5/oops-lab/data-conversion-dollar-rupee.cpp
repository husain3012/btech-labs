#include <bits/stdc++.h>
using namespace std;



float dollar_to_rupee = 74.5;

class Dollar;   
class Rupee
{
    float amount;

public:
    float getAmount()
    {
        return amount;
    }
    Rupee(float amount)
    {
        this->amount = amount;
    }
    // operator Dollar();
};

class Dollar
{
    float amount;

public:
    float getAmount()
    {
        return amount;
    }
    Dollar(float amount)
    {
        this->amount = amount;
    }
    operator Rupee()
    {
        return Rupee(this->amount * dollar_to_rupee);
    }
    Dollar(Rupee r){
        amount = r.getAmount()/dollar_to_rupee;


    }
};

// Rupee::operator Dollar()
// {
//     return Dollar(this->amount / dollar_to_rupee);
// }

int main()
{

    int choice = -1;
    float amount;
    while (choice)
    {
        cout << "1. Rupee to Dollar" << endl;
        cout << "2. Dollar to Rupee" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "Enter amount in Rupee: ";
            cin >> amount;
            Rupee r(amount);
            Dollar d = r;
            cout << "Amount in Dollar: " << d.getAmount() << endl;
            break;
        }
        case 2:
        {
            cout << "Enter amount in Dollar: ";
            cin >> amount;
            Dollar d(amount);
            Rupee r = d;
            cout << "Amount in Rupee: " << r.getAmount() << endl;
            break;
        }
        default:
            choice = 0;
        }
    }

}
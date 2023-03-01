#include <bits/stdc++.h>
using namespace std;

class Account
{
public:
    int accountNumber;
    string name;
    int balance;

public:
    void display()
    {
        cout << "---------------ACCOUNT INFO-------------" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Balance: " << balance << endl;
        cout << "----------------------------------------" << endl;
    }
};

class AccountBook
{
    Account accounts[1000];
    Account nullAccount;
    int accountCount;

public:
    AccountBook()
    {
        accountCount = 0;
        nullAccount.accountNumber = -1;
        nullAccount.name = "";
        nullAccount.balance = 0;
    }
    void addAccount(int accountNumber, string name, int balance)
    {
        accounts[accountCount].accountNumber = accountNumber;
        accounts[accountCount].name = name;
        accounts[accountCount].balance = balance;
        accountCount++;
    }

    void displayAll()
    {
        for (int i = 0; i < accountCount; i++)
        {
            cout << "--------------------------------" << endl;
            cout << "Account Number: \t" << accounts[i].accountNumber << endl;
            cout << "Name: \t" << accounts[i].name << endl;
            cout << "Balance: \t" << accounts[i].balance << endl;
            cout << "--------------------------------" << endl
                 << endl;
        }
    }
    Account &operator[](int index)
    {
        if (index < accountCount)
        {
            return accounts[index];
        }
        else
        {
            cout << "Invalid index" << endl;
            return nullAccount;
        }
    }
    int getAccountCount()
    {
        return accountCount;
    }
    Account &search(string name)
    {
        for (int i = 0; i < accountCount; i++)
        {
            if (accounts[i].name == name)
            {
                return accounts[i];
            }
        }
        cout << "Account not found" << endl;
        return nullAccount;
    }
    Account &search(int accountNumber)
    {
        for (int i = 0; i < accountCount; i++)
        {
            if (accounts[i].accountNumber == accountNumber)
            {
                return accounts[i];
            }
        }
        cout << "Account not found" << endl;
        return nullAccount;
    }
};

int main()
{
    AccountBook accounts;

    accounts.addAccount(1122, "Husain", 1000);
    accounts.addAccount(1223, "Sarfraz", 2000);
    accounts.addAccount(1324, "Atufa", 3000);
    accounts.addAccount(1425, "Ayaz", 3000);
    accounts.addAccount(1526, "Sparsh", 3000);
    cout << "Accessing account using [] operator" << endl;
    for (int i = 0; i < accounts.getAccountCount(); i++)
    {
        accounts[i].display();
    }
    cout << "Search by name" << endl;
    accounts.search("Sarfraz").display();
    cout << "Search by account number" << endl;
    accounts.search(1425).display();
}
#include <bits/stdc++.h>
using namespace std;

class User
{
protected:
    string name;
    string address;

public:
    User()
    {
        name = "";
        address = "";
    }
    User(string name, string address)
    {
        this->name = name;
        this->address = address;
    }
    void display()
    {
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
    }
};

class Student : public User
{
    int percentage;
    int marks;

public:
    Student()
    {
        percentage = 0;
    }
    Student(string name, string address, int percentage) : User(name, address)
    {
        this->percentage = percentage;
    }
    void display()
    {
        cout << "--------------------------------" << endl;
        cout << "Name: \t" << name << endl;
        cout << "Address: \t" << address << endl;
        cout << "Percentage: \t" << percentage << endl;
        cout << "--------------------------------" << endl
             << endl;
    }
    void readData()
    {
        cout << "Enter name: ";
        getchar();
        getline(cin, name);
        cout << "Enter address: ";
        getline(cin, address);
        cout << "Enter percentage: ";
        cin >> percentage;
    }
};

class Staff : public User
{
    int salary;

public:
    Staff()
    {
        salary = 0;
    }
    Staff(string name, string address, int salary) : User(name, address)
    {
        this->salary = salary;
    }
    void display()
    {
        cout << "--------------------------------" << endl;
        cout << "Name: \t" << name << endl;
        cout << "Address: \t" << address << endl;
        cout << "Salary: \t" << salary << endl;
        cout << "--------------------------------" << endl
             << endl;
    }
    void readData()
    {
        cout << "Enter name: ";
        getchar();
        getline(cin, name);
        cout << "Enter address: ";
        getline(cin, address);
        cout << "Enter salary: ";
        cin >> salary;
    }
};

int main()
{
    vector<Student> students;
    vector<Staff> staffs;
    int choice;
    while (true)
    {
        cout << "--------------MENU--------------" << endl;
        cout << "1. Add student" << endl;
        cout << "2. Display all students" << endl;
        cout << "3. Add staff" << endl;
        cout << "4. Display all staff" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            Student s;
            s.readData();
            students.push_back(s);
            break;
        }
        case 2:
        {
            for (int i = 0; i < students.size(); i++)
            {
                students[i].display();
            }
            break;
        }
        case 3:
        {
            Staff s;
            s.readData();
            staffs.push_back(s);
            break;
        }
        case 4:
        {
            for (int i = 0; i < staffs.size(); i++)
            {
                staffs[i].display();
            }
            break;
        }
        case 5:
        {
            exit(0);
        }
        default:
        {
            cout << "Invalid choice" << endl;
            break;
        }
        }
    }
    return 0;
}
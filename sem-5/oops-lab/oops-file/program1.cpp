#include <bits/stdc++.h>
using namespace std;
class Student
{
    string name;
    int enrollId;
    int marks;

public:
    Student()
    {
        name = "";
        enrollId = 0;
        marks = 0;
    }
    Student(string s_name, int s_enrollId, int s_marks)
    {
        name = s_name;
        enrollId = s_enrollId;
        marks = s_marks;
    }
    void display()
    {
        cout << "--------------------------------" << endl;
        cout << "Name: \t" << name << endl;
        cout << "Enroll ID: \t" << enrollId << endl;
        cout << "Marks: \t" << marks << endl;
        cout << "--------------------------------" << endl
             << endl;
    }
    void read()
    {
        cout << "Enter name: ";
        getchar();
        getline(cin, name);
        cout << "Enter enroll ID: ";
        cin >> enrollId;
        cout << "Enter marks: ";
        cin >> marks;
    }
};

int main()
{
    vector<Student> students;
    int choice;
    while (true)
    {
        cout << "--------------MENU--------------" << endl;
        cout << "1. Add student" << endl;
        cout << "2. Display all students" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            Student s;
            s.read();
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
            exit(0);
        }
        default:
        {
            cout << "Invalid choice" << endl;
        }
        }
    }
}
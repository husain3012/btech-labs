#include <bits/stdc++.h>
using namespace std;

string RandomString(int ch)
{
    char alpha[32] = {'a', 'b', 'c', 'd', 'e', 'f', 'g',
                      'h', 'i', 'j', 'k', 'l', 'm', 'n',
                      'o', 'p', 'q', 'r', 's', 't', 'u',
                      'v', 'w', 'x', 'y', 'z'};
    string result = "";
    for (int i = 0; i < ch; i++)
        result = result + alpha[rand() % 32];

    return result;
}

class Student
{
    int marks;
    string name;
    string email;
    bool hosteler;

public:
    int id;
    Student()
    {
        id = rand() % 1000;
        marks = 0;
        name = "";
        email = "";
        hosteler = false;
    }
    Student(int s_id, string s_name, string s_email, int s_marks, bool s_hosteler)
    {
        id = s_id;
        name = s_name;
        email = s_email;
        marks = s_marks;
        hosteler = s_hosteler;
    }

    bool isName(string x)
    {
        return x == this->name;
    }
    void getData()
    {
        int tmp_id, tmp_marks;
        string tmp_name, tmp_email;
        cout << "ID: ";
        cin >> tmp_id;
        cout << "Name: ";
        getchar();
        getline(cin, tmp_name);
        cout << "Email: ";
        cin >> tmp_email;
        cout << "Marks: ";
        cin >> tmp_marks;
        id = tmp_id;
        name = tmp_name;
        email = tmp_email;
        marks = tmp_marks;
    }
    void showData()
    {
        cout << id << "\t\t" << name << "\t\t" << email << "\t\t" << marks << "\n";
    }
    void update()
    {
        int tmp_marks;
        string tmp_name, tmp_email;
        cout << "Name: (" << name << ") ";
        getchar();
        getline(cin, tmp_name);
        cout << "Email: (" << email << ") ";
        cin >> tmp_email;
        cout << "Marks: (" << marks << ") ";
        cin >> tmp_marks;
        name = tmp_name;
        email = tmp_email;
        marks = tmp_marks;
    }
};
class Classroom
{
    Student students[10000];
    int numberOfStudents;

public:
    Classroom()
    {
        numberOfStudents = 0;
    }
    void addStudent()
    {
        students[numberOfStudents].getData();
        numberOfStudents++;
    }
    void deleteStudent()
    {
        int tmp_id;
        cout << "Enter ID: ";
        cin >> tmp_id;
        for (int i = 0; i < numberOfStudents; i++)
        {
            if (tmp_id == students->id)
            {
                swap(students[i], students[numberOfStudents]);
                // delete students[numberOfStudents];
                numberOfStudents--;
            }
        }
    }
    Student *findById(int id = -1)
    {
        int temp_id;
        if (id == -1)
        {
            cout << "Enter ID: ";
            cin >> temp_id;
        }
        cout << "Searching for ID: " << temp_id << endl;
        for (int i = 0; i <= numberOfStudents; i++)
        {
            cout << students[i].id << endl;
            if (id == students[i].id)
            {
                cout << "Found" << endl;
                students[i].showData();
                return &students[i];
            }
        }
        return &students[9999];
    }
    void searchByName()
    {
        string query;
        getchar();
        getline(cin, query);
        for (int i = 0; i <= numberOfStudents; i++)
        {
            if (students[i].isName(query))
            {
                cout << "ID\t\tNAME\t\t\tEMAIL\t\t\tMARKS" << endl;

                students[i].showData();
            }
        }
    }
    void update()
    {
        int temp_id;
        cin >> temp_id;
        this->findById(temp_id)->update();
    }
    void displayAll()
    {
        cout << "\n------------------------------------------------------------------------------\n";
        cout << "ID\t\tNAME\t\t\t\tEMAIL\t\t\tMARKS";
        cout << "\n------------------------------------------------------------------------------\n";
        for (int i = 0; i < numberOfStudents; i++)
        {
            students[i].showData();
        }
    }
    void populate(int n)
    {

        for (int i = 0; i < n; i++)
        {
            students[i] = Student(i, RandomString(12), RandomString(12), rand() % 100, rand() % 2);
        }
        numberOfStudents = n;
    }
};
int main()
{
    srand(time(NULL));
    Classroom students;
    int temp_id;

    int choice = -1;
    while (choice != 0)
    {
        cout << "\n============MENU============\n";
        cout << "1. Add Student\n2. Update Student\n3. Delete Student\n4. Find By ID\n5. Search By Name\n6. Display All\n7. Add random Students\n0. Exit\n";
        cout << "\n============================\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            students.addStudent();
            break;
        case 2:
            students.update();
            break;
        case 3:
            students.deleteStudent();
            break;
        case 4:
            students.findById()->showData();
            break;
        case 5:
            students.searchByName();
            break;
        case 6:
            students.displayAll();
            break;
        case 7:
            students.populate(100);
            break;

        default:
            break;
        }
    }
}
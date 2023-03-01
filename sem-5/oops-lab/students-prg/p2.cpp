#include <iostream>
#include <string>
using namespace std;
class Student
{
    int id, marks;
    string name;
    string email;
    bool hosteler;

public:
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
        cout << id << "\t" << name << "\t" << email << "\t" << marks << "\n";
    }
};
int main()
{
    Student s1, s2, s3;
    s1.getData();
    s2.getData();
    s3.getData();
    s1.showData();
    s2.showData();
    s3.showData();
}
#include <bits/stdc++.h>
using namespace std;
class Student
{
public:
    string name;
    int roll_no;
    Student(string name = "", int roll_no = 0)
    {
        this->name = name;
        this->roll_no = roll_no;
    }
    void printInfo()
    {
        cout << roll_no << ": " << name;
    }
};
class Branch
{
    vector<Student> students;

public:
    string title;
    Branch(string title, vector<Student> students = {})
    {
        this->title = title;
        this->students = students;
    }
    Student findByRollNo(int roll_no)
    {
        for (Student s : students)
            if (roll_no == s.roll_no)
                return s;
        return Student();
    }
    void addStudent()
    {
        string s_name;
        int s_roll_no;
        cout << "Enter Name: ";
        getchar();
        getline(cin, s_name);
        cout << "Enter Roll No: ";
        cin >> s_roll_no;
        Student student(s_name, s_roll_no);
        if (findByRollNo(student.roll_no).roll_no)
        {
            cout << "-> Student with the roll no: " << student.roll_no << " already exists!\n";
            return;
        }
        students.push_back(student);
        cout << "-> Successfully added!\n";
    }
    void getAllStudents()
    {
        cout << "---------Students of " << this->title << "---------\n";
        for (Student s : students)
        {
            cout << "[" << s.roll_no << "]\t" << s.name << "\n";
        }
        cout << "-------------------------------\n";
    }
    bool hasStudents(){
        return students.size()>0;
    }
};

class Faculty
{
    int selectedBranch;
    vector<Branch> branches;

public:
    string name;
    Faculty(string name, vector<Branch> branches = {})
    {
        this->name = name;
        this->branches = branches;
        selectedBranch = branches.size() - 1;
    }
    void createBranch()
    {
        string title;
        cout << "Enter branch name: ";
        getchar();
        getline(cin, title);
        branches.push_back(Branch(title));
        selectedBranch = branches.size() - 1;
        cout << "-> Created Successfully, currently selected: " << branches[selectedBranch].title << '\n';
    }
    void selectBranch()
    {
        int selectBranchTemp;
        cout << "Select classroom: ";
        cin >> selectBranchTemp;
        selectedBranch = selectBranchTemp - 1;
        cout << "-> Selected: " << branches[selectedBranch].title << '\n';
    }
    Branch &branch()
    {
        return branches[selectedBranch];
    }
    bool hasBranches()
    {
        return branches.size() > 0;
    }
    void getAllBranches()
    {
        cout << "------Branches-------\n";
        for (int i = 0; i < branches.size(); i++)
        {
            cout << i + 1 << ". " << branches[i].title << "\n";
        }
        cout << "---------------------\n";
    }
};

int main()
{
    // create faculty object here
    Faculty faculty("FET");
    // __________________________

    cout << "\n========================================\n";
    cout << "=> Welcome to " << faculty.name << "!";
    cout << "\n========================================\n";
    int choice = -1;
    while (choice != 0)
    {
        // =========MENU=========
        cout << "------------MENU------------\n";
        cout << "1. Create Branch\n";
        if (faculty.hasBranches())
        {
            cout << "2. List all branches\n";
            cout << "3. Select Branch\n";
            cout << "4. Add student to " << faculty.branch().title << "\n";
            if (faculty.branch().hasStudents())
            {
                cout << "5. Get all students of " << faculty.branch().title << "\n";
            }
        }
        cout << "0. Exit\n";
        cout << "----------------------------\n";
        // ======================

        cout << "=> ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            faculty.createBranch();
            break;
        case 2:
            faculty.getAllBranches();
            break;

        case 3:
            faculty.selectBranch();
            break;

        case 4:
            faculty.branch().addStudent();
            break;
        case 5:
            faculty.branch().getAllStudents();
            break;
        case 0:
            cout << "Bye!";
            return 0;
        default:
            cout << "\nEnter a valid choice!\n";
            break;
        }
    }
}
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class DFA
{
    int initialState;
    vector<int> finalStates;
    vector<vector<int>> transition_table;

public:
    void read_dfa(string file_name)
    {
        ifstream file;
        string line;
        file.open(file_name);
        int i = 0;

        while (getline(file, line))
        {
            if (i == 0)
            {
                initialState = stoi(line);
                cout<<initialState;
            }
            else if (i == 1)
            {
                int x = 0;
                string num = "";
                while (line[x] != 0)
                {
                    if (line[x] == ' ')
                    {
                        finalStates.push_back(stoi(num));
                        num = "";
                        x++;
                        continue;
                    }
                    num += line[x++];
                }
                finalStates.push_back(stoi(num));
            }
            else
            {
                vector<int> temp;
                int x = 0;
                string num = "";
                while (line[x] != 0)
                {
                    if (line[x] == ' ')
                    {
                        temp.push_back(stoi(num));
                        num = "";
                        x++;
                        continue;
                    }
                    num += line[x++];
                }
                temp.push_back(stoi(num));
                transition_table.push_back(temp);
            }
            i++;
        }
        file.close();
    }

    bool test(string s)
    {
        int curr = initialState;
        int size = s.size(), k = 0;
        if (s == "")
        {
            for (auto fs : finalStates)
            {
                if (fs == 0)
                    return true;
            }
            return false;
        }
        while (curr != -1 && k < size)
        {
            cout << curr << "->";
            string t = "";
            t += s[k++];
            curr = transition_table[curr][stoi(t)];
        }

        for (int i = 0; i < finalStates.size(); i++)
        {
            if (curr == finalStates[i])
            {
                return true;
            }
        }
        return false;
    }

    void print()
    {
        cout << "Initial State: " << initialState;
        cout << "\nFinal States: ";
        for (auto fs : finalStates)
        {
            cout << fs << ", ";
        }
        cout << endl;
    }
};

int main()
{

    DFA dfa;
    dfa.read_dfa("dfa.txt");
    dfa.print();
    string inp;
    while (true)
    {
        cout << "Enter input: ";
        getline(cin, inp);
        if (inp == "exit")
            return 0;
        if (dfa.test(inp))
        {
            cout << "Accepted :)\n";
        }
        else
        {
            cout << "Rejected :(\n";
        }
    }

    return 0;
}

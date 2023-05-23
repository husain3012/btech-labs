#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
vector<string> split(string s, char delem = ' ')
{
    vector<string> tokenized;
    string temp = "";
    for (char x : s)
    {
        if (x == delem)
        {
            tokenized.push_back(temp);
            temp = "";
        }
        else
        {
            temp += x;
        }
    }
    tokenized.push_back(temp);
    return tokenized;
}

class Moore
{
    int initialState;
    vector<pair<vector<int>, string>> transition_table;

public:
    Moore()
    {
        initialState = -1;
    }
    void read_dfa(string file_name)
    {
        ifstream file;
        string line;
        file.open(file_name);
        int i = 0;

        while (getline(file, line))
        {

            if (initialState == -1)
            {
                initialState = stoi(line);
            }

            else
            {
                vector<string> temp = split(line);
                // print tokenized string
                for (auto x : temp)
                {
                    cout << x << ", ";
                }
                cout << endl;
                pair<vector<int>, string> current_state;
                for (int j = 0; j < temp.size() - 1; j++)
                {
                    current_state.first.push_back(stoi(temp[j]));
                }
                current_state.second = temp.back();
                transition_table.push_back(current_state);
            }
        }
        file.close();
    }

    void process(string input)
    {
        int current_state = initialState;
        string result = "";
        int i = 0;
        do
        {
            int new_state = transition_table[current_state].first[input[i] - '0'];
            cout << new_state << " -> ";
            result += transition_table[current_state].second;
            current_state = new_state;
            i++;
        } while (i < input.size() and current_state != -1);
        cout<<"\nOutput: "<<result;
    }

    void print()
    {
        // pretty print the transition table
        cout << "Initial state: " << initialState << endl;
        cout << "Transition table: " << endl;
      

        for (int i = 0; i < transition_table.size(); i++)
        {
            cout << i << "\t||\t";
            for (int j = 0; j < transition_table[i].first.size(); j++)
            {
                cout << transition_table[i].first[j] << "\t|\t";
            }
            cout << "\t||\t" << transition_table[i].second << endl;
        }
    }
};

int main()
{

    Moore moore;
    moore.read_dfa("moore.txt");
    moore.print();
    string inp;
    while (true)
    {
        cout << "\nEnter input: ";
        getline(cin, inp);
        if(inp=="exit") return 0;
        moore.process(inp);
    }

    return 0;
}

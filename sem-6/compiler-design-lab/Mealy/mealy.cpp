#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int stringToInt(string line)
{
    int i = 0;
    int num = 0;
    while (line[i] != 0)
    {
        if (line[0] == '-')
        {
            return -1;
        }
        num *= 10;
        num += (line[i] - '0');
        i++;
    }
    return num;
}
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

class Mealy
{
    int initialState;
    vector<vector<pair<int, string>>> transition_table;

public:
    void read(string file_name)
    {
        ifstream file;
        string line;
        file.open(file_name);
        int i = 0;

        while (getline(file, line))
        {
            if (i == 0)
            {
                initialState = stringToInt(line);
            }
            else
            {
                vector<pair<int, string>> temp;
                vector<string> tokenized_line = split(line);
                int number_of_input_symbols = tokenized_line.size() / 2;
                for (int j = 0; j < tokenized_line.size(); j += 2)
                {
                    int to_state = stringToInt(tokenized_line[j]);
                    // cout<<"At state "<<i-1<<" and input "<<tokenized_line[j+1][0]<<" to "<<stringToInt(tokenized_line[j])<<endl;
                    if (to_state == -1)
                    {
                        temp.push_back({-1, ""});
                        continue;
                    }
                    else
                    {
                        string output = tokenized_line[j + 1];
                        temp.push_back({to_state, output});
                    }
                }
                transition_table.push_back(temp);
            }
            i++;
        }
        file.close();
    }

    void process(string s)
    {
        int curr = initialState;
        int size = s.size(), k = 0;
        string output = "";

        while (k < size)
        {
            pair<int, string> current_result = transition_table[curr][s[k] - '0'];

            if (current_result.first == -1)
            {

                // continue;
            }
            else
            {
                curr = current_result.first;
                output += current_result.second;

                cout << "(from: " << curr << ", to: " << current_result.first << ", output: " <<current_result.second << ") =>";
            }
            k++;
        }

        cout <<"\nOutput: "<<output;
    }

    void print()
    {
        for (int i = 0; i < transition_table.size(); i++)
        {
            cout << "At state " << i;
            for (int j = 0; j < transition_table[i].size(); j++)
            {
                cout << " and input " << j << " to state " << transition_table[i][j].first << " and output " << transition_table[i][j].second << endl;
            }
            cout << endl;
        }
    }
};

int main()
{

    Mealy mealy;
    mealy.read("mealy.txt");
    mealy.print();
    string inp;
    while (true)
    {
        cout << "\nEnter input: ";
        getline(cin, inp);
        if (inp == "exit")
            return 0;
        cout <<endl;
        mealy.process(inp);
    }

    return 0;
}

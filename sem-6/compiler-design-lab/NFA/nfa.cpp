#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_set>
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

class NFA
{
    vector<vector<vector<int>>> nfa;
    int initialState;
    unordered_set<int> finalStates;
    vector<vector<int>> dfa;

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
                
            }
            i++;
        }
        file.close();
    }
};
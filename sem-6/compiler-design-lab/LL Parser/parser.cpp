#include <bits/stdc++.h>
#include "./first-and-follow.hpp"
using namespace std;

class LL_Parser : public First_and_Follow
{

    unordered_map<char, unordered_map<char, string>> parsing_table;

public:
    LL_Parser() : First_and_Follow()
    {
    }

    void generateParseTable()
    {
        for (auto production_pairs : productions)
        {
            char parent = production_pairs.first;
            vector<string> prods = production_pairs.second;
            for (string prod : prods)
            {
                string firsts = firstOf(prod);
                for (char c : firsts)
                {
                    if (c != epsilon)
                    {
                        parsing_table[parent][c] = prod;
                    }
                    else
                    {
                        string follows = followOf(parent);
                        for (char f : follows)
                        {
                            parsing_table[parent][f] = epsilon;
                        }
                    }
                }
            }
        }
    }

    void printTable()
    {

        vector<char> terminals_arr;
        vector<char> nonTerminals_arr;
        for (char c : terminals)
        {
            if (c == epsilon)
                continue;
            terminals_arr.push_back(c);
        }
        sort(terminals_arr.begin(), terminals_arr.end());

        terminals_arr.push_back(endSymbol);

        nonTerminals_arr.push_back(startSymbol);
        for (char c : nonTerminals)
        {
            if(c==startSymbol) continue;
            nonTerminals_arr.push_back(c);
        }

        // ========================= printing =========================
        cout << "\t";
        for (char t : terminals_arr)
        {
            if (t == epsilon)
                continue;
            cout << t << "\t";
        }
        cout << "\n";
        for (char c : nonTerminals_arr)
        {
            cout << c << "\t";
            for (char t : terminals_arr)
            {
                if (t == epsilon)
                    continue;

                if (parsing_table[c].find(t) == parsing_table[c].end())
                {
                    cout << " - ";
                }
                else
                {
                    cout << parsing_table[c][t];
                }
                cout << "\t";
            }
            cout << "\n";
        }
        // =============================================================
    }

    void writeToFile()
    {

        vector<char> terminals_arr;
        vector<char> nonTerminals_arr;
        for (char c : terminals)
        {
            if (c == epsilon)
                continue;
            terminals_arr.push_back(c);
        }
        sort(terminals_arr.begin(), terminals_arr.end());

        terminals_arr.push_back(endSymbol);
        nonTerminals_arr.push_back(startSymbol);
        for (char c : nonTerminals)
        {
            if(c==startSymbol) continue;
            nonTerminals_arr.push_back(c);
        }
        // writing to file
        ofstream file;
        file.open("parser.txt");

        for (char t : terminals_arr)
        {
            if (t == epsilon)
                continue;
            file << t << " ";
        }
        file << "\n";
        for (int i = 0; i < nonTerminals_arr.size(); i++)
        {
            char c = nonTerminals_arr[i];
            file << c << " ";
            for (char t : terminals_arr)
            {
                if (t == epsilon)
                    continue;

                if (parsing_table[c].find(t) == parsing_table[c].end())
                {
                    file << "-";
                }
                else
                {
                    file << parsing_table[c][t];
                }
                file << " ";
            }
            if (i < nonTerminals_arr.size() - 1)
                file << "\n";
        }
    }
};

int main()
{

    LL_Parser parser;
    parser.read();
    parser.generateParseTable();
    parser.printTable();
    parser.writeToFile();
}
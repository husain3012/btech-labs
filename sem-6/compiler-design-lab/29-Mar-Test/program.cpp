/*
Q. WAP to verify input against an LL(1) Parser.
Read LL Parser from a file and take input from the user.
*/

#include <bits/stdc++.h>

using namespace std;

vector<string> tokenize(string s, char delem = ' ')
{
    vector<string> tokenized;
    string temp = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == delem)
        {
            tokenized.push_back(temp);
            temp = "";
        }
        else
        {
            temp += s[i];
        }
    }
    if (temp != "")
    {
        tokenized.push_back(temp);
    }
    return tokenized;
}

class LL_Parser
{
    vector<char> terminals;
    vector<char> nonTerminals;
    map<char, vector<string>> transitions;
    char endSymbol;
    char epsilon;

    string getTransitionFromTable(char nonTerminal, char terminal)
    {

        int i = find(terminals.begin(),
                     terminals.end(), terminal) -
                terminals.begin();

        if (i == terminals.size())
            return "-";
        return transitions[nonTerminal][i];
    }

public:
    LL_Parser(char endSymbol = '$', char epsilon = '#')
    {
        this->endSymbol = endSymbol;
        this->epsilon = epsilon;
    }
    void readFile()
    {
        int i = 0;
        ifstream file;
        file.open("input.txt");
        string line;
        while (getline(file, line))
        {
            // read terminals if i  == 0
            if (i == 0)
            {
                vector<string> terms = tokenize(line);
                for (int i = 0; i < terms.size(); i++)
                {
                    terminals.push_back(terms[i][0]);
                }
            }
            else
            {
                // read table entries
                vector<string> row = tokenize(line);
                char var = row[0][0];
                nonTerminals.push_back(var);

                for (int i = 1; i < row.size(); i++)
                {
                    transitions[var].push_back(row[i]);
                }
            }

            i++;
        }
    }

    void print()
    {

        cout << "\t";
        for (int i = 0; i < terminals.size(); i++)
        {
            cout << terminals[i] << "\t";
        }
        cout << endl;
        for (int i = 0; i < nonTerminals.size(); i++)
        {
            char var = nonTerminals[i];
            cout << var << "\t";
            for (int j = 0; j < transitions[var].size(); j++)
            {
                cout << transitions[var][j] << "\t";
            }
            cout << endl;
        }
    }

    bool test(string input)
    {

        int i = 0;
        string st = "$";
        st.push_back(nonTerminals[0]);

        while (i < input.length())
        {

            // -------- Printing---------

            cout << endl
                 << st;

                cout << "\t\t";
            
            for (int k = 0; k < i; k++)
            {
                cout << input[k];
            }
            cout << "[" << input[i] << "]";
            for (int k = i + 1; k < input.length(); k++)
            {
                cout << input[k];
            }

            cout << "\t\t";
            // ---------------------------

            char c = input[i];
            char top = st.back();

            if (!isupper(top))
            {
                if (top != c)
                    return false;
                i++;
                cout << "POP";
                st.pop_back();
            }
            else
            {

                string nextProd = getTransitionFromTable(top, c);

                if (nextProd == "-")
                {
                    return false;
                }
                else if (nextProd[0] == epsilon)
                {
                    st.pop_back();
                    cout << "POP";
                }
                else
                {

                    st.pop_back();

                    for (int j = nextProd.length() - 1; j >= 0; j--)
                    {
                        st.push_back(nextProd[j]);
                    }
                }
                cout << "\t" << top << "->" << nextProd;
            }
        }
        // handle endSymbol transition
        while (st.back() != endSymbol)
        {

            char top = st.back();
            string nextProd = getTransitionFromTable(top, endSymbol);
            if (nextProd == "-")
                return false;
            cout << endl
                 << st << "\t\t" << input << "[]\t\t";

            if (nextProd[0] == epsilon)
            {
                cout << "POP";
                st.pop_back();
            }
            cout << "\t" << top << "->" << nextProd;
        }
        cout << endl
             << st << endl;

        return st.back() == endSymbol;
    }
};

int main()
{
    LL_Parser parser;
    parser.readFile();
    parser.print();
    while (true)
    {
        string s;
        cout << "\nEnter String: ";
        cin >> s;
        if (s == "")
            return 0;
        bool accepted = parser.test(s);
        if (accepted)
        {
            cout << "\nAccepted\n";
        }
        else
        {
            cout << "\nRejected\n";
        }
    }
}

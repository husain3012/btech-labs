#include <bits/stdc++.h>
using namespace std;

#define epsilon '#'
#define endSymbol '$'

vector<string> split(string s, char delem = ' ')
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

class First_and_Follow
{

    string removeInterEpsilon(string str)
    {
        string temp = "";
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] != epsilon or i == str.length() - 1)
            {
                temp += str[i];
            }
        }
        return temp;
    }

    string uniq(string s)
    {
        unordered_set<char> st;
        string temp;
        for (char c : s)
        {
            if (st.find(c) == st.end())
                temp += c;
            st.insert(c);
        }
        return temp;
    }
    string firstOfHelper(string str, unordered_set<string> &call_stack)
    {
        if (call_stack.find(str) != call_stack.end())
            return "";
        call_stack.insert(str);

        string first;
        if (str.length() == 1)
        {
            char c = str[0];

            if (isTerminal(c))
            {
                first += c;
                first = removeInterEpsilon(first);
                first = uniq(first);
                return first;
            }

            for (string production : productions[c])
            {
                first += firstOfHelper(production, call_stack);
            }
            first = removeInterEpsilon(first);
            first = uniq(first);
            return first;
        }
        // case where str.length > 1
        for (int i = 0; i < str.length(); i++)
        {
            char c = str[i];

            if (isTerminal(c))
            {
                first += c;
                first = uniq(first);
                return first;
            }

            first += firstOfHelper(str.substr(i, i + 1), call_stack);

            if (first.find(epsilon) == first.npos)
            {
                break;
            }
        }
        first = removeInterEpsilon(first);
        first = uniq(first);

        return first;
    }
    string followOfHelper(char c, unordered_set<char> &call_stack)
    {
        string follow;
        if (call_stack.find(c) != call_stack.end())
            return "";
        if (c == startSymbol)
        {
            follow.push_back(endSymbol);
        }
        for (auto production_pairs : productions)
        {
            vector<string> prods = production_pairs.second;
            char parent = production_pairs.first;
            for (string prod : prods)
            {
                for (int i = 0; i < prod.length(); i++)
                {
                    char el = prod[i];
                    if (el != c)
                        continue;

                    if (i == prod.length() - 1)
                    {
                        call_stack.insert(c);
                        follow += followOfHelper(parent, call_stack);
                    }
                    else
                    {
                        string temp_first = firstOf(prod.substr(i + 1, prod.length()));

                        follow += temp_first;
                        if (temp_first.find(epsilon) != temp_first.npos)
                        {
                            follow += followOf(parent);
                        }
                    }
                }
            }
        }
        // remove epsilons
        string filtered_follow;
        for (char c : follow)
        {
            if (c != epsilon)
                filtered_follow += c;
        }
        return uniq(filtered_follow);
    }

protected:
    unordered_map<char, vector<string>> productions;
    unordered_set<char> terminals;
    unordered_set<char> nonTerminals;

    char startSymbol;

    bool isTerminal(char c)
    {
        return !isupper(c);
    }
    bool hasNullProduction(char c)
    {
        if (isTerminal(c))
            return false;
        for (string production : productions[c])
        {
            if (production[0] == epsilon)
                return true;
        }
        return false;
    }

public:
    First_and_Follow()
    {
        startSymbol = '\0';
    }

    void read()
    {
        ifstream file;
        file.open("cfg.txt");
        string line;
        while (getline(file, line))
        {
            char symbol = line[0];
            nonTerminals.insert(symbol);
            string prod = line.substr(1, line.length());
            for (char c : prod)
            {
                if (isTerminal(c))
                {
                    terminals.insert(c);
                }
            }

            if (startSymbol == '\0')
                startSymbol = symbol;

            productions[symbol].push_back(prod);
        }
    }
    string getTerminals()
    {
        unordered_set<char> terminals_set;
        for (auto production_pairs : productions)
        {
            vector<string> productions = production_pairs.second;
            for (string prod : productions)
            {
                for (char c : prod)
                {
                    if (isTerminal(c))
                        terminals_set.insert(c);
                }
            }
        }
        string terminals;
        for (char c : terminals_set)
        {
            terminals.push_back(c);
        }
        return terminals;
    }
    string getNonTerminals()
    {
        string nonTerminals;
        for (auto production_pairs : productions)
        {
            nonTerminals.push_back(production_pairs.first);
        }
        return nonTerminals;
    }

    string firstOf(string str)
    {
        unordered_set<string> call_stack;
        string temp_first = firstOfHelper(str, call_stack);
        sort(temp_first.begin(), temp_first.end());
        return temp_first;
    }

    string followOf(char c)
    {
        unordered_set<char> call_stack;
        string temp_follow = followOfHelper(c, call_stack);
        return temp_follow;
    }

    void printProductions()
    {
        cout << startSymbol << " -> ";
        vector<string> prods = productions[startSymbol];
        for (int i = 0; i < prods.size(); i++)
        {
            cout << prods[i] << " ";
            if (i < prods.size() - 1)
            {
                cout << "| ";
            }
        }
        cout << "\n";
        for (auto production_pairs : productions)
        {
            if (production_pairs.first == startSymbol)
                continue;

            cout << production_pairs.first << " -> ";
            vector<string> prods = production_pairs.second;
            for (int i = 0; i < prods.size(); i++)
            {
                cout << prods[i] << " ";
                if (i < prods.size() - 1)
                {
                    cout << "| ";
                }
            }
            cout << "\n";
        }
    }

    void allFirsts()
    {
        for (char c : nonTerminals)
        {
            string tmp;
            tmp += c;
            string firsts = firstOf(tmp);
            cout << "FIRST(" << tmp << ") = {";
            for (int i = 0; i < firsts.length(); i++)
            {
                cout << firsts[i];
                if (i < firsts.length() - 1)
                    cout << ", ";
            }
            cout << "}\n";
        }
    }
    void allFollows()
    {
        for (char c : nonTerminals)
        {

            string follows = followOf(c);
            cout << "FOLLOW(" << c << ") = {";
            for (int i = 0; i < follows.length(); i++)
            {
                cout << follows[i];
                if (i < follows.length() - 1)
                    cout << ", ";
            }
            cout << "}\n";
        }
    }
};

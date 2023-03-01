#include <bits/stdc++.h>
using namespace std;

class String
{

public:
    string data;
    String()
    {
        data = "";
    }
    String(string s)
    {
        data = s;
    }

    String(const char *s)
    {
        while (*s != '\0')
        {
            data += *s;
            s++;
        }
    }
    
    operator char *()
    {
        char *s = new char[data.length() + 1];
        int i = 0;
        for (i = 0; i < data.length(); i++)
        {
            s[i] = data[i];
        }
        s[i] = '\0';
        return s;
    }
};

int main()
{
    char s[] = "This is char array";
    String str(s);
    cout << str.data << endl;
// =======================================
    String str2("This is string class");
    char *s2 = str2;
    cout << s2 << endl;

    return 0;
}
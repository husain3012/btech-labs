#include <bits/stdc++.h>

using namespace std;

class SubstitutionCypher
{

    int key;

public:
    unordered_map<int, char> mp;
    SubstitutionCypher(string data = "", int key = 3)
    {

        for (int i = 0; i < 26; i++)
        {
            mp[i] = 'a' + i;
            mp[26 + i] = 'A' + i;
        }

        this->key = key;
    }

    string encrypt(string data)
    {

        string encryptedData = "";
        for (auto c : data)
        {
            if (c == ' ')
                encryptedData += ' ';
            if (islower(c))
            {
                encryptedData += mp[(c - 'a' + key) % 26];
            }
            else if (isupper(c))
            {
                encryptedData += mp[(c - 'a' + key) % 52];
            }
        }
        return encryptedData;
    }
    string decrypt(string data)
    {
        string decryptedText = "";
        for (char c : data)
        {
            if (c == ' ')
                decryptedText += ' ';
            else
            {

                decryptedText += mp[(c - 'a' - key + 52) % 52];
            }
        }
        return decryptedText;
    }
    void setKey(int key)
    {
        this->key = key;
    }
};

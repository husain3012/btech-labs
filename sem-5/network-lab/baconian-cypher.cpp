#include <bits/stdc++.h>
using namespace std;

// Simple Baconian cipher for letters
class Baconian
{
    static map<char, string> ciphertext;

public:
    string encrypt(string data)
    {
        string encrypted = "";
        for (int i = 0; i < data.length(); i++)
        {
            encrypted += ciphertext[data[i]];
        }
        return encrypted;
    }
    string decrypt(string data)
    {
        string decrypted = "";
        for (int i = 0; i < data.length(); i += 5)
        {
            string temp = data.substr(i, 5);
            for (auto it = ciphertext.begin(); it != ciphertext.end(); it++)
            {
                if (it->second == temp)
                {
                    decrypted += it->first;
                    break;
                }
            }
        }
        return decrypted;
    }
};
map<char, string> Baconian::ciphertext = {{'a', "00000"}, {'b', "00001"}, {'c', "00010"}, {'d', "00011"}, {'e', "00100"}, {'f', "00101"}, {'g', "00110"}, {'h', "00111"}, {'i', "01000"}, {'j', "01001"}, {'k', "01010"}, {'l', "01011"}, {'m', "01100"}, {'n', "01101"}, {'o', "01110"}, {'p', "01111"}, {'q', "10000"}, {'r', "10001"}, {'s', "10010"}, {'t', "10011"}, {'u', "10100"}, {'v', "10101"}, {'w', "10110"}, {'x', "10111"}, {'y', "11000"}, {'z', "11001"}};
int main()
{
    string message;
    int option = -1;
    Baconian cypher;

    cout << "\n=====================\n1. Encrypt \n2. Decrypt\n3. Exit\n=====================\n";
    while (option != 3)
    {
        cout << "=>";
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "Enter Plain text: ";
            cin >> message;
            message = cypher.encrypt(message);
            cout << "Encrypted text: " << message << endl;
            break;
        case 2:
            cout << "Enter Encrypted text: ";
            cin >> message;
            message = cypher.decrypt(message);
            cout << "Decrypted text: " << message << endl;
            break;
        default:
            break;
        }
    }
    cout << "Bye!";

}

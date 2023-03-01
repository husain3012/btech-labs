#include <iostream>
#include <string>
#include <vector>
using namespace std;
//  a secret message from the president
string const terminator = "xabcdefghijklmnopqrstuvwxyz";


string encrypt(string s, int key)
{
    int rows = (s.length() / key) + (s.length() % key == 0 ? 0 : 1), cols = key;
    vector<vector<char>> matrix(rows, vector<char>(cols, '\0'));
    int ptr1 = 0, ptr2 = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {

            if (ptr1 < s.length())
            {
                if ((s[ptr1] >= 'a' && s[ptr1] <= 'z') || (s[ptr1] >= 'A' && s[ptr1] <= 'Z'))
                {
                    matrix[i][j] = s[ptr1++];
                }
                else
                {
                    cout << "\nInvalid characters!\n";
                    return "";
                }
            }
            else
            {
                matrix[i][j] = terminator[ptr2++];
            }
        }
    }
  

    string encrypted = "";
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            encrypted += matrix[j][i];
        }
    }
    return encrypted;
}

string decrypt(string encrypted, int key)
{
    int rows = (encrypted.length() / key) + (encrypted.length() % key == 0 ? 0 : 1);
    string re_encrypt = encrypt(encrypted, rows);
    for (int i = 0; i < re_encrypt.length(); i++)
    {
        bool isTerminator = false;
        if (re_encrypt[i] == terminator[0])
        {
            int ptr1 = i;
            int ptr2 = 0;

            while (ptr1 < re_encrypt.length() && re_encrypt[ptr1] == terminator[ptr2])
            {
                ptr1++, ptr2++;
            }
            if (ptr1 == re_encrypt.length())
            {
                isTerminator = true;
            }
        }
        if (isTerminator)
        {
            re_encrypt = re_encrypt.substr(0, i);
            return re_encrypt;
        }
    }
    return re_encrypt;
}

int main()
{

    int key = 5;
    int choice = -1;
    string s;
    while (choice != 0)
    {
        cout << "------------------MENU--------------------\n";
        cout << "1. Encrypt\n2. Decrypt\n3. Exit\n";
        cout << "------------------------------------------\n";
        cout << "=> ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter string to encrypt: ";
            cin >> s;
            cout << "Enter Key: ";
            cin >> key;
            s = encrypt(s, key);
            if (s.length())
            {
                cout << "Encrypted string: " << s << "\n";
            }
            break;
        case 2:
            cout << "Enter string to decrypt: ";
            cin >> s;
            cout << "Enter Key: ";
            cin >> key;
            s = decrypt(s, key);
            cout << "Decrypted string: " << s << "\n";
            break;
        case 3:
            cout << "Bye!";
            return 0;

        default:
            cout << "Invalid Choice!\n";
            break;
        }
    }
}
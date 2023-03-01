#include <iostream>
#include <unordered_map>
#include <string.h>
#include <string>

using namespace std;

class Encrypt
{

    int key;
    string data;
    bool encrypted;

public:
    unordered_map<int, char> mp;
    Encrypt(string data = "", int key = 3)
    {

        for (int i = 0; i < 26; i++)
        {
            mp[i] = 'a' + i;
            mp[26 + i] = 'A' + i;
        }
        this->data = data;
        this->key = key;
        encrypted = false;
    }

    void encrypt()
    {
        if (encrypted)
        {
            cout << "Already Encrypted!\n";
            return;
        }
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
        data = encryptedData;
        cout << "Encrypted Successfully!\n";
        encrypted = true;
        display();
    }
    void decrypt()
    {
        if (!encrypted)
        {
            cout << "Already Decrypted!\n";
            return;
        }
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
        cout << endl;
        data = decryptedText;
        cout << "Decrypted Successfully!\n";
        encrypted = false;
        display();
    }
    void setKey(int key)
    {
        this->key = key;
    }
    void setData(string data, bool encrypted = false)
    {

        this->data = data;
        encrypted = this->encrypted;
    }

    void display()
    {
        cout << "Data: " << data << endl;
    }
};

int main()
{
    cout << "\n20BCS028 Husain Shahid Rao\n";
    Encrypt enc("", 3);
    int choice = 0;

    while (choice != 6)
    {
        cout << "\n===========MENU===========\n";
        cout << "|1| Set key \t\t||\n|2| Set Data \t\t||\n|3| Encrypt \t\t||\n|4| Decrypt \t\t||\n|5| Display \t\t||\n|6| Exit \t\t||";
        cout << "\n==========================\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int k;
            cin >> k;
            enc.setKey(k);
            break;
        }
        case 2:
        {
            string st;
            cout << "Enter Data: ";
            getchar();
            getline(cin, st);
            enc.setData(st);
            break;
        }
        case 3:
            enc.encrypt();
            break;
        case 4:
            enc.decrypt();
            break;
        case 5:
            enc.display();
            break;

        case 6:
            cout << "Bye!";
            return 0;
        default:
            cout << "Invalid Option";
            break;
        }
    }
}
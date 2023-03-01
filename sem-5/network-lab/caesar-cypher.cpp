#include <iostream>
using namespace std;

class CaesarCypher
{
    int shift;

public:
    CaesarCypher(int shift)
    {
        this->shift = shift;
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
                encryptedData += (char)((c - 'a' + shift) % 26 + 'a');
            }
            else if (isupper(c))
            {
                encryptedData += (char)((c - 'A' + shift) % 26 + 'A');
            }
        }
        return encryptedData;
    }
    string decrypt(string data)
    {
        string decryptedData = "";
        for (auto c : data)
        {
            if (c == ' ')
                decryptedData += ' ';
            if (islower(c))
            {
                decryptedData += (char)((c - 'a' - shift + 26) % 26 + 'a');
            }
            else if (isupper(c))
            {
                decryptedData += (char)((c - 'A' - shift + 26) % 26 + 'A');
            }
        }
        return decryptedData;
    }
    void setShift(int shift)
    {
        this->shift = shift;
    }
};

// Driver program to test the above function
int main()
{
    CaesarCypher cypher(3);
    //  a famous quote by Albert Einstein
    string data = "If you can't explain it to a six year old, you don't understand it yourself.";
    string encryptedData = cypher.encrypt(data);
    cout << "Encrypted Data: " << encryptedData << endl;
    cout << "Decrypted Data: " << cypher.decrypt(encryptedData) << endl;
    return 0;
}

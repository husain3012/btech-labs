#include <iostream>
#include <unordered_map>
#include <string.h>
#include <vector>
#include <string>

using namespace std;

class VignereCypher
{

    string key;

public:
    vector<vector<char>> matrix;

    VignereCypher(string key)
    {

        this->key = key;
        matrix.resize(26, vector<char>(26));

        for (int i = 0; i < 26; i++)
        {
            for (int j = 0; j < 26; j++)
            {
                matrix[i][j] = 'a' + (i + j) % 26;
            }
        }
    }

    void showMatrix()
    {
        for (int i = 0; i < 26; i++)
        {
            for (int j = 0; j < 26; j++)
            {
                cout << matrix[i][j] << " | ";
            }
            cout << endl;
            for (int i = 0; i < 26; i++)
            {
                cout << "----";
            }
            cout << endl;
        }
    }

    string encrypt(string data)
    {

        string encryptedData = "";

        for (int i = 0; i < data.length(); i++)
        {
            if (data[i] < 48 || data[i] > 122)
            {
                encryptedData += data[i];
                continue;
            }
           
            char row_char = key[i % key.length()];
            char col_char = data[i];

            int row = row_char - 'a';
            int col = col_char - 'a';
            // cout << "[" << row << ", " << col << "]\t";
            encryptedData += matrix[row][col];
        }
        return encryptedData;
    }
    string decrypt(string data)
    {
        string decryptedData = "";

        for (int i = 0; i < data.length(); i++)
        {
             if (data[i] < 48 || data[i] > 122)
            {
                decryptedData += data[i];
                continue;
            }
            char col_char = key[i % key.length()];
            int col = col_char - 'a';
            int row = 0;
            while (matrix[row++][col] != data[i])
                ;

            decryptedData += matrix[row - 1][0];
        }
        return decryptedData;
    }

    void setKey(string key)
    {
        this->key = key;
    }
};

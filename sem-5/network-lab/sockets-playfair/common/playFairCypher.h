#include <bits/stdc++.h>
using namespace std;

class PlayFair
{
    vector<vector<char>> matrix;
    string key;

    void updateMatrix()
    {
        set<char> strAlphabets;
        for (int i = 0; i < key.length(); i++)
        {
            if (key[i] == 'j')
            {
                key[i] = 'i';
            }
            if (strAlphabets.find(key[i]) == strAlphabets.end())
            {
                strAlphabets.insert(key[i]);
            }
        }
        int i = 0, j = 0;
        for (auto it = strAlphabets.begin(); it != strAlphabets.end(); it++)
        {
            matrix[i][j] = *it;
            j++;
            if (j == 5)
            {
                i++;
                j = 0;
            }
        }
        for (char ch = 'a'; ch <= 'z'; ch++)
        {
            if (ch == 'j')
            {
                continue;
            }
            if (strAlphabets.find(ch) == strAlphabets.end())
            {
                matrix[i][j] = ch;
                j++;
                if (j == 5)
                {
                    i++;
                    j = 0;
                }
            }
        }
    }

public:
    PlayFair(string k = "monarchy")
    {
        key = k;
        matrix.resize(5, vector<char>(5));
        updateMatrix();
    }
    string encrypt(string data)
    {
        string encrypted = "";
        for (int i = 0; i < data.length(); i += 2)
        {
            if (data[i] == 'j')
            {
                data[i] = 'i';
            }
            if (data[i + 1] == 'j')
            {
                data[i + 1] = 'i';
            }
            if (data[i] == data[i + 1])
            {
                data.insert(i + 1, "x");
            }
        }
        if (data.length() % 2 != 0)
        {
            data += 'x';
        }
        for (int i = 0; i < data.length(); i += 2)
        {
            int row1, row2, col1, col2;
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    if (matrix[j][k] == data[i])
                    {
                        row1 = j;
                        col1 = k;
                    }
                    if (matrix[j][k] == data[i + 1])
                    {
                        row2 = j;
                        col2 = k;
                    }
                }
            }
            if (row1 == row2)
            {
                encrypted += matrix[row1][(col1 + 1) % 5];
                encrypted += matrix[row2][(col2 + 1) % 5];
            }
            else if (col1 == col2)
            {
                encrypted += matrix[(row1 + 1) % 5][col1];
                encrypted += matrix[(row2 + 1) % 5][col2];
            }
            else
            {
                encrypted += matrix[row1][col2];
                encrypted += matrix[row2][col1];
            }
        }
        return encrypted;
    }
    string decrypt(string data)
    {
        string decrypted = "";
        for (int i = 0; i < data.length(); i += 2)
        {
            int row1, row2, col1, col2;
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    if (matrix[j][k] == data[i])
                    {
                        row1 = j;
                        col1 = k;
                    }
                    if (matrix[j][k] == data[i + 1])
                    {
                        row2 = j;
                        col2 = k;
                    }
                }
            }
            if (row1 == row2)
            {
                decrypted += matrix[row1][(col1 - 1 + 5) % 5];
                decrypted += matrix[row2][(col2 - 1 + 5) % 5];
            }
            else if (col1 == col2)
            {
                decrypted += matrix[(row1 - 1 + 5) % 5][col1];
                decrypted += matrix[(row2 - 1 + 5) % 5][col2];
            }
            else
            {
                decrypted += matrix[row1][col2];
                decrypted += matrix[row2][col1];
            }
        }
        // remove trailing x
        if (decrypted.back() == 'x')
        {
            decrypted.pop_back();
        }
        return decrypted;
    }

    void setKey(string k)
    {
        key = k;
        updateMatrix();
    }
};
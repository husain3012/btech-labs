#include <bits/stdc++.h>
using namespace std;

class RailFence
{
    int key;

public:
    RailFence(int k = 3)
    {
        key = k;
    }
    string encrypt(string data)
    {
        int len = data.length();
        int row = key;
        int col = len;
        char rail[row][col];
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                rail[i][j] = '\n';
            }
        }
        bool down = false;
        int r = 0, c = 0;
        for (int i = 0; i < len; i++)
        {
            if (r == 0 || r == key - 1)
            {
                down = !down;
            }
            rail[r][c++] = data[i];
            down ? r++ : r--;
        }
        string result;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (rail[i][j] != '\n')
                {
                    result.push_back(rail[i][j]);
                }
            }
        }
        return result;
    }
    string decrypt(string data)
    {
        int len = data.length();
        int row = key;
        int col = len;
        char rail[row][col];
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                rail[i][j] = '\n';
            }
        }
        bool down;
        int r = 0, c = 0;
        for (int i = 0; i < len; i++)
        {
            if (r == 0)
            {
                down = true;
            }
            if (r == key - 1)
            {
                down = false;
            }
            rail[r][c++] = '*';
            down ? r++ : r--;
        }
        int index = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (rail[i][j] == '*' && index < len)
                {
                    rail[i][j] = data[index++];
                }
            }
        }
        string result;
        r = 0, c = 0;
        for (int i = 0; i < len; i++)
        {
            if (r == 0)
            {
                down = true;
            }
            if (r == key - 1)
            {
                down = false;
            }
            if (rail[r][c] != '*')
            {
                result.push_back(rail[r][c++]);
            }
            down ? r++ : r--;
        }
        return result;
    }
    void setKey(int k)
    {
        key = k;
    }
};
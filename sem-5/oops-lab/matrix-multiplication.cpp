#include <iostream>
#include <vector>
using namespace std;

class Matrix
{
    int row, col;
    vector<vector<int>> matrix;

public:
    static int totalMultiplicationsPerformed;
    Matrix(int row, int col)
    {
        this->row = row;
        this->col = col;
        matrix.resize(row, vector<int>(col, 0));
    }
    // copy constructor
    Matrix(const Matrix &m)
    {
        this->row = m.row;
        this->col = m.col;
        matrix.resize(row, vector<int>(col, 0));
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                matrix[i][j] = m.matrix[i][j];
            }
        }
    }
    void reshape(int row, int col)
    {
        this->row = row;
        this->col = col;
        matrix.resize(row, vector<int>(col, 0));
    }

    void readData(istream &istream = cin)
    {
        cout << "Enter number of rows and columns: ";
        int r, c;
        istream >> r >> c;
        this->reshape(r, c);
        cout << "Enter Values:\n";
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                cout << "[" << i << "][" << j << "] = ";
                int d;
                istream>>matrix[i][j];
            }
        }
        cout << "\n====================\n";
        this->display();
        cout << "====================\n";
    }

    // matrix multiplication using operator overloading
    Matrix operator*(const Matrix &m)
    {
        // return null matrix if the number of columns of the first matrix is not equal to the number of rows of the second matrix
        if (this->col != m.row)
        {
            cout << "\nInvalid matrix multiplication\n";
            return Matrix(0, 0);
        }
        Matrix result(row, m.col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < m.col; j++)
            {
                for (int k = 0; k < col; k++)
                {
                    result.matrix[i][j] += matrix[i][k] * m.matrix[k][j];
                    totalMultiplicationsPerformed++;
                }
            }
        }
        return result;
    }
    Matrix operator+(const Matrix &m)
    {
        if (this->col != m.col or this->row != m.row)
        {
            cout << "\nCannot add these two matrices!\n";
            return Matrix(0, 0);
        }
        Matrix result(row, col);

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                result.matrix[i][j] = this->matrix[i][j] + m.matrix[i][j];
            }
        }
        return result;
    }
    bool operator==(const Matrix &m)
    {
        if (this->col != m.col or this->row != m.row)
        {
            return false;
        }
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (this->matrix[i][j] != m.matrix[i][j])
                    return false;
            }
        }
        return true;
    }
    // display matrix
    void display(ostream &stream = cout)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                stream << matrix[i][j] << " ";
            }
            stream << endl;
        }
    }
 

    // randomize matrix
    void randomize()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                matrix[i][j] = rand() % 100;
            }
        }
    }

    static int getTotalMultiplications()
    {
        return totalMultiplicationsPerformed;
    }
};
int Matrix::totalMultiplicationsPerformed = 0;

void operator<<(ostream &stream, Matrix m)
{
    m.display(stream);
}
void operator>>(istream &stream, Matrix m)
{
    m.readData(stream);
}

int main()
{

    // menu driven program
    int choice = 0;
    Matrix A(0, 0);
    Matrix B(0, 0);
    srand(time(NULL));

    while (choice != 8)
    {
        cout << "\n=====================MENU=====================\n";
        cout << "1. Generate two random matrices\n2. Input two matrices\n3. Display Matrices\n4. Add\n5. Multiply\n6. Are equal?\n7. Display total multiplications performed\n8. Exit\nChoice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            int row, col;
            cout << "Enter the number of rows and columns of matrix A: ";
            cin >> row >> col;
            A.reshape(row, col);
            cout << "Enter the number of rows and columns of matrix B: ";
            cin >> row >> col;
            B.reshape(row, col);
            A.randomize();
            B.randomize();
            cout << "Matrix A: " << endl
                 << A;
            cout << "Matrix B: " << endl
                 << B;
            break;
        }
        case 2:
        {
            // cin >> A;
            // cin >> B;
            A.readData();
            B.readData();
            break;
        }
        case 3:
        {
            cout << "MATRIX A:\n"
                 << A;
            cout << endl;
            cout << "MATRIX B:\n"
                 << A;
            break;
        }
        case 4:
        {
            Matrix C = A + B;
            cout << "Matrix C = A + B " << endl;
            cout << C;
            break;
        }

        case 5:
        {
            Matrix C = A * B;
            cout << "Matrix C = A * B " << endl;
            cout << C;
            break;
        }
        case 6:
        {
            bool areEqual = A == B;
            cout << "A == B " << endl;
            if (areEqual)
            {
                cout << "Yes";
            }
            else
            {
                cout << "No";
            }
            break;
        }
        case 7:
        {
            cout << "Total multiplications performed: " << Matrix::getTotalMultiplications() << endl;
            break;
        }

        case 8:
        {
            cout << "Bye!" << endl;
            break;
        }

        default:
            break;
        }
    }
}
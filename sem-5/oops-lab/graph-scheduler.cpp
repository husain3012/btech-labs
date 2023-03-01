#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

class Graph
{
private:
    vector<vector<int>> adjacencyMatrix;

public:
    int vertices;
    Graph(int n)
    {
        this->adjacencyMatrix.resize(n, vector<int>(n, -1));
        this->vertices = n;
    }
    void generateRandomConnections()
    {
        srand(time(0));

        for (int i = 0; i < vertices; i++)
            for (int i = 0; i < vertices; i++)
            {
                for (int j = i + 1; j < vertices; j++)
                {
                    int randNum = rand() % vertices - 1;
                    adjacencyMatrix[i][j] = randNum == 0 ? 1 : randNum;
                }
            }
    }
    void displayAdjacencyMatrix()
    {
        cout << "Adjacency Matrix\n";
        for (auto row : adjacencyMatrix)
        {
            for (auto cell : row)
            {
                cout << cell << "\t";
            }
            cout << "\n\n";
        }
    }
};

class ProcessScheduler
{
    int processors;
    int numberOfTasks;
    vector<vector<int>> burstTimeTable;

public:
    ProcessScheduler(int processors, Graph tasks)
    {
        numberOfTasks = tasks.vertices;
        burstTimeTable.resize(processors, vector<int>(numberOfTasks, 0));
    }
    void generateRandomBurstTimes()
    {
        srand(time(0));

        for (int i = 0; i < burstTimeTable.size(); i++)
        {
            for (int j = 0; j < burstTimeTable[0].size(); j++)
            {
                burstTimeTable[i][j] = rand()%10 +1;
            }
        }
    }
    void displayBurstTimeMatrix()
    {
        cout << "Process Burst Time Table\n";
        // cout << "\t";
        for (int i = 0; i < numberOfTasks; i++)
        {
            cout << "T" << i << "\t";
        }
        cout << endl;
        for (auto row : burstTimeTable)
        {
            cout << "P";
            for (auto cell : row)
            {
                cout << cell << "\t";
            }
            cout << "\n\n";
        }
    }
};

int main()
{
    int processors = 3;
    int tasks = 5;
    cout << "Enter number of tasks: ";
    cin >> tasks;
    cout << "Enter number of processors: ";
    cin >> processors;
    Graph g(tasks);
    g.generateRandomConnections();
    g.displayAdjacencyMatrix();
    ProcessScheduler ps(processors, g);
    ps.generateRandomBurstTimes();
    ps.displayBurstTimeMatrix();
}
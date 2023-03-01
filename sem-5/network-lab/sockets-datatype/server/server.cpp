#include <thread>
#include <unordered_set>
#include "server.h"
using namespace std;

void ServerConnectionHandler(Server *server)
{
    while (true)
    {
        server->Accept();
    }
}

string checkDataType(string data)
{
    // remove whitespace
    data.erase(remove_if(data.begin(), data.end(), ::isspace), data.end());
    // check if data is a number
    unordered_set<char> numberSet = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
    int decimalCount = 0;
    bool isNumber = true;

    for (int i = 0; i < data.length(); i++)
    {
        if (data[i] == '.')
        {
            decimalCount++;
        }
    }

    for (int i = 0; i < data.length(); i++)
    {
        if (numberSet.find(data[i]) == numberSet.end())
        {
            isNumber = false;
            break;
        }
    }
    if (isNumber && decimalCount == 0)
    {
        return "int";
    }
    if (isNumber && decimalCount == 1)
    {
        return "float";
    }
    return "string";
}

int main()
{

    Server server(8080);
    thread accept_connections(ServerConnectionHandler, &server);
    while (true)
    {
        pair<int, string> message = server.Receive();

        if (message.first != -1)
        {

            cout << message.first << ": " << message.second << " (" << checkDataType(message.second) << ")" << endl;

            vector<ConnectedClient> connected_clients = server.getConnectedClients();

            // Forward message to all clients except the sender
            for (int j = 0; j < connected_clients.size(); j++)
            {
                ConnectedClient connected_client = connected_clients[j];
                if (connected_client.socket_fd != message.first)
                {
                    server.Send(to_string(message.first) + "@" + message.second, connected_client.socket_fd);
                }
            }
        }
    }

    server.Close();
    return 0;
}
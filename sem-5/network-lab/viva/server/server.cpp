#include <thread>
#include "./server.h"
using namespace std;

#define _EXIT_COMMAND_ "!!exit"
#define PORT 3000


void ServerConnectionHandler(Server *server)
{
    while (true)
    {
        server->Accept();
    }
}

pair<int, int> char_num_count(string s)
{
    int char_count = 0;
    int num_count = 0;
    for (char c : s)
    {
        if (isdigit(c))
        {
            num_count++;
        }
        else if (isalpha(c))
        {
            char_count++;
        }
    }
    return {char_count, num_count};
}

int main()
{

    Server server(PORT);
    thread accept_connections(ServerConnectionHandler, &server);
    while (true)
    {
        pair<int, string> message = server.Receive();

        if (message.first != -1)
        {

            cout << message.first << ": " << message.second << endl;
            if (message.second == _EXIT_COMMAND_)
            {
                server.Close(message.first);
                cout << "Connection closed with " << message.first << endl;

            }
            else
            {
                pair<int, int> char_num = char_num_count(message.second);
                string response = "No. of characters: " + to_string(char_num.first) + " No. of numbers: " + to_string(char_num.second);

                vector<ConnectedClient> connected_clients = server.getConnectedClients();

                //  reply back to the client
                server.Send(to_string(message.first) + "@" + response, message.first);
            }
        }
    }

    return 0;
}
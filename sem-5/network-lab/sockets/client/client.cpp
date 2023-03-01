#include <thread>
#include "./client.h"

using namespace std;

void ReceiveMessageHandler(Client *client)
{

    while (true)
    {
        string message = client->Receive();
        if (message.length() > 0)
        {
            string message_data = message.substr(message.find("@") + 1);
            string message_sender = message.substr(0, message.find("@"));
            message = message_sender + ": " + message_data;
            for (int i = 0; i < message.length() + 4; i++)
            {
                cout << "-";
            }
            cout << endl;
            cout << "| " << message << " |";
            cout << endl;
            for (int i = 0; i < message.length() + 4; i++)
            {
                cout << "-";
            }
            cout << endl;
        }
    }
}

int main()
{

    string ip = "127.0.0.1";
    Client client(ip, 8080);
    client.Connect();
    thread message_receiver_thread(ReceiveMessageHandler, &client);

    while (true)
    {
        string message;
        getline(cin, message);

        cout << "\rMe: " << message << endl;
        client.Send(message);
        // cout << "Message sent: " << message << endl;
    }

    client.Close();
    return 0;
}
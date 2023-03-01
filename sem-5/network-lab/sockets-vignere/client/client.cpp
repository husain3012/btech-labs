#include <thread>
#include "./client.h"
#include "../common/VignereCypher.h"

using namespace std;

void ReceiveMessageHandler(Client *client, string decryptionKey)
{
    VignereCypher cypher(decryptionKey);

    while (true)
    {
        string message = client->Receive();
        if (message.length() > 0)
        {
            string message_data = message.substr(message.find("@") + 1);
            string message_sender = message.substr(0, message.find("@"));
            message_data = cypher.decrypt(message_data);
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
    string decryptionKey;
    cout << "Enter decryption key: ";
    cin >> decryptionKey;
    Client client(ip, 8080);
    client.Connect();
    thread message_receiver_thread(ReceiveMessageHandler, &client, decryptionKey);
    VignereCypher cypher(decryptionKey);

    while (true)
    {
        string message;
        string encrypted;
        getline(cin, message);
        if (message.length() > 0)
        {
            encrypted = cypher.encrypt(message);
        }

        cout << "\rMe: " << message << endl;
        client.Send(encrypted);
        // cout << "Message sent: " << message << endl;
    }

    client.Close();
    return 0;
}
#include <thread>
#include "./client.h"
#include "../common/railFenceCypher.h"

using namespace std;

RailFence cypher;

void ReceiveMessageHandler(Client *client)
{

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
    Client client(ip, 8080);
    int decryptionKey;
    cout << "Enter decryption key: ";
    cin >> decryptionKey;
    cypher.setKey(decryptionKey);
    client.Connect();
    thread message_receiver_thread(ReceiveMessageHandler, &client);

    while (true)
    {
        string message;
        string encryptedMessage;
        getline(cin, message);
        encryptedMessage = cypher.encrypt(message);
        cout << "\rMe: " << message << endl;
        client.Send(encryptedMessage);
    }

    client.Close();
    return 0;
}
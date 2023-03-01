#include <iostream>
using namespace std;

template <typename T>
class Node
{
    T data;
    Node *next;

public:
    Node(T data, Node *nxt = nullptr)
    {
        this->data = data;
        next = nxt;
    }
};

template <typename T>
class LinkedList
{
    Node<T> head;

public:
    LinkedList()
    {
        head = nullptr;
    }
    void display()
    {
        Node<T> *temp = head;
        while (temp)
        {
            cout << temp->data << " => ";
            temp = temp->next;
        }
    }
    void push(T data)
    {
        Node<T> *temp = head;
        if(!temp){
            head
        }
        while (temp && temp->next)
        {
            temp = temp->next;
        }
        temp->next = new Student(data);
    }
};

int main()
{
}
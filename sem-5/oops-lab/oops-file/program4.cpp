#include <bits/stdc++.h>
using namespace std;

class Media
{
protected:
    string title;
    string publication;

public:
    Media(string title, string publication)
    {
        this->title = title;
        this->publication = publication;
    }
    virtual void display() = 0;
};

class Book : public Media
{
    int pages;

public:
    Book(string title, string publication, int pages) : Media(title, publication)
    {
        this->pages = pages;
    }
    // override display function of Media class
    void display()
    {
        cout << "----------------BOOK----------------" << endl;
        cout << "Title: \t" << title << endl;
        cout << "Publication: \t" << publication << endl;
        cout << "Pages: \t" << pages << endl;
        cout << "------------------------------------" << endl
             << endl;
    }
};
class Tape : public Media
{
    int playtime;

public:
    Tape(string title, string publication, int playtime) : Media(title, publication)
    {
        this->playtime = playtime;
    }
    void display()
    {
        cout << "----------------TAPE----------------" << endl;
        cout << "Title: \t" << title << endl;
        cout << "Publication: \t" << publication << endl;
        cout << "Play Time: \t" << playtime << endl;
        cout << "------------------------------------" << endl
             << endl;
    }
};
int main()
{
    Media *media1 = new Book("Let us C", "Oxford", 500);
    Media *media2 = new Tape("See you again", "Charlie Puth", 365);
    media1->display();
    media2->display();
}
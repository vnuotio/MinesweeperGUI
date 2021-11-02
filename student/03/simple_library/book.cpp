#include "book.hh"
#include <iostream>

using namespace std;

Book::Book(const string& author, const string& title):
    author_(author), title_(title), loaned_(false)
{

}

void Book::print()
{
    cout << author_ << " : " << title_
         << endl
         << "- ";
    if (loaned_)
    {
        cout << "loaned: ";
        loan_date_.print();

        cout << "- to be returned: ";
        return_date_.print();
    }
    else
    {
        cout << "available"
             << endl;
    }
}

void Book::loan(const Date date)
{
    if (loaned_)
    {
        cout << "Already loaned: cannot be loaned"
             << endl;
    }
    else
    {
        loaned_ = true;
        loan_date_ = date;
        return_date_ = date;
        return_date_.advance(28);
    }
}

void Book::renew()
{
    if (loaned_)
    {
        return_date_.advance(28);
    }
    else
    {
        cout << "Not loaned: cannot be renewed"
             << endl;
    }
}


void Book::give_back()
{
    loaned_ = false;
}

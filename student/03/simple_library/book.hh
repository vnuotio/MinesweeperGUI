#ifndef BOOK_HH
#define BOOK_HH

#include "date.hh"
#include <iostream>
using namespace std;


class Book
{
public:
    Book(const string& author, const string& title);
    void print();
    void loan(const Date date);
    void renew();
    void give_back();
private:
    string author_;
    string title_;
    bool loaned_;
    Date loan_date_;
    Date return_date_;
};

#endif // BOOK_HH

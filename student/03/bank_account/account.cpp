#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), iban_(), saldo_(0), has_credit_(has_credit)
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::print() const
{
    std::cout << owner_ << " : " << iban_ << " : " << saldo_ << " euros"
              << std::endl;
}

void Account::set_credit_limit(int limit)
{
    if (has_credit_)
    {
        credit_limit_ = limit;
    }
    else
    {
        std::cout << "Cannot set credit limit: the account has no credit card"
                  << std::endl;
    }
}

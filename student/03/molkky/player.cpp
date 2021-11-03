#include "player.hh"
#include <iostream>

using namespace std;

Player::Player(const string& name):
    name_(name), score_(0)
{

}

string Player::get_name() const
{
    return name_;
}

int Player::get_points() const
{
    return score_;
}

void Player::add_points(int pts)
{
    if (score_ + pts > 50)
    {
        score_ = 25;
        cout << name_ << " gets penalty points!"
             << endl;
    }
    else
    {
        score_ += pts;
    }
}

bool Player::has_won() const
{
    return score_ == 50;
}

#ifndef PLAYER_HH
#define PLAYER_HH

#include <iostream>

using namespace std;

class Player
{
public:
    Player(const string& name);

    string get_name() const;
    int get_points() const;
    void add_points(int pts);
    bool has_won() const;
private:
    string name_;
    int score_;
};

#endif // PLAYER_HH

#include <iostream>

using namespace std;


long unsigned int factorial(int num)
{
    if (num == 0)
    {
        return 1;
    }

    long unsigned int f = 1;
    for (int i = 1; i <= num; ++i)
    {
        f *= i;
    }
    return f;
}


int take_input(string msg)
{
    int ans = 0;
    cout << msg;
    cin >> ans;

    return ans;
}


long unsigned int probability(int n, int p)
{
    long unsigned int prob = factorial(n) / (factorial(n - p) * factorial(p));
    return prob;
}


int main()
{
    int total_balls = take_input("Enter the total number of lottery balls: ");
    int drawn_balls = take_input("Enter the number of drawn balls: ");

    if (total_balls <= 0 or drawn_balls <= 0)
    {
        cout << "The number of balls must be a positive number." << endl;
        return EXIT_FAILURE;
    }
    if (drawn_balls > total_balls)
    {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return EXIT_FAILURE;
    }

    cout << "The probability of guessing all " << drawn_balls << " correct is "  << probability(total_balls, drawn_balls) << endl;

    return EXIT_SUCCESS;
}

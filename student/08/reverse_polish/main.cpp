#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

set<char> OPERATORS = {'+', '-', '*', '/'};
char END = '#';

int reverse_polish(const vector<char>& input)
{
    if (not isdigit(input.front()))
    {
        cout << "Error: Expression must start with a number" << endl;
        return -1;
    }

    vector<int> op;

    for (size_t i = 0; i < input.size(); i++)
    {
        char c = input.at(i);
        if (OPERATORS.find(c) != OPERATORS.end())
        {
            size_t s = op.size();
            if (op.size() < 2)
            {
                cout << "Error: Too few operands" << endl;
                return -1;
            }
            else
            {
                if (c == '+')
                {
                    op.at(s - 2) += op.back();
                }
                else if (c == '-')
                {
                    op.at(s - 2) -= op.back();
                }
                else if (c == '*')
                {
                    op.at(s - 2) *= op.back();
                }
                else if (c == '/')
                {
                    if (op.back() == 0)
                    {
                        cout << "Error: Division by zero" << endl;
                        return -1;
                    }
                    else
                    {
                        op.at(s -2) /= op.back();
                    }
                }
                op.pop_back();
            }
        }
        else if (isdigit(c))
        {
            op.push_back((int)c - int('0'));
        }
        else
        {
            cout << "Error: Unknown character" << endl;
            return -1;
        }
    }

    if (op.size() == 1)
    {
        return op.front();
    }
    else
    {
        cout << "Error: Too few operators" << endl;
        return -1;
    }
}

int main()
{
    cout << "Input an expression in reverse Polish notation (end with #):" << endl;
    cout << "EXPR> ";

    vector<char> input;

    char c;
    while (cin >> c and c != END)
    {
        input.push_back(c);
    }

    int result = reverse_polish(input);
    if (result < 0)
    {
        return EXIT_FAILURE;
    }
    else
    {
        cout << "Correct: " << result << " is the result" << endl;
        return EXIT_SUCCESS;
    }
}

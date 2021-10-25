#include <iostream>
using namespace std;


int main()
{
    cout << "How many numbers would you like to have? ";
    int n = 0;
    cin >> n;

    string output = "";
    for (int i = 1; i <= n; ++i)
    {
        output = "";
        if (i % 3 == 0)
        {
            output += "zip";
        }
        else
        {
            output += to_string(i);
        }
        cout << output << endl;
    }
    return 0;
}

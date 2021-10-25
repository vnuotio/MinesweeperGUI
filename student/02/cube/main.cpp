#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    int num = 0;
    cout << "Enter a number: ";
    cin >> num;

    int num_3_pow = pow(num, 3);

    if ((int)cbrt(num_3_pow) != num)
    {
        cout << "Error! The cube of " << num << " is not " << num_3_pow << endl;
    }
    else
    {
        cout << "The cube of " << num << " is " << num_3_pow << endl;
    }
    return 0;
}

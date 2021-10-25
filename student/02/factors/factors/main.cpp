#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    int num = 0;
    cout << "Enter a positive number: ";
    cin >> num;

    if (num <= 0)
    {
        cout << "Only positive numbers accepted" << endl;
        return 0;
    }

    int factor = (int)sqrt(num);

    while (num % factor != 0)
    {
        --factor;
    }
    cout << num << " = " << factor << " * " << num / factor << endl;
    return 0;
}

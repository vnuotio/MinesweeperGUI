#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";

    double t = 0.0;

    cin >> t;

    double c = (t - 32) / 1.8;
    double f = t * 1.8 + 32;

    cout << t << " degrees Celsius is " << f << " degrees Fahrenheit" << endl;
    cout << t << " degrees Fahrenheit is " << c << " degrees Celsius" << endl;

    return 0;
}

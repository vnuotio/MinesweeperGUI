#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";
    int n = 0;
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        std::cout << i << std::endl;
    }
    return 0;
}

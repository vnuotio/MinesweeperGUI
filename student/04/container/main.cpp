#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}

// TODO: Implement your solution here

bool same_values(const std::vector<int>& nums)
{
    for (std::vector<int>::size_type i=1; i < nums.size(); ++i)
    {
        if (nums.at(i) != nums.at(i-1))
        {
            return false;
        }
    }
    return true;
}

bool  is_ordered_non_strict_ascending(const std::vector<int>& nums)
{
    for (std::vector<int>::size_type i=1; i < nums.size(); ++i)
    {
        if (nums.at(i) < nums.at(i-1))
        {
            return false;
        }
    }
    return true;
}

bool is_arithmetic_series(const std::vector<int>& nums)
{
    const int d = nums.at(1) - nums.at(0);
    for (std::vector<int>::size_type i=2; i < nums.size(); ++i)
    {
        if (nums.at(i) - nums.at(i-1) != d)
        {
            return false;
        }
    }
    return true;
}

bool is_geometric_series(const std::vector<int>& nums)
{
    const double q = nums.at(1) / nums.at(0);
    for (std::vector<int>::size_type i=2; i < nums.size(); ++i)
    {
        if (nums.at(i) / nums.at(i-1) != q)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}

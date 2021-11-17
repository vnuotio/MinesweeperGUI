#include "array_operations.hh"
#include <algorithm>

int greatest_v1(int* itemptr, int size)
{
    return *std::max_element(itemptr, itemptr + size);
}

int greatest_v2(int* itemptr, int* endptr)
{
    return *std::max_element(itemptr, endptr);
}

void copy(int* itemptr, int* endptr, int* targetptr)
{
    std::copy(itemptr, endptr, targetptr);
}

void reverse(int* leftptr, int* rightptr)
{
    std::reverse(leftptr, rightptr);
}

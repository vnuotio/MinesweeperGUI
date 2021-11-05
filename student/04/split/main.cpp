#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


// TODO: Implement split function here
// Do not change main function

vector<string> split(const string& str, char sep, bool exclude_empty=false)
{
    vector<string> split_str;

    string sub;
    string::size_type c = str.find(sep);
    string::size_type prev_c = 0;

    while (c != string::npos)
    {
        sub = str.substr(prev_c, c-prev_c);
        if (not exclude_empty or (exclude_empty and sub != ""))
        {
            split_str.push_back(sub);
        }

        prev_c = c;
        c = str.find(sep, prev_c+1);
        prev_c += 1;
    }

    if (not exclude_empty or (exclude_empty and str.back() != sep))
    {
        sub = str.substr(prev_c);
        split_str.push_back(sub);
    }

    return split_str;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}

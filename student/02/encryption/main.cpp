#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string take_str()
{
    string output = "";
    cout << "Enter the encryption key: ";
    getline(cin, output);

    return output;
}

bool validate_key(string key)
{
    if (key.length() != 26)
    {
        cout << "Error! The encryption key must contain 26 characters." << endl;;
        return false;
    }
    else if (any_of(key.begin(), key.end(), &::isupper) or !all_of(key.begin(), key.end(), &::isalpha))
    {
        cout << "Error! The encryption key must contain only lower case characters." << endl;
        return false;
    }
    else
    {
        for (char c = 'a';  c < 'z'; ++c)
        {
            if (key.find(c) == string::npos)
            {
                cout << "Error! The encryption key must contain all alphabets a-z." << endl;
                return false;
            }
        }
    }
    return true;
}

int main()
{
    string key = take_str();
    if (!validate_key(key))
    {
        return EXIT_FAILURE;
    }

}

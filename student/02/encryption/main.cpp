#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string take_str(string msg)
{
    string output = "";
    cout << msg;
    getline(cin, output);

    return output;
}

bool validate_txt(string txt)
{
    if (any_of(txt.begin(), txt.end(), &::isupper) or !all_of(txt.begin(), txt.end(), &::isalpha))
    {
        cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
        return false;
    }
    return true;
}


bool validate_key(string key)
{
    if (key.length() != 26)
    {
        cout << "Error! The encryption key must contain 26 characters." << endl;;
        return false;
    }

    if (any_of(key.begin(), key.end(), &::isupper) or !all_of(key.begin(), key.end(), &::isalpha))
    {
        cout << "Error! The encryption key must contain only lower case characters." << endl;
        return false;
    }

    for (char c = 'a';  c <= 'z'; ++c)
    {
        if (key.find(c) == string::npos)
        {
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            return false;
        }
    }
    return true;
}


void encrypt(string key, string text)
{
    cout << "Encrypted text: ";

    int ind = 0;
    for (char c : text)
    {
        ind = static_cast<int>(c) - 97;
        cout << key.at(ind);
    }
    cout << endl;
}

int main()
{
    string key = take_str("Enter the encryption key: ");
    if (!validate_key(key))
    {
        return EXIT_FAILURE;
    }
    string normal_text = take_str("Enter the text to be encrypted: ");
    if (!validate_txt(normal_text))
    {
        return EXIT_FAILURE;
    }

    encrypt(key, normal_text);
    return EXIT_SUCCESS;
}

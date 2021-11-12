#include <iostream>
#include <map>
#include <fstream>

using namespace std;

int main()
{
    string fileName;
    cout << "Input file: ";
    getline(cin, fileName);

    ifstream file(fileName);
    if (not file)
    {
        cout << "Error! The file " << fileName << " cannot be opened" << endl;
        return EXIT_FAILURE;
    }

    map<string, int> scores;

    string line;
    while(getline(file, line))
    {
        size_t i = line.find(':');
        string name = line.substr(0, i);
        int score = stoi(line.substr(i+1));

        if (scores.find(name) == scores.end())
        {
            scores.insert({name, score});
        }
        else
        {
            scores.at(name) += score;
        }
    }
    file.close();

    cout << "Final scores:" << endl;
    for (auto person : scores)
    {
        cout << person.first << ": " << person.second << endl;
    }

    return EXIT_SUCCESS;
}

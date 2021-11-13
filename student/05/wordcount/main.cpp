#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>

using namespace std;

int main()
{
    string fileName;
    cout << "Input file: ";
    getline(cin, fileName);

    ifstream file(fileName);
    if (not file)
    {
        cout << "Error! The file " << fileName << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    map<string, pair<int, set<int>>> wordMap;

    string line;
    int lineNum = 0;
    while (getline(file, line))
    {
        ++lineNum;

        istringstream ss(line);
        string word;
        while(getline(ss, word, ' '))
        {
            if (wordMap.find(word) == wordMap.end())
            {
                wordMap.insert({word, pair<int, set<int>> (1, {lineNum})});
            }
            else if (wordMap.at(word).second.find(lineNum) == wordMap.at(word).second.end())
            {
                wordMap.at(word).first += 1;
                wordMap.at(word).second.insert(lineNum);
            }
        }
    }
    file.close();

    for (auto wordPair : wordMap)
    {
        cout << wordPair.first << " " << wordPair.second.first << ": ";

        string line;
        for (auto lineCount : wordPair.second.second)
        {
            line += to_string(lineCount) + ", ";
        }
        line.pop_back();
        line.pop_back();
        cout << line;
        cout << endl;
    }

    return EXIT_SUCCESS;
}

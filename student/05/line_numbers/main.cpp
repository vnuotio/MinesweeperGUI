#include <iostream>
#include <fstream>

using namespace std;

int main()
{

    string inputFileName;
    string outputFileName;

    cout << "Input file: ";
    getline(cin, inputFileName);

    cout << "Output file: ";
    getline(cin, outputFileName);

    ifstream inputFile(inputFileName);
    if (not inputFile)
    {
        cout << "Error! The file " << inputFileName << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    string lineText;
    int lineNum = 0;

    ofstream outputFile(outputFileName);

    while (getline(inputFile, lineText))
    {
        ++lineNum;
        outputFile << lineNum << " " << lineText << "\n";
    }
    inputFile.close();
    outputFile.close();
    return EXIT_SUCCESS;
}

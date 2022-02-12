#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void basicSearch();
void fileSearch(int&, char* []);

int main(int argc, char* argv[])
{
    switch (argc)
    {
        case 1:
            basicSearch();
            break;
        default:
            fileSearch(argc, argv);
            break;
    }

    return 0;
}

void basicSearch()
{
    string stringToSearch;
    string searchString;
    int found;

    cout << "Give a string from which to search for: ";
    getline(cin, stringToSearch);

    cout << "Give a search string: ";
    getline(cin, searchString);

    found = stringToSearch.find(searchString);
    
    if (found != string::npos)
        cout << endl << "\"" << searchString << "\" found in \"" << stringToSearch << "\" in position " << found << endl;
    else
        cout << endl << "\"" << searchString << "\" NOT found in \"" << stringToSearch << "\"" << endl;
}

void fileSearch(int& argc, char* argv[])
{
    string searchString;
    string fileToSearch;
    string option;
    bool showLines, showOccur = false; 

    string line;
    int lineNumber = 0;
    int occurrences = 0;

    if (argv[1][0] != '-') { // If the first letter of the first argument is not '-'
        searchString = argv[1];
        fileToSearch = argv[2];
    } else {
        searchString = argv[2];
        fileToSearch = argv[3];
        option = argv[1];
        option.erase(0, 2);
    }

    if (option.find('l') != string::npos && option.find('o') != string::npos) {
        showLines = true;
        showOccur = true;
    } else if (option.find('o') != string::npos) {
        showOccur = true;
    } else if (option.find('l') != string::npos) {
        showLines = true;
    }

    ifstream ifile;
    ifile.open(fileToSearch);

    if (ifile.fail()) {
        cout << "File couldn't be opened" << endl;
        return;
    }

    while (!ifile.eof()) {
        getline(ifile, line);
        lineNumber++;

        if (line.find(searchString) != string::npos) {
            occurrences++;

            if (showLines) {
                cout << lineNumber << ":" << line << endl;
            } else {
                cout << line << endl;
            }
        }
    }

    if (showOccur) {
        cout << endl << "Occurrences of lines containing " << searchString << ": " << occurrences << endl;
    }

    ifile.close();
}

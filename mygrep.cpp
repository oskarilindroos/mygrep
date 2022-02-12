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
    string searchString = argv[1];
    string fileToSearch = argv[2];

    string line;

    ifstream ifile;
    ifile.open(fileToSearch);

    if (ifile.fail()) {
        cout << "File couldn't be opened" << endl;
        return;
    }

    while (!ifile.eof()) {
        getline(ifile, line);
        if (line.find(searchString) != string::npos) {
            cout << line << endl;
        }
    }

    ifile.close();
}

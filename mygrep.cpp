#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void basicSearch();
void fileSearch();

int main(int argc, char* argv[])
{
    switch (argc)
    {
        case 1:
            basicSearch();
            break;
        case 2:
            fileSearch();
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

void fileSearch()
{
    ;
}

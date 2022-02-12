#include <iostream>
#include <string>

using namespace std;

int grep(string, string);

int main()
{
    string stringToSearch;
    string searchString;

    int searchResult;

    cout << "Give a string from which to search for: ";
    getline(cin, stringToSearch);

    cout << "Give a search string: ";
    getline(cin, searchString);

    searchResult = grep(stringToSearch, searchString);

    if (searchResult != string::npos) {
        cout << endl << "\""<< searchString << "\" found in \"" << stringToSearch << "\" in position " << searchResult;
    } else {
        cout << endl << searchString << " NOT found in " << stringToSearch;
    }

    return 0;
}


int grep(string stringToSearch, string searchString)
{
    return stringToSearch.find(searchString);
}

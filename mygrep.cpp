#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void basicSearch();
void fileSearch(int&, char* []);
void setOptionsFlags(bool&, bool&, bool&, bool&, string&);
void stringToLowerCase(string&);

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

    bool showLines = false;
    bool showOccur = false;
    bool reverseSearch = false; 
    bool caseSensitive = true;
    
    string line;
    int lineNumber = 0;
    int occurrences = 0;
    
    if (argv[1][0] == '-' && argv[1][1] == 'o') { // If the first letter of the first argument is not '-'
        option = argv[1];
        searchString = argv[2];
        fileToSearch = argv[3];
        option.erase(0, 2); // Erase the first two characters from given option because they are not needed
        setOptionsFlags(showLines, showOccur, reverseSearch, caseSensitive, option);

        if (!caseSensitive) {
            stringToLowerCase(searchString);
        }
    } else {
        searchString = argv[1];
        fileToSearch = argv[2];
    }

    ifstream ifile;
    ifile.open(fileToSearch);

    if (ifile.fail()) {
        cout << "File couldn't be opened" << endl;
        return;
    }

    while (!ifile.eof()) 
    {
        getline(ifile, line);
        lineNumber++;
        
        if (!reverseSearch)
        {
            if (line.find(searchString) != string::npos) 
            {
                occurrences++;

                if (showLines)
                {
                    cout << lineNumber << ":" << line << endl;
                } 
                else
                {
                    cout << line << endl;
                }
            }
        }
        else if (reverseSearch)
        {
            if (line.find(searchString) == string::npos) 
            {
                occurrences++;

                if (showLines)
                {
                    cout << lineNumber << ":" << line << endl;
                } 
                else
                {
                    cout << line << endl;
                }
            }
        }
    }

    if (showOccur && !reverseSearch) {
        cout << endl << "Occurrences of lines containing \"" << searchString << "\": " << occurrences << endl;
    } else if (showOccur && reverseSearch) {
        cout << endl << "Occurrences of lines NOT containing \"" << searchString << "\": " << occurrences << endl;
    }


    ifile.close();
}

void setOptionsFlags(bool& lines, bool& occur, bool& reverse, bool& casesens, string& option)
{
    if (option.find('o') != string::npos) {
        occur = true;
    }
    if (option.find('l') != string::npos) {
        lines = true;
    }
    if (option.find('r') != string::npos) {
        reverse = true;
    }
    if (option.find('i') != string::npos) {
        casesens = false;
    }
}

void stringToLowerCase(string& convertThis) 
{
    for (int i = 0; i < convertThis.size(); i++) {
        convertThis[i] = tolower(convertThis[i]);
    }h
}
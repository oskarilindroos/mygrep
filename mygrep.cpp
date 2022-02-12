#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void basicSearch();
void fileSearch(int&, char* []);
void setOptionsFlags(bool&, bool&, bool&, bool&, string&);
string stringToLowerCase(string);

int main(int argc, char* argv[])
{
    if (argc == 1) {
        basicSearch();
    } else {
        fileSearch(argc, argv);
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
    
    if (found != string::npos) {
        cout << endl << "\"" << searchString << "\" found in \"" << stringToSearch << "\" in position " << found << endl;
    } else {
        cout << endl << "\"" << searchString << "\" NOT found in \"" << stringToSearch << "\"" << endl;
    }
}

void fileSearch(int& argc, char* argv[])
{
    string searchString, temp_searchString, fileToSearch, option;

    bool showLines = false;
    bool showOccur = false;
    bool reverseSearch = false; 
    bool caseSensitive = true;
    
    if (argv[1][0] == '-' && argv[1][1] == 'o') {
        option = argv[1];
        searchString = argv[2];
        fileToSearch = argv[3];
        option.erase(0, 2); // Erase the first two characters from given option because they are not needed
        setOptionsFlags(showLines, showOccur, reverseSearch, caseSensitive, option);

        if (!caseSensitive) {
            //temp_searchString = stringToLowerCase(searchString);
            searchString = stringToLowerCase(searchString);
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

    int lineNumber = 0;
    int occurrences = 0;
    string temp_line, line;

    while (!ifile.eof()) {
        getline(ifile, temp_line);
        lineNumber++;

        if (!caseSensitive) {
            line = stringToLowerCase(temp_line);
        } else {
            line = temp_line;
        }
        
        if (!reverseSearch) {
            if (line.find(searchString) != string::npos) {
                occurrences++;
                
                if (showLines) {
                    cout << lineNumber << ":" << temp_line << endl;
                }    
                else {
                    cout << temp_line << endl;
                }
            }
        } else if (reverseSearch) {
            if (line.find(searchString) == string::npos) {
                occurrences++;

                if (showLines) {
                    cout << lineNumber << ":" << temp_line << endl;
                } else {
                    cout << temp_line << endl;
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
    if (option.find('o') != string::npos) occur = true;
    if (option.find('l') != string::npos) lines = true;
    if (option.find('r') != string::npos) reverse = true;
    if (option.find('i') != string::npos) casesens = false;
}

string stringToLowerCase(string convertThis) 
{
    for (int i = 0; i < convertThis.size(); i++) {
        convertThis[i] = tolower(convertThis[i]);
    }

    return convertThis;
}
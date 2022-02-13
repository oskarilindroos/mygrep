#include <iostream>
#include <string>
#include <fstream>

// Used to search string for substring if no arguments are given
void basicSearch();

// Main grep function, used to search files for substrings
void fileSearch(int&, char* []);

// Used to search for given arguments and set flag values based on them
void setOptionsFlags(bool&, bool&, bool&, bool&, std::string&);

std::string stringToLowerCase(std::string);

int main(int argc, char* argv[])
{
    if (argc <= 2) {
        basicSearch();
    } else {
        fileSearch(argc, argv);
    }

    return 0;
}

void basicSearch()
{
    std::string stringToSearch;
    std::string searchString;
    int found;

    std::cout << "Give a string from which to search for: ";
    getline(std::cin, stringToSearch);

    std::cout << "Give a search string: ";
    getline(std::cin, searchString);

    found = stringToSearch.find(searchString);
    
    if (found != std::string::npos) {
        std::cout << "\n" << "\"" << searchString << "\" found in \"" << stringToSearch << "\" in position " << found << "\n";
    } else {
        std::cout << "\n" << "\"" << searchString << "\" NOT found in \"" << stringToSearch << "\"" << "\n";
    }
}

void fileSearch(int& argc, char* argv[])
{
    std::ifstream ifile;
    std::string searchString, copy_searchString, fileToSearch, option;

    // Option/arg flags
    bool showLines = false;
    bool showOccur = false;
    bool reverseSearch = false; 
    bool caseSensitive = true;
    
    // If the first letters of the argument are '-o'
    if (argv[1][0] == '-' && argv[1][1] == 'o') {
        option = argv[1]; 
        searchString = argv[2];
        copy_searchString = argv[2]; // Save the search string to a copy. Used to print the original string without lowercase conversion
        fileToSearch = argv[3];  
        option.erase(0, 2); // Erase the first two characters from given option (-o) for easier identification later
        setOptionsFlags(showLines, showOccur, reverseSearch, caseSensitive, option);

        // If case insensitivity is given as an option, convert the search string to lowercase
        if (!caseSensitive) {
            searchString = stringToLowerCase(searchString);
        }
    } else {
        searchString = argv[1];
        copy_searchString = argv[1]; // Save the search string to a copy. Used to print the original string without lowercase conversion
        fileToSearch = argv[2];
    }

    try 
    {
        ifile.open(fileToSearch, std::ios::binary); // Open the file in binary mode to also be able to read binary files
        if (ifile.fail()) {
            throw "Could not open file \"" + fileToSearch + "\"";
        }      
    }
    catch (std::string errorMessage)
    {
        std::cout << "ERROR: \t" << errorMessage << "\n";
        exit(1);
    }

    int lineNumber = 0;
    int occurrences = 0;
    std::string temp_line, line; // temp_line is used for case insensitivity

    // Read the file line by line until we reach the end
    while (!ifile.eof()) {
        getline(ifile, temp_line);
        lineNumber++;

        if (!caseSensitive) {
            line = stringToLowerCase(temp_line);
        } else {
            line = temp_line;
        }
        
        if (!reverseSearch) { // If reverse search argument is not given, search line by line for searchString and print the line if found
            if (line.find(searchString) != std::string::npos) {
                occurrences++;
                
                if (showLines) {
                    std::cout << lineNumber << ":" << temp_line << "\n";
                }    
                else {
                    std::cout << temp_line << "\n";
                }
            }
        } else if (reverseSearch) { // If reverse search argument is given, search line by line for searchString and print the line if not found
            if (line.find(searchString) == std::string::npos) {
                occurrences++;

                if (showLines) {
                    std::cout << lineNumber << ":" << temp_line << "\n";
                } else {
                    std::cout << temp_line << "\n";
                }
            }
        }
    }
    
    if (showOccur && !reverseSearch) {
        std::cout << "\n" << "Occurrences of lines containing \"" << copy_searchString << "\": " << occurrences << "\n";
    } else if (showOccur && reverseSearch) {
        std::cout << "\n" << "Occurrences of lines NOT containing \"" << copy_searchString << "\": " << occurrences << "\n";
    }

    ifile.close();
}

void setOptionsFlags(bool& lines, bool& occur, bool& reverse, bool& casesens, std::string& option)
{
    if (option.find('o') != std::string::npos) occur = true;
    if (option.find('l') != std::string::npos) lines = true;
    if (option.find('r') != std::string::npos) reverse = true;
    if (option.find('i') != std::string::npos) casesens = false;
}

std::string stringToLowerCase(std::string convertThis) 
{
    for (int i = 0; i < convertThis.size(); i++) {
        convertThis[i] = tolower(convertThis[i]);
    }

    return convertThis;
}
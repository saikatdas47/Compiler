#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    string inputFile = "input.c";
    string outputFile = "output.c";

   
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Error opening files!" << endl;
        return 1;
    }

    char ch;
    bool insideSingleLineComment = false;
    bool insideMultiLineComment = false;
    bool insideString = false;

    string filteredCode;

    while (inFile.get(ch)) {
      
        if (insideSingleLineComment) {
            if (ch == '\n') {
                insideSingleLineComment = false;
                filteredCode += ch; // Keep the newline
            }
            continue;
        }

    
        if (insideMultiLineComment) {
            if (ch == '*' && inFile.peek() == '/') {
                inFile.get(ch); // Consume the '/'
                insideMultiLineComment = false;
            }
            continue;
        }

  
        if (ch == '/' && inFile.peek() == '/' && !insideString) {
            insideSingleLineComment = true;
            inFile.get(ch); // Consume the second '/'
            continue;
        }

        if (ch == '/' && inFile.peek() == '*' && !insideString) {
            insideMultiLineComment = true;
            inFile.get(ch); // Consume the '*'
            continue;
        }

        if (ch == '"' || ch == '\'') {
            insideString = !insideString;
        }

        
        filteredCode += ch;
    }


    string compactCode;
    bool insideSpace = false;
    for (int i = 0; i < filteredCode.length(); i++) {
        char c = filteredCode[i];
        if (isspace(c)) {
            if (!insideSpace) {
                compactCode += ' '; 
                insideSpace = true;
            }
        } else {
            compactCode += c;
            insideSpace = false;
        }
    }


    outFile << compactCode;

    
    cout << "Input File Content (" << inputFile << "):\n";
    inFile.clear(); 
    inFile.seekg(0); 
    std::cout << inFile.rdbuf();

    cout << "\n\nFiltered Output File Content (" << outputFile << "):\n";
    cout << compactCode << std::endl;

   
    inFile.close();
    outFile.close();

    return 0;
}

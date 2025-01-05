#ifndef FILE_PROCESSOR_HPP
#define FILE_PROCESSOR_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;


///////////////////////////////FILE PROCESSOR///////////////////////////////  




string processFile(const string &inputFile, const string &outputFile) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Error opening files!" << endl;
        return "";
    }

    char ch;
    bool insideSingleLineComment = false;
    bool insideMultiLineComment = false;
    bool insideString = false;

    string filteredCode;

    while (inFile.get(ch)) {
        // Handle single-line comments
        if (insideSingleLineComment) {
            if (ch == '\n') {
                insideSingleLineComment = false;
                filteredCode += ch; // Keep the newline
            }
            continue;
        }

        // Handle multi-line comments
        if (insideMultiLineComment) {
            if (ch == '*' && inFile.peek() == '/') {
                inFile.get(ch); // Consume the '/'
                insideMultiLineComment = false;
            }
            continue;
        }

        // Detect single-line comments
        if (ch == '/' && inFile.peek() == '/' && !insideString) {
            insideSingleLineComment = true;
            inFile.get(ch); // Consume the second '/'
            continue;
        }

        // Detect multi-line comments
        if (ch == '/' && inFile.peek() == '*' && !insideString) {
            insideMultiLineComment = true;
            inFile.get(ch); // Consume the '*'
            continue;
        }

        // Toggle string state for handling string literals
        if (ch == '"' || ch == '\'') {
            insideString = !insideString;
        }

        // Append valid characters to the filtered code
        filteredCode += ch;
    }

    // Compact code by removing extra spaces
    string compactCode;
    bool insideSpace = false;
    for (int i = 0; i < filteredCode.size(); i++) {
        char c = filteredCode[i];
        if (isspace(c)) {
            if (!insideSpace) {
                compactCode += ' '; // Add a single space
                insideSpace = true;
            }
        } else {
            compactCode += c;
            insideSpace = false;
        }
    }

    // Write the compact code to the output file
    outFile << compactCode;

    // Display the results
    cout << "\n\nInput File Content (" << inputFile << "):\n\n";
    inFile.clear();  // Clear the EOF flag
    inFile.seekg(0); // Reset the file pointer
    cout << inFile.rdbuf();

   // cout << "\n\nFiltered Output File Content (" << outputFile << "):\n";
    cout << compactCode << endl;
    cout << "\n................1st Pros Done.............................\n\n";
    // Close the files
    inFile.close();
    outFile.close();

    return compactCode;
 
}




/////////////////////////////LEXEME SEPARATION///////////////////////////////




// Function to check if a character is a valid operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>');
}

// Function to check if a character is a valid separator
bool isSeparator(char c) {
    return (c == ';' || c == ',' || c == '(' || c == ')' || c == '{' || c == '}');
}

// Function to separate lexemes and store them in an array
void separateLexemes(const string& input, string lexemes[], int& lexemeCount) {
    string lexeme;

    for (size_t i = 0; i < input.length(); i++) {
        char current = input[i];

        // Skip white spaces
        if (isspace(current)) {
            if (!lexeme.empty()) {
                lexemes[lexemeCount++] = lexeme;
                lexeme.clear();
            }
            continue;
        }

        // Handle operators
        if (isOperator(current)) {
            if (!lexeme.empty()) {
                lexemes[lexemeCount++] = lexeme;
                lexeme.clear();
            }
            lexemes[lexemeCount++] = string(1, current);
            continue;
        }

        // Handle separators
        if (isSeparator(current)) {
            if (!lexeme.empty()) {
                lexemes[lexemeCount++] = lexeme;
                lexeme.clear();
            }
            lexemes[lexemeCount++] = string(1, current);
            continue;
        }

        // Handle identifiers and keywords (alphanumeric or underscore)
        if (isalnum(current) || current == '_') {
            lexeme += current;
            continue;
        }

        // Handle string literals (for simplicity)
        if (current == '"') {
            if (!lexeme.empty()) {
                lexemes[lexemeCount++] = lexeme;
                lexeme.clear();
            }
            lexeme += current;  // Include opening quote
            i++;
            while (i < input.length() && input[i] != '"') {
                lexeme += input[i++];
            }
            lexeme += '"';  // Include closing quote
            lexemes[lexemeCount++] = lexeme;
            lexeme.clear();
            continue;
        }
    }

    // Add any remaining lexeme
    if (!lexeme.empty()) {
        lexemes[lexemeCount++] = lexeme;
    }
}





#endif // FILE_PROCESSOR_HPP
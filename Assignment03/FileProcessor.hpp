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


/////////////////////////////2nd///////////////////////////////


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




bool isKeyword(const string &word)
{
    const string keywords[] = {"auto", "break", "case", "char", "const", "continue", "default", "do",
                               "double", "else", "enum", "extern", "float", "for", "goto", "if",
                               "int", "long", "register", "return", "short", "signed", "sizeof",
                               "static", "struct", "switch", "typedef", "union", "unsigned", "void",
                               "volatile", "while"};
    // for (const string &keyword : keywords) {
    //     if (word == keyword)
    //         return true;
    // }
    for (int i = 0; i < keywords->length(); i++)
    {
        if (word == keywords[i])
            return true;
    }

    return false;
}

// Function to check if a string is a valid identifier
bool isIdentifier(const string &word)
{
    if (!isalpha(word[0]) && word[0] != '_')
        return false;
    for (int i = 0; i < word.length(); i++)
    {
        char c = word[i];
        if (!isalnum(c) && c != '_')
            return false;
    }
    return true;
}

bool isNumber(const string &word)
{
    bool hasDigits = false, hasDecimal = false;
    int start = (word[0] == '+' || word[0] == '-') ? 1 : 0;

    for (int i = start; i < word.length(); i++)
    {
        if (isdigit(word[i]))
        {
            hasDigits = true;
        }
        else if (word[i] == '.' && !hasDecimal)
        {
            hasDecimal = true;
        }
        else
        {
            return false;
        }
    }
    return hasDigits;
}



// Function to categorize a token
string categorizeToken(const string &token)
{
    if (isKeyword(token))
    {
        return "[kw " + token + "]";
    }
    if (isIdentifier(token))
    {
        return "[id " + token + "]";
    }
    if (isNumber(token))
    {
        return "[num " + token + "]";
    }
    if (token == ";" || token == "," || token == "'" || token == "\"")
    {
        return "[sep " + token + "]";
    }
    if (token == "(" || token == ")" || token == "{" || token == "}")
    {
        return "[par " + token + "]";
    }
    if (token == "+" || token == "-" || token == "*" || token == "/" || token == "=" ||
        token == "<" || token == ">" || token == "<=" || token == ">=" || token == "==" || token == "!=")
    {
        return "[op " + token + "]";
    }
    if (token == "#include")
    {
        return "[pp " + token + "]";
    }
    if (token[0] == '"')
    {
        return "[str " + token + "]";
    }
    return "[unkn " + token + "]";
}
// Function to categorize a token
string categorizeTokenWithouttype(const string &token)
{
    if (isKeyword(token))
    {
        return "[" + token + "]";
    }
    if (isIdentifier(token))
    {
        return "[id " + token + "]";
    }
    if (isNumber(token))
    {
        return "[" + token + "]";
    }
    if (token == ";" || token == "," || token == "'" || token == "\"")
    {
        return "[" + token + "]";
    }
    if (token == "(" || token == ")" || token == "{" || token == "}")
    {
        return "[" + token + "]";
    }
    if (token == "+" || token == "-" || token == "*" || token == "/" || token == "=" ||
        token == "<" || token == ">" || token == "<=" || token == ">=" || token == "==" || token == "!=")
    {
        return "[" + token + "]";
    }
    if (token == "include")
    {
        return "[" + token + "]";
    }
    if (token[0] == '"')
    {
        return "[" + token + "]";
    }
    return "[" + token + "]";
}



#endif // FILE_PROCESSOR_HPP
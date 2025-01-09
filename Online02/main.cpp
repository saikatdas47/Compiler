#include <iostream>
#include <cctype>
#include <cstring>
#include <string>
#include "FileProcessor.hpp"

using namespace std;

// Function to check if a string is a keyword
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

// Function to check if a string is a valid number
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

int main()
{
    // Input C++ code string
    string inputFile = "input.c";
    string outputFile = "output.c";

    // Read the processed content from the FileProcessor function
    string input = processFile(inputFile, outputFile);

    // Fixed-size array to store lexemes
    const int maxLexemes = input.length();
    string lexemes[maxLexemes];
    int lexemeCount = 0;

    // Separate lexemes and store them in the array
    separateLexemes(input, lexemes, lexemeCount);

    // Print all lexemes using loop
    cout << "\nLexemes:\n\n";
    for (int i = 0; i < lexemeCount; i++)
    {
        cout << lexemes[i] << " ";
    }
    cout << "\n\n";
    cout << "Categorized Tokens:\n\n";
    // Loop through each lexeme and categorize it
    for (int i = 0; i < lexemeCount; i++)
    {
        cout << categorizeToken(lexemes[i]) << " ";
    }
    cout << "\n\n.........................\n\n";

   


//questions: Separate array for lexemes which contain only keywords then letter_letterLetterDigitDigit then valid identifiers



    // Separate array for lexemes which contain only identifiers
    string a[maxLexemes];
    int idCount = 0;
    for (int i = 0; i < lexemeCount; i++)
    {
        if (isIdentifier(lexemes[i]))
        {
            a[idCount] = lexemes[i];
            idCount++;
        }
    }

    // Print the identifiers
    cout << "Identifiers:\n\n";
    for (int i = 0; i < idCount; i++)
    {
        cout << a[i] << " ";
    }
    cout << "\n\n";

    // Count valid identifiers based on specific criteria
    int validIdCount = 0;
    for (int i = 0; i < idCount; i++)
    {
        string id = a[i];
        if (isalpha(id[0]) && id[1] == '_' && isalpha(id[2]) && isalpha(id[3]) && (isdigit(id[4]) || isdigit(id[5])))
        {
            validIdCount++;
        }
    }
    cout << "Number of valid identifiers: " << validIdCount << "\n\n";


    return 0;
}

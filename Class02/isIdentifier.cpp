#include <iostream>
#include <string>
using namespace std;

// Function to check if the string is a keyword
bool isKeyword(const string &str) {
    string keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "int", "long", "register", "return", "short", "signed", "sizeof",
        "static", "struct", "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while", "class", "private", "public", "protected", "main"
    };
    int keywordCount = 38; // Number of C++ keywords

    for (int i = 0; i < keywordCount; i++) {
        if (str == keywords[i]) {
            return true; // It is a keyword
        }
    }
    return false; // Not a keyword
}


// Function to check if the string is an identifier
bool isIdentifier(const string &str) {
    // Start state: Check the first character
    if (str.empty() || (!isalpha(str[0]) && str[0] != '_')) {
        return false; // Invalid if the first character is not a letter or '_'
    }

    // Intermediate state: Check the rest of the characters
    for (int i = 1; i < str.length(); i++) {
        if (!isalnum(str[i]) && str[i] != '_') {
            return false; // Invalid if any character is not a letter, digit, or '_'
        }
    }

    return true; // Valid identifier
}

int main() {
    string input;
    while (true)
    {
        cout << "Enter a string: ";
    cin >> input;

    // First, check if it's a keyword
    if (isKeyword(input)) {
        cout << "'" << input << "' is a keyword and not a valid identifier." << endl;
    }
    // Then check if it's a valid identifier
    else if (isIdentifier(input)) {
        cout << "'" << input << "' is a valid identifier." << endl;
    }
    // If neither, it's invalid
    else {
        cout << "'" << input << "' is neither a keyword nor a valid identifier." << endl;
    }
    }
    
    

    return 0;
}
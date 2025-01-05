// 1. Write a program to recognize whether the entered string is a keyword or not.
#include <iostream>
#include <string>
using namespace std;

int main()
{
    // List of keywords in C++
    string keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "int", "long", "register", "return", "short", "signed", "sizeof",
        "static", "struct", "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while"};

    int keywordCount = 32; // Total number of C++ keywords
    string input;

    // Get user input
    while (true)
    {
        cout << "Enter a string: ";
        cin >> input;

        // Check if the input is a keyword
        bool isKeyword = false;
        for (int i = 0; i < keywordCount; i++)
        {
            if (input == keywords[i])
            {
                isKeyword = true;
                break;
            }
        }

        if (isKeyword)
        {
            cout << "'" << input << "' is a keyword." << endl;
        }
        else
        {
            // Check if the input is a valid identifier
            bool isIdentifier = true;

            // First character must be a letter or underscore
            if (!isalpha(input[0]) && input[0] != '_')
            {
                isIdentifier = false;
            }

            // Check the rest of the characters
            for (int i = 1; i < input.length(); i++)
            {
                if (!isalnum(input[i]) && input[i] != '_')
                {
                    isIdentifier = false;
                    break;
                }
            }

            // Display the result
            if (isIdentifier)
            {
                cout << "'" << input << "' is a valid identifier." << endl;
            }
            else
            {
                cout << "'" << input << "' is neither a keyword nor a valid identifier." << endl;
            }
        }
    }
    return 0;
}
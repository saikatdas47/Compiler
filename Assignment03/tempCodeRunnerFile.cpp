#include <iostream>
#include <vector>
#include <string>
#include "FileProcessor.hpp"

using namespace std;

// Structure to represent a symbol table entry
struct Symbol {
    int slNo;
    string name;
    string idType;
    string dataType;
    string scope;
    string value;

    // Constructor to initialize the Symbol object
    Symbol(int slNo, string name, string idType, string dataType, string scope, string value)
        : slNo(slNo), name(name), idType(idType), dataType(dataType), scope(scope), value(value) {}
};

// Function to display the symbol table
// Function to display the symbol table using a normal for loop
void displaySymbolTable(const vector<Symbol> &symbolTable) {
    cout << "Sl. No.\tName\tId Type\tData Type\tScope\tValue\n";
    for (int i = 0; i < symbolTable.size(); i++) {
        cout << symbolTable[i].slNo << "\t" << symbolTable[i].name << "\t" 
             << symbolTable[i].idType << "\t" << symbolTable[i].dataType << "\t"
             << symbolTable[i].scope << "\t" << symbolTable[i].value << "\n";
    }
}

// Function to generate the symbol table from lexemes
vector<Symbol> generateSymbolTable(const string lexemes[], int lexemeCount) {
    vector<Symbol> symbolTable;
    int slNo = 1;

    // Temporary variables to store symbol details
    string name, idType, dataType, scope, value;

    for (int i = 0; i < lexemeCount; i++) {
        if (lexemes[i] == "float" || lexemes[i] == "int" || lexemes[i] == "double") {
            // Data type
            dataType = lexemes[i];

            // Name
            if (i + 1 < lexemeCount) {
                name = lexemes[i + 1];
            }

            // Scope and ID type
            if (name == "main") {
                idType = "func";
                scope = "global";
                value = "";
            } else {
                idType = "var";
                scope = (i > 0 && lexemes[i - 1] == "global") ? "global" : "local";
            }

            // Value (if assigned)
            if (i + 3 < lexemeCount && lexemes[i + 2] == "=") {
                value = lexemes[i + 3];
            } else {
                value = "";
            }

            // Add entry to the symbol table using the constructor
            symbolTable.push_back(Symbol(slNo++, name, idType, dataType, scope, value));
        }

        // Function declaration
        if (lexemes[i] == "void" || lexemes[i] == "int" || lexemes[i] == "double" || lexemes[i] == "float") {
            if (i + 1 < lexemeCount && lexemes[i + 1] == "main") {
                name = "main";
                idType = "func";
                dataType = lexemes[i];
                scope = "global";
                value = "";

                // Add entry to the symbol table using the constructor
                symbolTable.push_back(Symbol(slNo++, name, idType, dataType, scope, value));
            }
        }
    }

    return symbolTable;
}

int main() {
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

    // Print all lexemes using a loop
    cout << "\nLexemes:\n\n";
    for (int i = 0; i < lexemeCount; i++) {
        cout << lexemes[i] << " ";
    }

    cout << "\n\nCategorized Tokens:\n\n";
    // Loop through each lexeme and categorize it
    string token[maxLexemes];
    for (int i = 0; i < lexemeCount; i++) {
        token[i] = categorizeTokenWithouttype(lexemes[i]);
        cout << token[i] << " ";
    }
    cout << "\n\n";

    // Store lexemes into another array
    string a[maxLexemes];
    for (int i = 0; i < lexemeCount; i++) {
        a[i] = lexemes[i];
    }

    cout << "\nStored Lexemes in Array `a`:\n\n";
    for (int i = 0; i < lexemeCount; i++) {
        cout << a[i] << " ";
    }
    cout << "\n\n"<<lexemeCount<<"\n\n";

    // Generate the symbol table
    vector<Symbol> symbolTable = generateSymbolTable(a, lexemeCount);

    // Display the symbol table
    displaySymbolTable(symbolTable);

    return 0;
}
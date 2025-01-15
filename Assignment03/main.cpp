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

    Symbol(int slNo, string name, string idType, string dataType, string scope, string value)
        : slNo(slNo), name(name), idType(idType), dataType(dataType), scope(scope), value(value) {}
};

// Global vector to represent the symbol table
vector<Symbol> symbolTable;

// Function to insert a name in the symbol table
void insert(const Symbol &symbol) {
    symbolTable.push_back(symbol);
    cout << "Inserted: " << symbol.name << endl;
}

// Function to set an attribute for an existing entry
void set_attribute(int slNo, const string &attribute, const string &value) {
    for (int i = 0; i < symbolTable.size(); i++) {
        if (symbolTable[i].slNo == slNo) {
            if (attribute == "name") symbolTable[i].name = value;
            else if (attribute == "idType") symbolTable[i].idType = value;
            else if (attribute == "dataType") symbolTable[i].dataType = value;
            else if (attribute == "scope") symbolTable[i].scope = value;
            else if (attribute == "value") symbolTable[i].value = value;
            cout << "Attribute updated for entry " << slNo << endl;
            return;
        }
    }
    cout << "Entry not found for slNo: " << slNo << endl;
}

// Function to free the entire symbol table
void free_table() {
    symbolTable.clear();
    cout << "Symbol table cleared." << endl;
}

// Function to lookup a name in the symbol table
Symbol* lookup(const string &name) {
    for (int i = 0; i < symbolTable.size(); i++) {
        if (symbolTable[i].name == name) {
            return &symbolTable[i];
        }
    }
    cout << "Entry not found: " << name << endl;
    return nullptr;
}

// Function to display the entire symbol table
void display() {
    cout << "Sl. No.\tName\tId Type\tData Type\tScope\tValue\n";
    for (int i = 0; i < symbolTable.size(); i++) {
        cout << symbolTable[i].slNo << "\t" << symbolTable[i].name << "\t" << symbolTable[i].idType << "\t"
             << symbolTable[i].dataType << "        \t" << symbolTable[i].scope << " \t" << symbolTable[i].value << "\n";
    }
}

// Function to generate the symbol table from lexemes
vector<Symbol> generateSymbolTable(const string lexemes[], int lexemeCount) {
    vector<Symbol> generatedTable;
    int slNo = 1;

    string name, idType, dataType, scope, value;

    for (int i = 0; i < lexemeCount; i++) {
        if (lexemes[i] == "float" || lexemes[i] == "int" || lexemes[i] == "double") {
            dataType = lexemes[i];
            if (i + 1 < lexemeCount) {
                name = lexemes[i + 1];
            }
            idType = (name == "main") ? "func" : "var";
            scope = (idType == "func") ? "global" : "local";

            if (i + 3 < lexemeCount && lexemes[i + 2] == "=") {
                value = lexemes[i + 3];
            } else {
                value = "";
            }

            generatedTable.push_back(Symbol(slNo++, name, idType, dataType, scope, value));
        }
    }

    return generatedTable;
}

int main() {
    string inputFile = "input.c";
    string outputFile = "output.c";
    string input = processFile(inputFile, outputFile);

    const int maxLexemes = input.length();
    string lexemes[maxLexemes];
    int lexemeCount = 0;

    separateLexemes(input, lexemes, lexemeCount);

    cout << "\nLexemes:\n\n";
    for (int i = 0; i < lexemeCount; i++) {
        cout << lexemes[i] << " ";
    }
    cout << "\n\n";

    vector<Symbol> generatedTable = generateSymbolTable(lexemes, lexemeCount);

    for (int i = 0; i < generatedTable.size(); i++) {
        insert(generatedTable[i]);
    }

    cout << "\nInitial Symbol Table:\n";
    display();

    set_attribute(1, "value", "42");

    cout << "\nUpdated Symbol Table:\n";
    display();

    Symbol* foundSymbol = lookup("main");
    if (foundSymbol) {
        cout << "\nFound Symbol: " << foundSymbol->name << ", Scope: " << foundSymbol->scope << endl;
    }

    free_table();

    cout << "\nSymbol Table After Clearing:\n";
    display();

    return 0;
}
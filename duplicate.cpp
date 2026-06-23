#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <cctype>
using namespace std;

// Keywords list
vector<string> keywords = {
    "int", "float", "char", "double", "if", "else",
    "for", "while", "return"
};

set<string> symbolTable;

// Check keyword
bool isKeyword(string word) {
    for (string key : keywords) {
        if (word == key)
            return true;
    }
    return false;
}

// Check valid identifier
bool isValidIdentifier(string word) {
    if (word.empty())
        return false;

    if (!(isalpha(word[0]) || word[0] == '_'))
        return false;

    for (char ch : word) {
        if (!(isalnum(ch) || ch == '_'))
            return false;
    }

    return true;
}

int main() {
    string code, line;
    bool foundDuplicate = false;

    cout << "Enter source code (type END to stop):\n";

    while (getline(cin, line)) {
        if (line == "END")
            break;
        code += line + " ";
    }

    stringstream ss(code);
    string token;

    while (ss >> token) {
        // Remove symbols
        while (!token.empty() &&
              (token.back() == ';' || token.back() == ',' ||
               token.back() == '(' || token.back() == ')' ||
               token.back() == '{' || token.back() == '}')) {
            token.pop_back();
        }

        if (!isKeyword(token) && isValidIdentifier(token)) {
            if (symbolTable.find(token) != symbolTable.end()) {
                cout << "Duplicate Identifier: " << token << endl;
                foundDuplicate = true;
            } else {
                symbolTable.insert(token);
            }
        }
    }

    if (!foundDuplicate) {
        cout << "No duplicate identifiers found." << endl;
    }

    return 0;
}
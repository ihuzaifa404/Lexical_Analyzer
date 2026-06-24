#include <iostream>
#include <sstream>
#include <set>
using namespace std;

int main() {
    string code, line, token;
    set<string> identifiers;

    cout << "Enter source code (type END to stop):\n";

    while (getline(cin, line)) {
        if (line == "END")
            break;
        code += line + " ";
    }

    stringstream ss(code);

    while (ss >> token) {
        // Remove semicolon if present
        if (token.back() == ';')
            token.pop_back();

        // Check duplicate
        if (identifiers.find(token) != identifiers.end()) {
            cout << "Duplicate Identifier: " << token << endl;
        } else {
            identifiers.insert(token);
        }
    }

    return 0;
}
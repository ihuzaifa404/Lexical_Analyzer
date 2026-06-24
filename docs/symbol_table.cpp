#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <iomanip> // Used for clean table alignment

using namespace std;


struct Token {
    string value;
    string type;
    int line;
};

struct SymbolEntry {
    string name;
    string type;
};

bool isKeyword(const string& str) {
    vector<string> keywords = {"int", "double", "float", "char", "if", "else", "while", "return", "void", "main"};
    for (const string& kw : keywords) {
        if (str == kw) return true;
    }
    return false;
}

bool isAllowedSymbol(char ch) {
    string allowed = "+-*/%=;(){}[],.<>!&|";
    return allowed.find(ch) != string::npos;
}

bool validateToken(const string& str, int line_num) {
    if (str.empty()) return false;

    if (isdigit(str[0])) {
        bool has_letter = false;
        for (char ch : str) {
            if (isalpha(ch)) { has_letter = true; break; }
        }
        if (has_letter) {
            cout << "[Lexical Error] Line " << line_num << ": Invalid token -> \"" << str << "\"\n";
            return false;
        }
    }

    for (char ch : str) {
        if (!isalnum(ch) && !isspace(ch) && !isAllowedSymbol(ch)) {
            cout << "[Lexical Error] Line " << line_num << ": Unknown symbol -> \"" << ch << "\" in \"" << str << "\"\n";
            return false;
        }
    }
    return true;
}

int main() {
    cout << "========================================================\n";
    cout << "       COMPILER CONSTRUCTION: OUTPUT & SYMBOL TABLE     \n";
    cout << "========================================================\n";
    cout << "Paste your code below. Type 'END' on a new line to finish:\n\n";

    vector<string> input_lines;
    string current_line;

    while (getline(cin, current_line)) {
        if (current_line == "END") break;
        input_lines.push_back(current_line);
    }

    vector<Token> validated_tokens;
    vector<SymbolEntry> symbol_table;

    cout << "\n--- [Step 1] Running Error Scans ---\n";

    for (int i = 0; i < input_lines.size(); ++i) {
        int current_line_num = i + 1;
        stringstream ss(input_lines[i]);
        string token_str;
        
        while (ss >> token_str) {
            string clean_token = "";
            for (char ch : token_str) {
                if (isAllowedSymbol(ch)) {
                    if (!clean_token.empty()) {
                        if (validateToken(clean_token, current_line_num)) {
                            string type = isKeyword(clean_token) ? "KEYWORD" : (isdigit(clean_token[0]) ? "NUMBER" : "IDENTIFIER");
                            validated_tokens.push_back({clean_token, type, current_line_num});
                        }
                        clean_token = "";
                    }
                    string symbol_str(1, ch);
                    if (validateToken(symbol_str, current_line_num)) {
                        validated_tokens.push_back({symbol_str, "OPERATOR/PUNCTUATION", current_line_num});
                    }
                } else {
                    clean_token += ch;
                }
            }
            if (!clean_token.empty()) {
                if (validateToken(clean_token, current_line_num)) {
                    string type = isKeyword(clean_token) ? "KEYWORD" : (isdigit(clean_token[0]) ? "NUMBER" : "IDENTIFIER");
                    validated_tokens.push_back({clean_token, type, current_line_num});
                }
            }
        }
    }

    for (const auto& tok : validated_tokens) {
        if (tok.type == "IDENTIFIER" && tok.value != "main") {
            bool exists = false;
            for (const auto& entry : symbol_table) {
                if (entry.name == tok.value) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                symbol_table.push_back({tok.value, "VARIABLE"});
            }
        }
    }

    cout << "\n========================================================\n";
    cout << "                 FINAL VALIDATED TOKENS                 \n";
    cout << "========================================================\n";
    cout << left << setw(20) << "TOKEN VALUE" << setw(25) << "TOKEN TYPE" << setw(10) << "LINE NO" << "\n";
    cout << "--------------------------------------------------------\n";
    
    for (const auto& tok : validated_tokens) {
        cout << left << setw(20) << tok.value 
             << setw(25) << tok.type 
             << setw(10) << tok.line << "\n";
    }
    cout << "========================================================\n";

    cout << "\n========================================================\n";
    cout << "                      SYMBOL TABLE                      \n";
    cout << "========================================================\n";
    if (symbol_table.empty()) {
        cout << " (No identifiers / variables found to store) \n";
    } else {
        cout << left << setw(25) << "IDENTIFIER NAME" << setw(25) << "SYMBOL TYPE" << "\n";
        cout << "--------------------------------------------------------\n";
        for (const auto& entry : symbol_table) {
            cout << left << setw(25) << entry.name 
                 << setw(25) << entry.type << "\n";
        }
    }
    cout << "========================================================\n";

    return 0;
}
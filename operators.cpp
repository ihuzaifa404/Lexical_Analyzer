#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Define the structure for a Token
struct Token {
    string type;
    string value;
    int line;
};

class OperatorSymbolLexer {
private:
    string source;
    size_t index;
    int current_line;

    // Helper to get the current character
    char currentChar() {
        if (index >= source.length()) return '\0';
        return source[index];
    }

    // Helper to peek at the next character without consuming it
    char peekNextChar() {
        if (index + 1 >= source.length()) return '\0';
        return source[index + 1];
    }

    // Move the index forward by one character
    void advance() {
        index++;
    }

public:
    OperatorSymbolLexer(string src) {
        source = src;
        index = 0;
        current_line = 1;
    }

    // This function handles your part of the project
    Token getOperatorOrSymbol() {
        char ch = currentChar();

        // Track line numbers if we encounter a newline
        if (ch == '\n') {
            current_line++;
            advance();
            return Token{"NEWLINE", "\\n", current_line - 1};
        }

        // 1. SPECIAL SYMBOLS (Single Character)
        if (ch == ';') { advance(); return Token{"SEMICOLON", ";", current_line}; }
        if (ch == '{') { advance(); return Token{"LBRACE", "{", current_line}; }
        if (ch == '}') { advance(); return Token{"RBRACE", "}", current_line}; }
        if (ch == '(') { advance(); return Token{"LPAREN", "(", current_line}; }
        if (ch == ')') { advance(); return Token{"RPAREN", ")", current_line}; }
        if (ch == '[') { advance(); return Token{"LBRACKET", "[", current_line}; }
        if (ch == ']') { advance(); return Token{"RBRACKET", "]", current_line}; }

        // 2. ARITHMETIC OPERATORS
        if (ch == '+') { advance(); return Token{"PLUS", "+", current_line}; }
        if (ch == '-') { advance(); return Token{"MINUS", "-", current_line}; }
        if (ch == '*') { advance(); return Token{"MULTIPLY", "*", current_line}; }
        if (ch == '/') { advance(); return Token{"DIVIDE", "/", current_line}; }
        if (ch == '%') { advance(); return Token{"MODULO", "%", current_line}; }

        // 3. RELATIONAL OPERATORS (Requires Lookahead)
        if (ch == '=') {
            if (peekNextChar() == '=') {
                advance(); advance(); // consume both '='
                return Token{"EQ", "==", current_line};
            }
            // If your language uses a single '=' for assignment, handle it here
            advance();
            return Token{"ASSIGN", "=", current_line};
        }
        if (ch == '!') {
            if (peekNextChar() == '=') {
                advance(); advance();
                return Token{"NEQ", "!=", current_line};
            }
            advance();
            return Token{"NOT", "!", current_line};
        }
        if (ch == '<') {
            if (peekNextChar() == '=') {
                advance(); advance();
                return Token{"LE", "<=", current_line};
            }
            advance();
            return Token{"LT", "<", current_line};
        }
        if (ch == '>') {
            if (peekNextChar() == '=') {
                advance(); advance();
                return Token{"GE", ">=", current_line};
            }
            advance();
            return Token{"GT", ">", current_line};
        }

        // 4. LOGICAL OPERATORS (Requires Lookahead)
        if (ch == '&') {
            if (peekNextChar() == '&') {
                advance(); advance();
                return Token{"AND", "&&", current_line};
            }
            advance();
            return Token{"ERROR", "&", current_line}; // Single '&' is invalid
        }
        if (ch == '|') {
            if (peekNextChar() == '|') {
                advance(); advance();
                return Token{"OR", "||", current_line};
            }
            advance();
            return Token{"ERROR", "|", current_line}; // Single '|' is invalid
        }

        // If it's a space, letter, or number, let other team members' modules handle it
        advance();
        return Token{"UNKNOWN_OR_SKIP", string(1, ch), current_line};
    }

    bool isFinished() {
        return index >= source.length();
    }
};

int main() {
    // Testing your module with a mix of operators and symbols
    string code = "if (a == b && c != d) { x = y + z; }";
    
    OperatorSymbolLexer lexer(code);
    
    cout << "--- Extracted Operators & Symbols ---" << endl;
    while (!lexer.isFinished()) {
        Token t = lexer.getOperatorOrSymbol();
        
        // Only print the tokens your module cares about
        if (t.type != "UNKNOWN_OR_SKIP" && t.type != "NEWLINE") {
            cout << "Type: " << t.type << "\t | Value: " << t.value << "\t | Line: " << t.line << endl;
        }
    }
    
    return 0;
} 
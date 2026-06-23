// main.cpp
#include <iostream>
#include <vector>
#include <string>
#include "Token.h"

// Forward Declarations (Baqi members ke functions)
std::string preprocessCode(const std::string& filename);
bool isKeyword(const std::string& str);
bool isIdentifier(const std::string& str);
bool isOperator(char ch);
bool isSymbol(char ch);
void handleError(int line, const std::string& invalidToken);
void displayTokens(const std::vector<Token>& tokens);

std::vector<Token> tokenize(const std::string& sourceCode) {
    std::vector<Token> tokens;
    std::string currentLexeme = "";
    int currentLine = 1;
    size_t i = 0;

    while (i < sourceCode.length()) {
        char ch = sourceCode[i];

        if (ch == '\n') { currentLine++; i++; continue; }
        if (isspace(ch)) { i++; continue; }

        // Operators & Symbols
        if (isOperator(ch) || isSymbol(ch)) {
            std::string op(1, ch);
            TokenType type = isOperator(ch) ? TOKEN_OPERATOR : TOKEN_SYMBOL;
            tokens.push_back({type, op, currentLine});
            i++; continue;
        }

        // Keywords & Identifiers
        if (isalnum(ch) || ch == '_') {
            currentLexeme = "";
            while (i < sourceCode.length() && (isalnum(sourceCode[i]) || sourceCode[i] == '_' || sourceCode[i] == '.')) {
                currentLexeme += sourceCode[i];
                i++;
            }
            if (isKeyword(currentLexeme)) tokens.push_back({TOKEN_KEYWORD, currentLexeme, currentLine});
            else if (isIdentifier(currentLexeme)) tokens.push_back({TOKEN_IDENTIFIER, currentLexeme, currentLine});
            else {
                tokens.push_back({TOKEN_ERROR, currentLexeme, currentLine});
                handleError(currentLine, currentLexeme);
            }
            continue;
        }
        i++;
    }
    return tokens;
}

int main() {
    std::string cleanCode = preprocessCode("input.txt");
    if (cleanCode.empty()) return 1;

    std::vector<Token> tokenList = tokenize(cleanCode);
    displayTokens(tokenList);
    return 0;
}
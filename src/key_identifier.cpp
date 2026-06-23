#include <iostream>
#include <string>
#include <unordered_set>
#include <cctype>

using namespace std;

enum class TokenType
{
    KEYWORD,
    IDENTIFIER,
    INVALID_IDENTIFIER
};

const unordered_set<string> KEYWORDS =
{
    "int", "float", "double", "char", "bool",
    "if", "else", "for", "while", "do",
    "switch", "case", "break", "continue",
    "return", "void", "class", "public",
    "private", "protected", "const",
    "static", "string"
};

bool isKeyword(const string& token)
{
    return KEYWORDS.find(token) != KEYWORDS.end();
}

bool isIdentifier(const string& token)
{
    if (token.empty())
        return false;

    if (!(isalpha(token[0]) || token[0] == '_'))
        return false;

    for (char ch : token)
    {
        if (!(isalnum(ch) || ch == '_'))
            return false;
    }

    return !isKeyword(token);
}

TokenType classifyWord(const string& token)
{
    if (isKeyword(token))
        return TokenType::KEYWORD;

    if (isIdentifier(token))
        return TokenType::IDENTIFIER;

    return TokenType::INVALID_IDENTIFIER;
}

string tokenTypeToString(TokenType type)
{
    switch (type)
    {
        case TokenType::KEYWORD:
            return "KEYWORD";
        case TokenType::IDENTIFIER:
            return "IDENTIFIER";
        case TokenType::INVALID_IDENTIFIER:
            return "INVALID_IDENTIFIER";
        default:
            return "UNKNOWN";
    }
}

int main()
{
    int n;
    
    cout << "Enter number of tokens: ";
    cin >> n;

    string token;

    cout << "\nEnter tokens:\n";

    for (int i = 0; i < n; i++)
    {
        cin >> token;

        cout << token << " --> "
             << tokenTypeToString(classifyWord(token))
             << endl;
    }

    return 0;
}
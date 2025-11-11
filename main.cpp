#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <unordered_set>
using namespace std;
enum class TokenType {
    Keyword,
    Identifier,
    Number,
    Operator,
    Punctuation,
    Unknown
};
unordered_set<string> keywords = {
    "int", "float", "double", "char", "return", "for", "while", "if", "else",
    "switch", "case", "break", "continue", "void", "using", "namespace",
    "include", "std", "main", "cout", "cin", "class", "public", "private",
    "true", "false", "bool"
};

TokenType identifyToken(const string &token) {
    if (keywords.count(token)) return TokenType::Keyword;

    bool isNum = true;
    for (char c : token) {
        if (!isdigit(c) && c != '.') { isNum = false; break; }
    }
    if (isNum) return TokenType::Number;

    if (token == "+" || token == "-" || token == "*" || token == "/" ||
        token == "=" || token == "==" || token == "++" || token == "--" ||
        token == "<" || token == ">" || token == "<=" || token == ">=")
        return TokenType::Operator;

    if (token == ";" || token == "," || token == "(" || token == ")" ||
        token == "{" || token == "}" )
        return TokenType::Punctuation;


    if (isalpha(token[0]) || token[0] == '_') return TokenType::Identifier;

    return TokenType::Unknown;
}


void processLine(const string &line, int lineNum) {
    vector<string> tokens;
    string token;


    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        if (isspace(c)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else if (ispunct(c) && c != '_' && c != '#') {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            string punct(1, c);
            tokens.push_back(punct);
        } else {
            token += c;
        }
    }
    if (!token.empty()) tokens.push_back(token);

    cout << "\nLine " << lineNum << " -> " << tokens.size() << " tokens found:\n";

    for (auto &t : tokens) {
        TokenType tt = identifyToken(t);
        string typeName;
        switch (tt) {
            case TokenType::Keyword: typeName = "Keyword"; break;
            case TokenType::Identifier: typeName = "Identifier"; break;
            case TokenType::Number: typeName = "Constant"; break;
            case TokenType::Operator: typeName = "Operator"; break;
            case TokenType::Punctuation: typeName = "Punctuation"; break;
            default: typeName = "Unknown"; break;
        }


        cout << "  " << t << "  ->  " << typeName << '\n';
    }
}

int main() {
    ifstream fin("text.txt");
    if (!fin) {
        cerr << "File open failed!\n";
        return 1;
    }

    string line;
    int lineNum = 1;
    while (getline(fin, line)) {
        processLine(line, lineNum);
        lineNum++;
    }

    fin.close();
    return 0;
}

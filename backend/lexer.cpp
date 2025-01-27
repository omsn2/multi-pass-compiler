#include "lexer.h"
#include <cctype>
#include <iostream>

std::vector<Token> Lexer::tokenize(const std::string& source_code) {
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < source_code.length()) {
        char c = source_code[i];
        if (std::isspace(c)) { i++; continue; }
        if (std::isalpha(c) || c == '_') {
            size_t start = i;
            while (i < source_code.length() && (std::isalnum(source_code[i]) || source_code[i] == '_')) i++;
            tokens.push_back({"IDENTIFIER", source_code.substr(start, i - start)});
            continue;
        }
        if (std::isdigit(c)) {
            size_t start = i;
            while (i < source_code.length() && std::isdigit(source_code[i])) i++;
            tokens.push_back({"NUMBER", source_code.substr(start, i - start)});
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=') {
            tokens.push_back({"OPERATOR", std::string(1, c)});
            i++;
            continue;
        }
        if (c == '{' || c == '}') {
    tokens.push_back({"SYMBOL", std::string(1, c)});
    i++;
    continue;
}

        if (c == '(' || c == ')' || c == ';') {
            tokens.push_back({"SYMBOL", std::string(1, c)});
            i++;
            continue;
        }
        std::cerr << "Error: Unrecognized character '" << c << "'\n";
        i++;
    }

    return tokens;
}

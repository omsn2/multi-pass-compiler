#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "../common/tokens.h" // Use Token from common header

class Lexer {
public:
    std::vector<Token> tokenize(const std::string& source_code);
};

#endif

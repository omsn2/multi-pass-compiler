#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "../common/tokens.h"
#include <vector>
#include <string>

class Parser {
public:
    // Main function to parse tokens into an AST
    ASTNode* parse(const std::vector<Token>& tokens);

private:
    // Function to parse a block (e.g., { ... })
    ASTNode* parseBlock(const std::vector<Token>& tokens, size_t& i);

    // Function to parse a single statement (e.g., int x; x = 1;)
    ASTNode* parseStatement(const std::vector<Token>& tokens, size_t& i);

    // Function to parse expressions
    ASTNode* parseExpression(const std::vector<Token>& tokens, size_t& i);

    // Helper functions for expression parsing
    ASTNode* parseTerm(const std::vector<Token>& tokens, size_t& i);
    ASTNode* parseFactor(const std::vector<Token>& tokens, size_t& i);
};

#endif

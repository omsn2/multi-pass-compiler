#include "parser.h"
#include <iostream>

// Helper function to print the AST


// Parser Implementation
ASTNode* Parser::parse(const std::vector<Token>& tokens) {
    ASTNode* root = new ASTNode("Program");

    size_t i = 0;
    while (i < tokens.size()) {
        if (tokens[i].value == "int" && i + 2 < tokens.size() &&
            tokens[i + 1].type == "IDENTIFIER" && tokens[i + 2].value == "(") {
            // Function Declaration: int main() { ... }
            ASTNode* functionNode = new ASTNode("FUNCTION", tokens[i + 1].value);
            i += 3; // Skip 'int', IDENTIFIER, and '('

            if (i < tokens.size() && tokens[i].value == ")") {
                i++; // Skip ')'
            } else {
                std::cerr << "Error: Missing closing ')' in function declaration." << std::endl;
                delete root;
                return nullptr;
            }

            if (i < tokens.size() && tokens[i].value == "{") {
                // Parse the block
                ASTNode* blockNode = parseBlock(tokens, i);
                if (blockNode) {
                    functionNode->children.push_back(blockNode);
                } else {
                    delete root;
                    delete functionNode;
                    return nullptr;
                }
            } else {
                std::cerr << "Error: Missing '{' after function declaration." << std::endl;
                delete root;
                delete functionNode;
                return nullptr;
            }

            root->children.push_back(functionNode);
        } else {
            // Parse standalone statements (e.g., int x; x = 1;)
            ASTNode* statementNode = parseStatement(tokens, i);
            if (statementNode) {
                root->children.push_back(statementNode);
            } else {
                delete root;
                return nullptr;
            }
        }
    }

    return root;
}

ASTNode* Parser::parseBlock(const std::vector<Token>& tokens, size_t& i) {
    if (tokens[i].value != "{") {
        std::cerr << "Error: Expected '{' at the beginning of block." << std::endl;
        return nullptr;
    }
    i++; // Skip '{'

    ASTNode* blockNode = new ASTNode("BLOCK");

    while (i < tokens.size() && tokens[i].value != "}") {
        ASTNode* child = parseStatement(tokens, i);
        if (child) {
            blockNode->children.push_back(child);
        } else {
            delete blockNode;
            return nullptr;
        }
    }

    if (i < tokens.size() && tokens[i].value == "}") {
        i++; // Skip '}'
        return blockNode;
    } else {
        std::cerr << "Error: Missing closing '}' for block." << std::endl;
        delete blockNode;
        return nullptr;
    }
}

ASTNode* Parser::parseStatement(const std::vector<Token>& tokens, size_t& i) {
    if (tokens[i].value == "int") {
        // Variable Declaration: int x;
        if (i + 1 < tokens.size() && tokens[i + 1].type == "IDENTIFIER") {
            ASTNode* declarationNode = new ASTNode("DECLARATION", "int");
            declarationNode->children.push_back(new ASTNode("IDENTIFIER", tokens[i + 1].value));
            i += 2; // Skip 'int' and IDENTIFIER

            if (i < tokens.size() && tokens[i].value == ";") {
                i++; // Skip the semicolon
                return declarationNode;
            } else {
                std::cerr << "Error: Missing semicolon in declaration." << std::endl;
                delete declarationNode;
                return nullptr;
            }
        } else {
            std::cerr << "Error: Expected identifier after 'int'." << std::endl;
            return nullptr;
        }
    } else if (tokens[i].type == "IDENTIFIER" && i + 1 < tokens.size() && tokens[i + 1].value == "=") {
        // Assignment: IDENTIFIER = expression;
        ASTNode* assignmentNode = new ASTNode("ASSIGNMENT", "=");
        assignmentNode->children.push_back(new ASTNode("IDENTIFIER", tokens[i].value));

        i += 2; // Skip IDENTIFIER and '='
        assignmentNode->children.push_back(parseExpression(tokens, i));

        if (i < tokens.size() && tokens[i].value == ";") {
            i++; // Skip the semicolon
            return assignmentNode;
        } else {
            std::cerr << "Error: Missing semicolon in assignment." << std::endl;
            delete assignmentNode;
            return nullptr;
        }
    } else {
        std::cerr << "Error: Unexpected token " << tokens[i].value << std::endl;
        return nullptr;
    }
}

ASTNode* Parser::parseExpression(const std::vector<Token>& tokens, size_t& i) {
    ASTNode* left = parseTerm(tokens, i);

    while (i < tokens.size() && (tokens[i].value == "+" || tokens[i].value == "-")) {
        ASTNode* operatorNode = new ASTNode("OPERATOR", tokens[i].value);
        i++;
        operatorNode->children.push_back(left);
        operatorNode->children.push_back(parseTerm(tokens, i));
        left = operatorNode;
    }

    return left;
}

ASTNode* Parser::parseTerm(const std::vector<Token>& tokens, size_t& i) {
    ASTNode* left = parseFactor(tokens, i);

    while (i < tokens.size() && (tokens[i].value == "*" || tokens[i].value == "/")) {
        ASTNode* operatorNode = new ASTNode("OPERATOR", tokens[i].value);
        i++;
        operatorNode->children.push_back(left);
        operatorNode->children.push_back(parseFactor(tokens, i));
        left = operatorNode;
    }

    return left;
}

ASTNode* Parser::parseFactor(const std::vector<Token>& tokens, size_t& i) {
    if (tokens[i].type == "NUMBER") {
        ASTNode* numberNode = new ASTNode("NUMBER", tokens[i].value);
        i++;
        return numberNode;
    } else if (tokens[i].type == "IDENTIFIER") {
        ASTNode* identifierNode = new ASTNode("IDENTIFIER", tokens[i].value);
        i++;
        return identifierNode;
    } else if (tokens[i].value == "(") {
        i++;
        ASTNode* expr = parseExpression(tokens, i);
        if (i < tokens.size() && tokens[i].value == ")") {
            i++;
            return expr;
        } else {
            std::cerr << "Error: Missing closing parenthesis" << std::endl;
            delete expr;
            return nullptr;
        }
    } else {
        std::cerr << "Error: Unexpected token " << tokens[i].value << std::endl;
        return nullptr;
    }
}

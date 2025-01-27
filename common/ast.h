#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <iostream>

struct ASTNode {
    std::string type;               // Node type (e.g., PROGRAM, OPERATOR, NUMBER)
    std::string value;              // Node value (e.g., "+", "5")
    std::vector<ASTNode*> children; // Child nodes

    ASTNode(const std::string& type, const std::string& value = "")
        : type(type), value(value) {}

    ~ASTNode() {
        for (auto child : children) {
            delete child;
        }
    }
};

// Declaration of the printAST function
void printAST(ASTNode* node, int depth = 0);

#endif

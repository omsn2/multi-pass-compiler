#include "codegen.h"
#include <iostream>

void CodeGen::reset() {
    tempVarCount = 0; // Reset temporary variable counter
}

void CodeGen::generate(ASTNode* root) {
    if (!root) return;

    for (auto child : root->children) {
        if (child->type == "FUNCTION") {
            generateFunction(child);
        } else if (child->type == "DECLARATION") {
            generateDeclaration(child);
        } else if (child->type == "ASSIGNMENT") {
            generateAssignment(child);
        } else if (child->type == "BLOCK") {
            generateBlock(child);
        } else {
            std::cerr << "Error: Unsupported node type in Program: " << child->type << std::endl;
        }
    }
}

void CodeGen::generateFunction(ASTNode* node) {
    std::cout << "Function: " << node->value << std::endl;

    for (auto child : node->children) {
        if (child->type == "BLOCK") {
            generateBlock(child);
        } else {
            std::cerr << "Error: Unsupported node type in Function: " << child->type << std::endl;
        }
    }
}

void CodeGen::generateBlock(ASTNode* node) {
    std::cout << "{" << std::endl;
    for (auto child : node->children) {
        if (child->type == "DECLARATION") {
            generateDeclaration(child);
        } else if (child->type == "ASSIGNMENT") {
            generateAssignment(child);
        } else {
            std::cerr << "Error: Unsupported node type in Block: " << child->type << std::endl;
        }
    }
    std::cout << "}" << std::endl;
}

void CodeGen::generateDeclaration(ASTNode* node) {
    if (node->children.size() != 1 || node->children[0]->type != "IDENTIFIER") {
        std::cerr << "Error: Invalid DECLARATION node structure." << std::endl;
        return;
    }

    ASTNode* identifier = node->children[0];
    std::cout << "DECLARE " << identifier->value << std::endl;
}

void CodeGen::generateAssignment(ASTNode* node) {
    if (node->children.size() != 2) {
        std::cerr << "Error: Invalid ASSIGNMENT node structure." << std::endl;
        return;
    }

    ASTNode* lhs = node->children[0];
    if (lhs->type != "IDENTIFIER") {
        std::cerr << "Error: Left-hand side of ASSIGNMENT must be IDENTIFIER." << std::endl;
        return;
    }

    ASTNode* rhs = node->children[1];
    generateExpression(rhs);

    std::cout << "STORE t" << tempVarCount++ << " " << lhs->value << std::endl;
}

void CodeGen::generateExpression(ASTNode* node) {
    if (node->type == "NUMBER") {
        std::cout << "LOAD " << node->value << std::endl;
    } else if (node->type == "IDENTIFIER") {
        std::cout << "LOAD " << node->value << std::endl;
    } else if (node->type == "OPERATOR" && node->children.size() == 2) {
        generateExpression(node->children[0]);
        generateExpression(node->children[1]);

        if (node->value == "+") std::cout << "ADD" << std::endl;
        else if (node->value == "-") std::cout << "SUB" << std::endl;
        else if (node->value == "*") std::cout << "MUL" << std::endl;
        else if (node->value == "/") std::cout << "DIV" << std::endl;
        else std::cerr << "Error: Unsupported operator " << node->value << std::endl;
    } else {
        std::cerr << "Error: Unsupported node type in expression: " << node->type << std::endl;
    }
}

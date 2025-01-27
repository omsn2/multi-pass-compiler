#include "type_checker.h"
#include <iostream>

bool TypeChecker::check(ASTNode* root) {
    if (!root) return true;

    for (auto child : root->children) {
        if (!check(child)) return false;
    }

    if (root->type == "OPERATOR") {
        if (root->children.size() != 2) {
            std::cerr << "Error: Operator " << root->value << " requires two operands." << std::endl;
            return false;
        }
    } else if (root->type == "ASSIGNMENT") {
        if (root->children.size() != 2 || root->children[0]->type != "IDENTIFIER") {
            std::cerr << "Error: Invalid assignment statement." << std::endl;
            return false;
        }
    }

    return true;
}

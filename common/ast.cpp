#include "ast.h"

void printAST(ASTNode* node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; ++i) std::cout << "  ";
    std::cout << node->type << ": " << node->value << std::endl;
    for (auto child : node->children) {
        printAST(child, depth + 1);
    }
}

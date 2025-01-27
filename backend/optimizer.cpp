#include "optimizer.h"

void Optimizer::optimize(ASTNode* root) {
    if (!root) return;

    for (auto& child : root->children) {
        optimize(child);
    }

    if (root->type == "OPERATOR" && root->children.size() == 2) {
        ASTNode* left = root->children[0];
        ASTNode* right = root->children[1];

        if (left->type == "NUMBER" && right->type == "NUMBER") {
            int leftValue = std::stoi(left->value);
            int rightValue = std::stoi(right->value);
            int result = 0;

            if (root->value == "+") result = leftValue + rightValue;
            else if (root->value == "-") result = leftValue - rightValue;
            else if (root->value == "*") result = leftValue * rightValue;
            else if (root->value == "/") result = leftValue / rightValue;

            root->type = "NUMBER";
            root->value = std::to_string(result);
            root->children.clear();
        }
    }
}

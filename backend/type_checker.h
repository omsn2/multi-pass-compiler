#ifndef TYPE_CHECKER_H
#define TYPE_CHECKER_H

#include "ast.h"

class TypeChecker {
public:
    bool check(ASTNode* root);
};

#endif

#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "ast.h"

class Optimizer {
public:
    void optimize(ASTNode* root);
};

#endif

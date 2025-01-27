#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"

// Code generator class
class CodeGen {
public:
    // Resets the internal state of the code generator
    void reset();

    // Main function to generate code for the entire AST
    void generate(ASTNode* root);

private:
    int tempVarCount = 0; // Counter for temporary variables

    // Function to handle function nodes
    void generateFunction(ASTNode* node);

    // Function to handle block nodes
    void generateBlock(ASTNode* node);

    // Function to handle declaration nodes
    void generateDeclaration(ASTNode* node);

    // Function to handle assignment nodes
    void generateAssignment(ASTNode* node);

    // Recursive function to handle expressions
    void generateExpression(ASTNode* node);
};

#endif

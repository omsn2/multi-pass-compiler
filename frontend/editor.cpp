#include "editor.h"
#include "lexer.h"
#include "parser.h"
#include "type_checker.h"
#include "optimizer.h"
#include "codegen.h"
#include <iostream>

bool Editor::compileSource(const std::string& source) {
    std::cout << "Starting Compilation Process..." << std::endl;

    // Step 1: Lexical Analysis
    std::cout << "\n========================\n";
    std::cout << "Step 1: Lexical Analysis\n";
    std::cout << "========================" << std::endl;
    Lexer lexer;
    std::vector<Token> tokens = lexer.tokenize(source);

    std::cout << "Tokens:" << std::endl;
    for (const auto& token : tokens) {
        std::cout << token.type << ": " << token.value << std::endl;
    }

    // Step 2: Syntax Analysis (Parsing)
    std::cout << "\n========================\n";
    std::cout << "Step 2: Syntax Analysis (Parsing)\n";
    std::cout << "========================" << std::endl;
    Parser parser;
    ASTNode* ast = parser.parse(tokens);
    if (!ast) {
        std::cerr << "Parsing failed. Exiting compilation process." << std::endl;
        return false;
    }

    std::cout << "Abstract Syntax Tree (AST):" << std::endl;
    printAST(ast, 0);

    // Step 3: Semantic Analysis (Type Checking)
    std::cout << "\n========================\n";
    std::cout << "Step 3: Semantic Analysis (Type Checking)\n";
    std::cout << "========================" << std::endl;
    TypeChecker typeChecker;
    if (!typeChecker.check(ast)) {
        std::cerr << "Semantic analysis failed. Exiting compilation process." << std::endl;
        delete ast; // Clean up AST memory
        return false;
    }
    std::cout << "Semantic analysis completed successfully." << std::endl;

    // Step 4: Optimization
    std::cout << "\n========================\n";
    std::cout << "Step 4: Optimization\n";
    std::cout << "========================" << std::endl;
    Optimizer optimizer;
    optimizer.optimize(ast); // Optimizes the AST in place

    std::cout << "Optimized AST:" << std::endl;
    printAST(ast, 0);

    // Step 5: Code Generation
    std::cout << "\n========================\n";
    std::cout << "Step 5: Code Generation\n";
    std::cout << "========================" << std::endl;
    CodeGen codegen;
    codegen.reset();
    std::cout << "Generated Code:" << std::endl;
    codegen.generate(ast);

    // Cleanup
    delete ast;
    std::cout << "\nCompilation Process Completed Successfully!" << std::endl;
    return true;
}

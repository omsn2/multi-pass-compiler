#ifndef EDITOR_H
#define EDITOR_H

#include <string>
#include "lexer.h"
#include "parser.h"
#include "type_checker.h"
#include "optimizer.h"
#include "codegen.h"

class Editor {
public:
    std::string openEditor();
    bool compileSource(const std::string& source_code);
};

#endif

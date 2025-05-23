/*
    The Fluent Programming Language
    -----------------------------------------------------
    This code is released under the GNU GPL v3 license.
    For more information, please visit:
    https://www.gnu.org/licenses/gpl-3.0.html
    -----------------------------------------------------
    Copyright (c) 2025 Rodrigo R. & All Fluent Contributors
    This program comes with ABSOLUTELY NO WARRANTY.
    For details type `fluent l`. This is free software,
    and you are welcome to redistribute it under certain
    conditions; type `fluent l -f` for details.
*/

//
// Created by rodrigo on 5/20/25.
//

#ifndef COMPILER_H
#define COMPILER_H
#include <llvm/IR/DebugInfo.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include "../reader/file_reader.h"
#include "fluent/file_code/converter.h"
#include "fluent/file_code/file_code.h"
#include "fluent/lexer/lexer.h"
#include "fluent/parser/ast/ast.h"
#include "fluent/parser/parser.h"

#include "backend.h"

inline void compile(const char *path, const char *output_path, size_t optimization_level)
{
    // Read the file
    const auto file = read_file(path);

    // Parse the code
    auto tokens = fluent::lexer::tokenize(file);
    const auto ast = fluent::parser::parse_code(&tokens);
    const auto code = fluent::file_code::convert_code(ast);

    // Store the IR in a string
    std::string ir;
    llvm::raw_string_ostream stream(ir);

    // Initialize the environment
    llvm::LLVMContext context;
    const auto module = new llvm::Module("fluent", context);
    llvm::IRBuilder builder(context);

    do_compile(context, module, builder, &code);
    module->print(stream, nullptr);
    puts(ir.c_str());
    delete module;
}

#endif //COMPILER_H

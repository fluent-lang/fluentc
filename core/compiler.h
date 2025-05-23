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
#include <fluent/file_code/converter.h>
#include <fluent/file_code/file_code.h>
#include <fluent/lexer/lexer.h>
#include <fluent/parser/ast/ast.h>
#include <fluent/parser/parser.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include "../util/file_reader.h"

#include "../ir/ir_compiler.h"
#include "../state/state .h"
#include "backend.h"

inline void compile(
    const char *path,
    const char *output_path,
    const size_t optimization_level
)
{
    // Read the file
    const auto file = read_file(path);
    fluent::util::assert_eq(optimization_level > 3, false); // Ensure we have a valid optimization level (0-3)

    // Parse the code
    emit(fluent::compiler::state::Lexing, nullptr);
    auto tokens = fluent::lexer::tokenize(file);
    emit(fluent::compiler::state::Parsing, nullptr);
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

    // Call the LLVM Backend
    compile_ir(output_path, optimization_level, stream, code);
    delete module; // Delete the module
}

#endif //COMPILER_H

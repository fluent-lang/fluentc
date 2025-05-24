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
// Created by rodrigo on 5/21/25.
//

#ifndef FLUENTC_EXPR_H
#define FLUENTC_EXPR_H

#include <fluent/file_code/file_code.h>
#include <llvm/IR/IRBuilder.h>

#include "../call/call.h"

inline llvm::Value *process_expr(
    llvm::LLVMContext &context,
    const llvm::Module *module,
    llvm::IRBuilder<> &builder,
    const fluent::file_code::FileCode *code,
    const std::shared_ptr<fluent::parser::AST> &expr,
    const ankerl::unordered_dense::map<std::string_view, fluent::compiler::variable::Variable> &variables,
    const ankerl::unordered_dense::map<std::string_view, llvm::GlobalVariable *> &refs
)
{
    // Get the children
    const auto &children = fluent::util::try_unwrap(expr->children);

    // Get the first children
    switch (const auto &first_child = children[0]; first_child->rule)
    {
        case fluent::parser::Call:
        {
            return process_call(
                module,
                builder,
                first_child,
                variables,
                refs
            );
        }

        default:
            break;
    }

    return nullptr;
}

#endif //FLUENTC_EXPR_H

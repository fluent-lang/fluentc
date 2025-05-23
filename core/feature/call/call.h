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
// Created by rodrigo on 5/23/25.
//

#ifndef FLUENTC_CALL_H
#define FLUENTC_CALL_H
#include <llvm/IR/IRBuilder.h>

#include "../../../table/variable.h"
#include "fluent/file_code/file_code.h"

inline llvm::Value *process_call(
    const llvm::Module *module,
    llvm::IRBuilder<> &builder,
    const std::shared_ptr<fluent::parser::AST> &call,
    const ankerl::unordered_dense::map<std::string_view, Variable> &variables,
    const fluent::file_code::FileCode *code,
    const ankerl::unordered_dense::map<std::string_view, llvm::GlobalVariable *> &refs
)
{
    // Get the children
    const auto &children = fluent::util::try_unwrap(call->children);

    // Get the function's name
    const auto &name = children[0];

    // Collect the arguments
    std::vector<llvm::Value *> args;

    for (size_t i = 1; i < children.size(); ++i)
    {
        // Get the identifier
        const auto &id = children[i];

        // Get the variable
        const auto id_val = fluent::util::try_unwrap(id->value);
        args.push_back(find_value(variables, refs, id_val));
    }

    // Create a function call
    llvm::Function *function = module->getFunction(fluent::util::try_unwrap(name->value).data());
    if (!function)
    {
        throw std::runtime_error("Error: Function not found");
    }

    return builder.CreateCall(function, args);
}

#endif //FLUENTC_CALL_H

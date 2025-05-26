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

#ifndef FLUENTC_VARIABLE_H
#define FLUENTC_VARIABLE_H
#include <llvm/IR/Instructions.h>

namespace fluent::compiler::variable
{
    typedef struct
    {
        llvm::Type *type = nullptr;
        llvm::AllocaInst *alloca = nullptr;
        llvm::Value *value = nullptr;
        file_code::Type original_type;
    } Variable;

    inline Variable get_variable(
        const ankerl::unordered_dense::map<std::string_view, Variable> &variables,
        const std::string_view &name
    )
    {
        // Check if the variable exists
        if (variables.contains(name))
        {
            return variables.at(name);
        }

        // If not found, throw an error
        throw std::runtime_error("Error: Variable not found (" + std::string(name.data()) + ")");
    }

    inline llvm::Value *find_value(
        const ankerl::unordered_dense::map<std::string_view, Variable> &variables,
        stats::CompileTimeStats &ct_stats,
        const std::string_view &name
    )
    {
        // Check if we have a ref
        if (ct_stats.has_ref(name))
        {
            return ct_stats.get_ref(name);
        }

        // Get the variable
        const Variable var = get_variable(variables, name);
        if (var.alloca != nullptr)
        {
            return var.alloca;
        }

        return var.value;
    }
}

#endif //FLUENTC_VARIABLE_H

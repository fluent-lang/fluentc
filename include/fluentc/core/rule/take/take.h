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
// Created by rodrigo on 5/25/25.
//

#ifndef FLUENTC_RULE_TAKE_H
#define FLUENTC_RULE_TAKE_H
#include <ankerl/unordered_dense.h>
#include <llvm/IR/IRBuilder.h>

#include "../../../stats/stats.h"
#include "../../../variable/variable.h"
#include "fluent/parser/ast/ast.h"
#include "fluent/util/assert.h"
#include "fluent/util/unwrap.h"

namespace fluent::compiler::rule
{
    inline llvm::Value *process_take(
        llvm::IRBuilder<> &builder,
        const std::shared_ptr<parser::AST> &take,
        const ankerl::unordered_dense::map<std::string_view, variable::Variable> &variables,
        stats::CompileTimeStats &ct_stats
    )
    {
        // Get the children
        const auto &children = util::try_unwrap(take->children);

        // Get the identifier
        const auto &id = children[0];
        util::assert_eq(id->rule, parser::Identifier);
        const auto id_val = util::try_unwrap(id->value);

        // Make sure the variable exists
        if (!variables.contains(id_val))
        {
            throw std::runtime_error("Error: Variable not found (" + std::string(id_val.data()) + ")");
        }

        // Get the value
        const auto var = variables.at(id_val);
        const auto value = var.value ? var.value : var.alloca;

        // Clone the original type
        const auto [pointers, arrays, base_type, primitive] = var.original_type;
        const auto cloned_type = file_code::Type{
            .pointers = std::max(pointers, static_cast<size_t>(1)) - 1, // Decrease pointers by 1 for take
            .arrays = arrays,
            .base_type = base_type,
            .primitive = primitive
        };

        // Convert the type to LLVM
        const auto type = types::convert_type(builder.getContext(), cloned_type, ct_stats);

        // Create a load instruction
        return builder.CreateLoad(type, value, id_val.data());
    }
}

#endif //FLUENTC_RULE_TAKE_H

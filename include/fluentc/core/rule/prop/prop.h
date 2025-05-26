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

#ifndef FLUENTC_RULE_PROP_H
#define FLUENTC_RULE_PROP_H
#include <ankerl/unordered_dense.h>
#include <fluent/atoi/library.h>
#include <llvm/IR/IRBuilder.h>

#include "../../../stats/stats.h"
#include "../../../variable/variable.h"
#include "fluent/parser/ast/ast.h"
#include "fluent/util/unwrap.h"

namespace fluent::compiler::rule
{
    inline llvm::Value *process_prop(
        llvm::IRBuilder<> &builder,
        const std::shared_ptr<parser::AST> &child,
        const ankerl::unordered_dense::map<std::string_view, variable::Variable> &variables,
        stats::CompileTimeStats &ct_stats,
        const char *expr_name
    )
    {
        // Create a new compile-time address if not provided
        if (expr_name == nullptr)
        {
            expr_name = ct_stats.request_addr();
        }

        // Get the children
        const auto &children = util::try_unwrap(child->children);

        // Get the identifier
        const auto &id = children[0]->value->data();

        // Get the counter
        const auto &counter = children[1];

        // Use fluent_libc to convert the counter to an integer
        const auto i = atoi_convert(counter->value->data());

        // Make sure the variable exists
        if (!variables.contains(id))
        {
            throw std::runtime_error("Error: Variable not found (" + std::string(id) + ")");
        }

        // Get the variable
        const auto &[type, alloca, value, _] = variables.at(id);
        const auto var_value = alloca ? alloca : value;

        // Get the filed
        return builder.CreateStructGEP(type, var_value, i, expr_name);
    }
}

#endif //FLUENTC_RULE_PROP_H

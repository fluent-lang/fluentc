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

#ifndef FLUENTC_RULE_ADDR_H
#define FLUENTC_RULE_ADDR_H
#include <ankerl/unordered_dense.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>

#include "../../../stats/stats.h"
#include "../../../variable/variable.h"
#include "fluent/parser/ast/ast.h"
#include "fluent/util/unwrap.h"

namespace fluent::compiler::rule
{
    inline llvm::AllocaInst *process_addr(
        llvm::IRBuilder<> &builder,
        const std::shared_ptr<parser::AST> &child,
        ankerl::unordered_dense::map<std::string_view, std::shared_ptr<variable::Variable>> &variables,
        stats::CompileTimeStats &ct_stats,
        const char *expr_name
    )
    {
        // If the expr name if null, set it to a compile-time address
        if (expr_name == nullptr)
        {
            expr_name = ct_stats.request_addr();
        }

        // Get the children
        const auto &children = util::try_unwrap(child->children);

        // Get the variable name
        // Avoid using ->data() directly to avoid creating a new string_view
        // that will call strlen again
        const auto name = util::try_unwrap(children[0]->value);

        // Create an alloca instruction for the variable
        const auto &var = get_variable(variables, name);

        // If the variable is not alloca, make it an alloca
        if (var->alloca == nullptr)
        {
            // Create an alloca instruction for the variable
            variables[name]->alloca = builder.CreateAlloca(
                var->type,
                nullptr,
                name
            );

            // Store the value in the alloca instruction
            builder.CreateStore(
                var->value,
                variables[name]->alloca,
                name.data()
            );
        }

        const auto value = find_value(variables, ct_stats, name);
        const auto alloca_inst = builder.CreateAlloca(
            var->type,
            nullptr,
            expr_name
        );

        // Store the variable in the alloca instruction
        // effectively, this is a pointer to the variable
        builder.CreateStore(
            value,
            alloca_inst
        );

        return alloca_inst;
    }
}

#endif //FLUENTC_RULE_ADDR_H

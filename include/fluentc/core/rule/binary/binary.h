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

#ifndef FLUENTC_RULE_BINARY_H
#define FLUENTC_RULE_BINARY_H
#include <ankerl/unordered_dense.h>
#include <llvm/IR/IRBuilder.h>

#include "../../../stats/stats.h"
#include "../../../variable/variable.h"
#include "fluent/parser/ast/ast.h"
#include "fluent/util/unwrap.h"

namespace fluent::compiler::rule
{
    inline llvm::Value *process_binary_opt(
        llvm::IRBuilder<> &builder,
        const std::shared_ptr<parser::AST> &add,
        const ankerl::unordered_dense::map<std::string_view, std::shared_ptr<variable::Variable>> &variables,
        stats::CompileTimeStats &ct_stats,
        const char *name,
        const parser::Rule &rule
    )
    {
        // Get the children
        const auto &children = util::try_unwrap(add->children);
        const auto left = find_value(variables, ct_stats, children[0]->value->data());
        const auto right = find_value(variables, ct_stats, children[1]->value->data());

        // Create the instruction
        switch (rule)
        {
            case parser::Add:
            {
                return builder.CreateAdd(left, right, name);
            }

            case parser::Sub:
            {
                return builder.CreateSub(left, right, name);
            }

            case parser::Mul:
            {
                return builder.CreateMul(left, right, name);
            }

            case parser::Div:
            {
                return builder.CreateSDiv(left, right, name);
            }

            case parser::And:
            {
                return builder.CreateAnd(left, right, name);
            }

            case parser::Or:
            {
                return builder.CreateOr(left, right, name);
            }

            default:
            {
                throw std::runtime_error("Error: Unknown binary operator");
            }
        }
    }
}

#endif //FLUENTC_RULE_BINARY_H

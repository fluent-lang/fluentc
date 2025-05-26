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

#ifndef FLUENTC_RULE_EQ_H
#define FLUENTC_RULE_EQ_H
#include <ankerl/unordered_dense.h>
#include <llvm/IR/IRBuilder.h>

#include "../../../stats/stats.h"
#include "../../../variable/variable.h"
#include "fluent/file_code/file_code.h"
#include "fluent/file_code/type/type_wrapper.h"
#include "fluent/parser/ast/ast.h"
#include "fluent/util/unwrap.h"

namespace fluent::compiler::rule
{
    inline llvm::Value *process_eq(
        llvm::IRBuilder<> &builder,
        const std::shared_ptr<parser::AST> &eq,
        const ankerl::unordered_dense::map<std::string_view, std::shared_ptr<variable::Variable>> &variables,
        stats::CompileTimeStats &ct_stats,
        const char *expr_name
    )
    {
        // Get the children
        const auto &children = util::try_unwrap(eq->children);

        // Get the left and right values
        const auto left = find_value(variables, ct_stats, children[0]->value->data());
        const auto right = find_value(variables, ct_stats, children[1]->value->data());

        // Get the left variable to check if we are comparing floats or structs
        const auto left_var = variables.at(util::try_unwrap(children[0]->value));
        const file_code::Type original_type = left_var->original_type;

        // Check if we are comparing structs
        if (original_type.base_type.has_value())
        {
            // Structs are non-comparable, put false directly
            const auto false_value = llvm::ConstantInt::get(
                llvm::Type::getInt1Ty(builder.getContext()),
                0
            );

            const auto true_value = llvm::ConstantInt::get(
                llvm::Type::getInt1Ty(builder.getContext()),
                1
            );

            return builder.CreateICmpEQ(false_value, true_value, expr_name);
        }

        // Check for float comparison
        if (original_type.primitive.value() == file_code::Dec)
        {
            // Use CreateFCmpOEQ instead
            return builder.CreateFCmpOEQ(
                left,
                right,
                expr_name
            );
        }

        // Create the equality instruction
        return builder.CreateICmpEQ(left, right, expr_name);
    }
}

#endif //FLUENTC_RULE_EQ_H

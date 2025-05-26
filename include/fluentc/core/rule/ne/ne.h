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
// Created by rodrigo on 5/26/25.
//

#ifndef FLUENTC_RULE_NE_H
#define FLUENTC_RULE_NE_H
#include <ankerl/unordered_dense.h>
#include <llvm/IR/IRBuilder.h>

#include "../../../stats/stats.h"
#include "../../../variable/variable.h"
#include "fluent/parser/ast/ast.h"
#include "fluent/util/unwrap.h"

namespace fluent::compiler::rule
{
    inline llvm::Value *process_ne(
        llvm::LLVMContext &context,
        llvm::IRBuilder<> &builder,
        const std::shared_ptr<parser::AST> &ne,
        const ankerl::unordered_dense::map<std::string_view, std::shared_ptr<variable::Variable>> &variables,
        stats::CompileTimeStats &ct_stats,
        const char *expr_name
    )
    {
        // Get the children
        const auto &children = util::try_unwrap(ne->children);

        // Process the left and right expressions
        const auto left_val = find_value(context, variables, ct_stats, children[0]);
        const auto right_val = find_value(context, variables, ct_stats, children[1]);

        // Check if we have a struct comparison
        if (left_val->getType()->isStructTy())
        {
            // Create a false condition, structs are not comparable
            const auto false_value = llvm::ConstantInt::get(
                llvm::Type::getInt1Ty(builder.getContext()),
                0
            );

            const auto true_value = llvm::ConstantInt::get(
                llvm::Type::getInt1Ty(builder.getContext()),
                1
            );

            return builder.CreateICmpNE(
                false_value,
                true_value,
                expr_name
            );
        }

        // Check if we are comparing floats
        if (left_val->getType()->isFloatingPointTy())
        {
            // Create a floating point not equal instruction
            return builder.CreateFCmpUNE(
                left_val,
                right_val,
                expr_name
            );
        }

        // Create the not equal instruction
        return builder.CreateICmpNE(
            left_val,
            right_val,
            expr_name
        );
    }
}

#endif //FLUENTC_RULE_NE_H

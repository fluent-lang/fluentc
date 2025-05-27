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
        llvm::LLVMContext &context,
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
        const auto left = find_value(context, variables, ct_stats, children[0]);
        auto *right = find_value(context, variables, ct_stats, children[1]);

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

            case parser::Gt:
            {
                // Check if we are comparing floats
                if (left->getType()->isFloatingPointTy() || right->getType()->isFloatingPointTy())
                {
                    return builder.CreateFCmpOGT(left, right, name);
                }

                return builder.CreateICmpSGT(left, right, name);
            }

            case parser::Ge:
            {
                // Check if we are comparing floats
                if (left->getType()->isFloatingPointTy() || right->getType()->isFloatingPointTy())
                {
                    return builder.CreateFCmpOGE(left, right, name);
                }

                return builder.CreateICmpSGE(left, right, name);
            }

            case parser::Lt:
            {
                // Check if we are comparing floats
                if (left->getType()->isFloatingPointTy() || right->getType()->isFloatingPointTy())
                {
                    return builder.CreateFCmpOLT(left, right, name);
                }

                return builder.CreateICmpSLT(left, right, name);
            }

            case parser::Le:
            {
                // Check if we are comparing floats
                if (left->getType()->isFloatingPointTy() || right->getType()->isFloatingPointTy())
                {
                    return builder.CreateFCmpOLE(left, right, name);
                }

                return builder.CreateICmpSLE(left, right, name);
            }

            default:
            {
                throw std::runtime_error("Error: Unknown binary operator");
            }
        }
    }
}

#endif //FLUENTC_RULE_BINARY_H

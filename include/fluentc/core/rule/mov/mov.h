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
// Created by rodrigo on 5/24/25.
//

#ifndef FLUENTC_RULE_MOV_H
#define FLUENTC_RULE_MOV_H
#include <ankerl/unordered_dense.h>
#include <llvm/IR/IRBuilder.h>

#include "../../../variable/variable.h"
#include "../binary/binary.h"
#include "fluent/parser/ast/ast.h"

namespace fluent::compiler::rule
{
    inline void process_mov(
        const llvm::Module *module,
        llvm::IRBuilder<> &builder,
        llvm::LLVMContext &context,
        const std::shared_ptr<parser::AST> &child,
        ankerl::unordered_dense::map<std::string_view, variable::Variable> &variables,
        stats::CompileTimeStats &ct_stats
    )
    {
        // Get the children
        const auto &children = util::try_unwrap(child->children);

        // Get the variable name, type and expr
        const auto name = children[0];
        const auto type = types::convert_type(context, file_code::process_type(children[1]), ct_stats);
        const auto expr = children[2];
        llvm::Value *value = nullptr;
        llvm::AllocaInst *alloca = nullptr;

        // Convert the expression to an LLVM object
        switch (expr->rule)
        {
            case parser::DecLiteral:
            case parser::NumLiteral:
            {
                // Get the value
                value = llvm::ConstantInt::get(
                    type,
                    std::stod(expr->value->data())
                );
                break;
            }

            case parser::Call:
            {
                value = process_call(
                    module,
                    context,
                    builder,
                    child,
                    variables,
                    ct_stats,
                    false,
                    nullptr
                );

                break;
            }

            case parser::Construct:
            {
                // Initialize the alloca value
                alloca = builder.CreateAlloca(type, nullptr, name->value->data());

                value = process_call(
                    module,
                    context,
                    builder,
                    child,
                    variables,
                    ct_stats,
                    true,
                    alloca
                );

                break;
            }

            case parser::Sub:
            case parser::Mul:
            case parser::Div:
            case parser::Add:
            {
                value = process_binary_opt(
                    builder,
                    child,
                    variables,
                    ct_stats,
                    name->value->data(),
                    child->rule
                );
                break;
            }

            default:
            {}
        }

        // Insert to the variables
        variables[name->value->data()] = { .type = type, .alloca = alloca, .value = value };
    }
}

#endif //FLUENTC_RULE_MOV_H

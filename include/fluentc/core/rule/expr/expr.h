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

#ifndef FLUENTC_RULE_EXPR_H
#define FLUENTC_RULE_EXPR_H
#include <ankerl/unordered_dense.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>

#include "../../../stats/stats.h"
#include "../../../variable/variable.h"
#include "../addr/addr.h"
#include "../binary/binary.h"
#include "../call/call.h"
#include "../eq/eq.h"
#include "../ne/ne.h"
#include "../prop/prop.h"
#include "../take/take.h"
#include "fluent/parser/ast/ast.h"

namespace fluent::compiler::rule
{
    inline std::pair<llvm::Value *, llvm::AllocaInst *> process_expr(
        const llvm::Module *module,
        llvm::IRBuilder<> &builder,
        llvm::LLVMContext &context,
        const std::shared_ptr<parser::AST> &expr,
        ankerl::unordered_dense::map<std::string_view, std::shared_ptr<variable::Variable>> &variables,
        stats::CompileTimeStats &ct_stats,
        llvm::Type *type,
        const char *expr_name,
        llvm::AllocaInst *alloca_inst = nullptr
    )
    {
        switch (expr->rule)
        {
            case parser::NumLiteral:
            {
                // Get the value
                return
                {
                    llvm::ConstantInt::get(
                        type,
                        atoi_convert(expr->value->data())
                    ),
                    nullptr
                };
            }

            case parser::DecLiteral:
            {
                // Get the value
                return
                {
                    llvm::ConstantInt::get(
                        type,
                        std::stod(expr->value->data())
                    ),
                    nullptr
                };
            }

            case parser::Call:
            {
                return
                {
                    process_call(
                        module,
                        context,
                        builder,
                        expr,
                        variables,
                        ct_stats,
                        false,
                        nullptr
                    ),
                    nullptr
                };
            }

            case parser::Construct:
            {
                // Let process_call create a new alloca instruction
                const auto result = static_cast<llvm::AllocaInst *>(
                    process_call(
                        module,
                        context,
                        builder,
                        expr, variables,
                        ct_stats,
                        true,
                        alloca_inst
                    )
                );

                return
                {
                    result,
                    result
                };
            }

            case parser::Gt:
            case parser::Lt:
            case parser::Ge:
            case parser::Le:
            case parser::Sub:
            case parser::Mul:
            case parser::Div:
            case parser::Add:
            case parser::Or:
            case parser::And:
            {
                return
                {
                    process_binary_opt(
                        context,
                        builder,
                        expr,
                        variables,
                        ct_stats,
                        expr_name,
                        expr->rule
                    ),
                    nullptr
                };
            }

            case parser::Take:
            {
                return
                {
                    process_take(
                        builder,
                        expr,
                        variables,
                        ct_stats
                    ),
                    nullptr
                };
            }

            case parser::Addr:
            {
                return
                {
                    nullptr,
                    process_addr(
                        builder,
                        expr,
                        variables,
                        ct_stats,
                        expr_name
                    )
                };
            }

            case parser::Prop:
            {
                return
                {
                    process_prop(
                        builder,
                        expr,
                        variables,
                        ct_stats,
                        expr_name
                    ),
                    nullptr,
                };
            }

            case parser::Eq:
            {
                return
                {
                    process_eq(
                        context,
                        builder,
                        expr,
                        variables,
                        ct_stats,
                        expr_name
                    ),
                    nullptr
                };
            }

            case parser::Ne:
            {
                return
                {
                    process_ne(
                        context,
                        builder,
                        expr,
                        variables,
                        ct_stats,
                        expr_name
                    ),
                    nullptr
                };
            }

            default:
            {
                return
                { nullptr, nullptr };
            }
        }
    }
}

#endif //FLUENTC_RULE_EXPR_H

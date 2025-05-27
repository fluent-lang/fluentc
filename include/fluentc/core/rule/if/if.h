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

#ifndef FLUENTC_RULE_IF_H
#define FLUENTC_RULE_IF_H
#include <ankerl/unordered_dense.h>
#include <fluent/parser/ast/ast.h>
#include <fluent/util/unwrap.h>
#include <llvm/IR/IRBuilder.h>

#include "../../../stats/stats.h"
#include "../../../variable/variable.h"

namespace fluent::compiler::rule
{
    inline void process_if(
        llvm::LLVMContext &context,
        llvm::IRBuilder<> &builder,
        const std::shared_ptr<parser::AST> &ast,
        BlockList &blocks,
        const ankerl::unordered_dense::map<std::string_view, std::shared_ptr<variable::Variable>> &variables,
        stats::CompileTimeStats &ct_stats
    )
    {
        // Get the children
        const auto &children = util::try_unwrap(ast->children);

        // Get the condition address
        const auto &cond = children[0];

        // Get the condition from the variables
        llvm::Value * cond_val;

        // Check if we have an integer literal in the condition
        if (cond->rule == parser::NumLiteral)
        {
            // Create an i1 true value
            cond_val = llvm::ConstantInt::get(
                llvm::Type::getInt1Ty(context),
                std::stoi(cond->value->data())
            );
        } else
        {
            cond_val = find_value(variables, ct_stats, cond->value->data());
        }

        // Get the then/else block names
        const auto &then_block_name = children[1]->value->data();
        const auto &else_block_name = children[2]->value->data();

        // Get the blocks
        const auto then_block = blocks.get_block(then_block_name, context);
        const auto else_block = blocks.get_block(else_block_name, context);

        // Create the condition
        builder.CreateCondBr(cond_val, then_block, else_block);
    }
}

#endif //FLUENTC_RULE_IF_H

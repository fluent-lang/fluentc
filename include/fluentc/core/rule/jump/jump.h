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

#ifndef FLUENTC_RULE_JUMP_H
#define FLUENTC_RULE_JUMP_H
#include <ankerl/unordered_dense.h>
#include <llvm/IR/IRBuilder.h>
#include <fluent/parser/ast/ast.h>
#include <fluent/util/unwrap.h>

namespace fluent::compiler::rule
{
    inline void process_jump(
        llvm::LLVMContext &context,
        llvm::IRBuilder<> &builder,
        const std::shared_ptr<parser::AST> &ast,
        BlockList &blocks
    )
    {
        // Get the children
        const auto &children = util::try_unwrap(ast->children);

        // Create the branch instruction
        builder.CreateBr(blocks.get_block(
            util::try_unwrap(children[0]->value),
            context
        ));
    }
}

#endif //FLUENTC_RULE_JUMP_H

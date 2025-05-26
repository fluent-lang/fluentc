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
#include "../expr/expr.h"
#include "../take/take.h"
#include "fluent/parser/ast/ast.h"

namespace fluent::compiler::rule
{
    inline void process_mov(
        const llvm::Module *module,
        llvm::IRBuilder<> &builder,
        llvm::LLVMContext &context,
        const std::shared_ptr<parser::AST> &child,
        ankerl::unordered_dense::map<std::string_view, std::shared_ptr<variable::Variable>> &variables,
        stats::CompileTimeStats &ct_stats
    )
    {
        // Get the children
        const auto &children = util::try_unwrap(child->children);

        // Get the variable name, type and expr
        // Avoid using ->data() directly to avoid creating a new string_view
        // that will call strlen again
        const auto name = util::try_unwrap(children[0]->value);
        const auto original_type = file_code::process_type(children[1]);
        const auto type = types::convert_type(context, original_type , ct_stats);
        const auto expr = children[2];
        const auto [ value, alloc_inst ] = process_expr(
            module,
            builder,
            context,
            expr,
            variables,
            ct_stats,
            type,
            name.data()
        );

        // Skip if the expression wasn't parsed
        if (value == nullptr && alloc_inst == nullptr)
        {
            return;
        }

        // Insert to the variables
        const auto new_var = std::make_shared<variable::Variable>();
        new_var->type = type;
        new_var->alloca = alloc_inst;
        new_var->value = value;
        new_var->original_type = original_type;

        variables[name] = new_var;
    }
}

#endif //FLUENTC_RULE_MOV_H

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

#ifndef FLUENTC_RULE_TAKE_H
#define FLUENTC_RULE_TAKE_H
#include <ankerl/unordered_dense.h>
#include <llvm/IR/IRBuilder.h>

#include "../../../stats/stats.h"
#include "../../../variable/variable.h"
#include "fluent/parser/ast/ast.h"
#include "fluent/util/assert.h"
#include "fluent/util/unwrap.h"

namespace fluent::compiler::rule
{
    inline llvm::Value *process_take(
        llvm::IRBuilder<> &builder,
        const std::shared_ptr<parser::AST> &take,
        const ankerl::unordered_dense::map<std::string_view, std::shared_ptr<variable::Variable>> &variables,
        stats::CompileTimeStats &ct_stats
    )
    {
        // Get the children
        const auto &children = util::try_unwrap(take->children);

        // Get the identifier
        const auto &id = children[0];
        util::assert_eq(id->rule, parser::Identifier);
        const auto id_val = util::try_unwrap(id->value);

        // Get the value
        const auto var = get_variable(variables, id_val);

        // Create a load instruction
        return builder.CreateLoad(var->alloca->getAllocatedType(), var->alloca, id_val.data());
    }
}

#endif //FLUENTC_RULE_TAKE_H

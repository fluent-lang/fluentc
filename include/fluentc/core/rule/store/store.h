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

#ifndef FLUENTC_RULE_STORE_H
#define FLUENTC_RULE_STORE_H

#include "../../../variable/variable.h"
#include "../block/block.h"

namespace fluent::compiler::rule
{
    inline void process_store(
        const llvm::Module *module,
        llvm::IRBuilder<> &builder,
        llvm::LLVMContext &context,
        const std::shared_ptr<parser::AST> &store,
        ankerl::unordered_dense::map<std::string_view, variable::Variable> &variables,
        stats::CompileTimeStats &ct_stats
    )
    {
        // Get the children
        const auto &children = util::try_unwrap(store->children);

        // Get the variable name
        // Avoid using ->data() directly to avoid creating a new string_view
        // that will call strlen again
        const auto &name = util::try_unwrap(children[0]->value);

        // Get the expression
        const auto &expr = children[1];

        // Get the variable
        auto var = get_variable(variables, name);

        // Make sure we have an alloca
        util::assert_eq(var.alloca != nullptr, true);

        // Get the value
        const auto &[value, _] = process_expr(
            module,
            builder,
            context,
            expr,
            variables,
            ct_stats,
            var.type,
            name.data(),
            var.alloca
        );

        // Update the value of the variable
        var.value = value;
    }
}

#endif //FLUENTC_RULE_STORE_H

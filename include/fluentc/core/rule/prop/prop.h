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

#ifndef FLUENTC_RULE_PROP_H
#define FLUENTC_RULE_PROP_H
#include <ankerl/unordered_dense.h>
#include <fluent/atoi/atoi.h>
#include <llvm/IR/IRBuilder.h>

#include "../../../stats/stats.h"
#include "../../../variable/variable.h"
#include "fluent/parser/ast/ast.h"
#include "fluent/util/unwrap.h"

namespace fluent::compiler::rule
{
    inline llvm::Value *process_prop(
        llvm::LLVMContext &context,
        llvm::IRBuilder<> &builder,
        const std::shared_ptr<parser::AST> &child,
        const ankerl::unordered_dense::map<std::string_view, std::shared_ptr<variable::Variable>> &variables,
        stats::CompileTimeStats &ct_stats,
        const char *expr_name
    )
    {
        // Create a new compile-time address if not provided
        if (expr_name == nullptr)
        {
            expr_name = ct_stats.request_addr();
        }

        // Get the children
        const auto &children = util::try_unwrap(child->children);

        // Get the identifier
        const auto &id = util::try_unwrap(children[0]->value);

        // Get the counter
        const auto &counter = children[1];

        // Use fluent_libc to convert the counter to an integer
        const auto i = atoi_convert(counter->value->data());

        // Get the variable
        const auto &[type, alloca, value, original_type] = *get_variable(variables, id);

        // Get the struct type
        llvm::StructType *struct_type = ct_stats.get_mod(util::try_unwrap(original_type.base_type));

        auto var_value = alloca ? alloca : value;
        auto actual_type = type;
        auto fluent_type = original_type;

        // Dereference pointers if necessary
        while (fluent_type.pointers > 1)
        {
            // Decrement the pointer count
            fluent_type.pointers--;

            // Process the type again
            actual_type = types::convert_type(context, fluent_type, ct_stats);

            // Create a load instruction
            var_value = builder.CreateLoad(actual_type, var_value, ct_stats.request_addr());
        }

        // Check if the alloca is nullptr (Params)
        if (alloca == nullptr)
        {
            // Cast the raw ptr to the actual type
            var_value = builder.CreateBitCast(
                var_value,
                llvm::PointerType::get(struct_type, 0)
            );
        }

        // Get the filed
        return builder.CreateStructGEP(struct_type, var_value, i, expr_name);
    }
}

#endif //FLUENTC_RULE_PROP_H

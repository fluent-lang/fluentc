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

#ifndef FLUENTC_RULE_ALLOCA_H
#define FLUENTC_RULE_ALLOCA_H

#include <llvm/IR/IRBuilder.h>

#include "../../../stats/stats.h"
#include "../../../variable/variable.h"
#include "../../types/types.h"
#include "fluent/file_code/file_code.h"
#include "fluent/file_code/rule/type/type.h"

namespace fluent::compiler::rule
{
    inline void process_alloca(
        llvm::LLVMContext &context,
        llvm::IRBuilder<> &builder,
        const std::shared_ptr<parser::AST> &ast,
        ankerl::unordered_dense::map<std::string_view, variable::Variable> &variables,
        stats::CompileTimeStats &ct_stats
    )
    {
        // Get the children
        const auto &children = util::try_unwrap(ast->children);

        // Get the name
        // Avoid using ->data() directly to avoid creating a new string_view
        // that will call strlen again
        const auto &name = util::try_unwrap(children[0]->value);

        // Get the type
        llvm::Type *type = types::convert_type(
            context,
            file_code::process_type(children[1]),
            ct_stats
        );

        // Create a new alloca instructions
        llvm::AllocaInst *alloca_inst = builder.CreateAlloca(
            type,
            nullptr,
            name.data()
        );

        // Save the variable
        variable::Variable var;
        var.type = type;
        var.alloca = alloca_inst;
        var.value = alloca_inst;
        variables[name] = var;
    }
}

#endif //FLUENTC_RULE_ALLOCA_H

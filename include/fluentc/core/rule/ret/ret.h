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
// Created by rodrigo on 5/21/25.
//

#ifndef FLUENTC_RULE_RET_H
#define FLUENTC_RULE_RET_H

namespace fluent::compiler::rule
{
    inline void process_ret(
        llvm::IRBuilder<> &builder,
        const std::shared_ptr<parser::AST> &child,
        const ankerl::unordered_dense::map<std::string_view, variable::Variable> &variables,
        stats::CompileTimeStats &ct_stats
    )
    {
        // Get the children
        const auto &children = util::try_unwrap(child->children);

        // Check if the return type is void
        if (children.empty())
        {
            // Add a void return instruction
            builder.CreateRetVoid();
            return;
        }

        // Get the identifier
        const auto &identifier = children[0];
        util::assert_eq(identifier->rule, parser::Identifier);
        const auto id_val = util::try_unwrap(identifier->value);

        // Create a return instruction
        builder.CreateRet(find_value(variables, ct_stats, id_val));
    }
}
#endif //FLUENTC_RULE_RET_H

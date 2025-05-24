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

#ifndef FEATURE_RET_H
#define FEATURE_RET_H

inline void process_ret(
    llvm::IRBuilder<> &builder,
    const std::shared_ptr<fluent::parser::AST> &child,
    const ankerl::unordered_dense::map<std::string_view, fluent::compiler::variable::Variable> &variables,
    const ankerl::unordered_dense::map<std::string_view, llvm::GlobalVariable *> &refs
)
{
    // Get the children
    const auto &children = fluent::util::try_unwrap(child->children);

    // Check if the return type is void
    if (children.empty())
    {
        // Add a void return instruction
        builder.CreateRetVoid();
        return;
    }

    // Get the expression
    const auto &expr = children[0];
    fluent::util::assert_eq(expr->rule, fluent::parser::Expression);

    // Get the identifier
    const auto &identifier = children[1];
    fluent::util::assert_eq(identifier->rule, fluent::parser::Identifier);
    const auto id_val = fluent::util::try_unwrap(identifier->value);

    // Create a return instruction
    builder.CreateRet(find_value(variables, refs, id_val));
}

#endif //FEATURE_RET_H

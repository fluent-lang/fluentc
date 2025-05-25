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
// Created by rodrigo on 5/23/25.
//

#ifndef FLUENTC_CALL_H
#define FLUENTC_CALL_H
#include <llvm/IR/IRBuilder.h>

#include "../../../variable/variable.h"
#include "fluent/file_code/file_code.h"

namespace fluent::compiler::rule
{
    inline llvm::Value *process_call(
        const llvm::Module *module,
        llvm::LLVMContext &context,
        llvm::IRBuilder<> &builder,
        const std::shared_ptr<parser::AST> &call,
        const ankerl::unordered_dense::map<std::string_view, variable::Variable> &variables,
        const ankerl::unordered_dense::map<std::string_view, llvm::GlobalVariable *> &refs,
        stats::CompileTimeStats &ct_stats,
        const bool is_construct,
        llvm::AllocaInst *struct_ptr
    )
    {
        // Get the children
        const auto &children = util::try_unwrap(call->children);

        // Get the function's name
        const auto &name = children[0];

        // Collect the arguments
        std::vector<llvm::Value *> args;

        for (size_t i = 1; i < children.size(); ++i)
        {
            // Get the identifier
            const auto &id = children[i];

            // Get the variable
            const auto id_val = util::try_unwrap(id->value);
            args.push_back(find_value(variables, refs, id_val));
        }

        if (is_construct)
        {
            // Get the struct type
            llvm::Type *struct_ty = llvm::StructType::getTypeByName(context, name->value->data());

            // Create a new alloca instruction for the struct
            if (struct_ptr == nullptr)
            {
                struct_ptr = builder.CreateAlloca(struct_ty, nullptr, ct_stats.request_addr());
            }

            // Add all fields
            for (size_t i = 1; i < children.size(); i++)
            {
                // Get the identifier
                const auto id = children[i];
                util::assert_eq(variables.contains(id->value.value()), true);

                // Get the variable
                const auto var = variables.at(id->value.value());

                // Get the filed
                llvm::Value *field = builder.CreateStructGEP(struct_ty, struct_ptr, i - 1, ct_stats.request_addr());

                // Store the information
                builder.CreateStore(var.value, field);
            }

            return struct_ptr;
        }

        // Create a function call
        llvm::Function *function = module->getFunction(util::try_unwrap(name->value).data());
        if (!function)
        {
            throw std::runtime_error("Error: Function not found");
        }

        return builder.CreateCall(function, args);
    }
}

#endif //FLUENTC_CALL_H

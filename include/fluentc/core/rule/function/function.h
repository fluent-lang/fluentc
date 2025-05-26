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
// Created by rodrigo on 5/20/25.
//

#ifndef FLUENTC_RULE_FUNCTION_H
#define FLUENTC_RULE_FUNCTION_H
#include <llvm/IR/IRBuilder.h>

#include "../../../variable/variable.h"
#include "../../types/types.h"
#include "../block/block.h"
#include "../mov/mov.h"
#include "fluent/file_code/file_code.h"

namespace fluent::compiler::rule
{
    inline void process_functions(
        llvm::LLVMContext &context,
        llvm::Module *module,
        llvm::IRBuilder<> &builder,
        const file_code::FileCode *code,
        stats::CompileTimeStats &ct_stats
    ) {
        // Used to avoid computing strcmp for every function
        bool has_found_main = false;

        // Since order of dependencies is not guaranteed, we have
        // to define all the functions' signatures beforehand
        ankerl::unordered_dense::map<std::string_view, std::pair<bool, llvm::Function *>> function_signatures;
        for (const auto &[name, fun] : code->functions)
        {
            // Convert the return type to a LLVM type
            llvm::Type *return_type;
            const bool is_main = !has_found_main && strcmp(name.data(), "main") == 0;
            if (is_main)
            {
                return_type = llvm::Type::getInt32Ty(context);
                has_found_main = true;
            } else
            {
                return_type = types::convert_type(context, fun->return_type, ct_stats);
            }

            // Collect the arguments
            std::vector<llvm::Type *> args;
            for (const auto &[_, arg] : fun->params)
            {
                // Convert the arg type and push it
                args.push_back(types::convert_type(context, arg, ct_stats));
            }

            // Create the function
            llvm::FunctionType *funcType = llvm::FunctionType::get(return_type, args, false);
            llvm::Function *func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, name.data(), module);

            // Name the arguments
            auto fn_args = func->arg_begin();
            for (const auto &[name, _] : fun->params)
            {
                // Convert the arg type and push it
                fn_args->setName(name.data());
                fn_args++;
            }

            function_signatures[name] = { is_main, func };
        }

        // Iterate over all functions
        for (const auto &[name, fun] : code->functions)
        {
            emit(state::Building, name.data());

            // Create a variable and block map
            ankerl::unordered_dense::map<std::string_view, variable::Variable> variables;
            ankerl::unordered_dense::map<std::string_view, llvm::BasicBlock *> blocks;
            const auto [is_main, func] = function_signatures[name];

            // Push all params to the variable map
            auto fn_args = func->arg_begin();
            size_t i = 0;
            for (const auto &[name, _] : fun->params)
            {
                // Convert the arg type and push it
                llvm::Value *param = func->getArg(0);

                // Insert to the variables
                variables[name] = variable::Variable{
                    .type = param->getType(),
                    .value = param,
                };

                i++;
                fn_args++;
            }

            // Insert all blocks (Insertion happens after the main block is written)
            for (const auto &[name, block] : fun->blocks)
            {
                // Create a new block
                llvm::BasicBlock *basic_block = llvm::BasicBlock::Create(context, name, func);
                blocks[name] = basic_block;
            }

            // Process the function body
            llvm::BasicBlock *block = llvm::BasicBlock::Create(context, "entry", func);
            process_block(
                block,
                context,
                module,
                builder,
                ct_stats,
                fun,
                is_main,
                variables,
                blocks
            );

            // Process additional blocks
            for (const auto &[name, block] : blocks)
            {
                // Entry block never present here, no need for
                // name checking
                process_block(
                    block,
                    context,
                    module,
                    builder,
                    ct_stats,
                    fun,
                    is_main,
                    variables,
                    blocks
                );
            }
        }
    }
}

#endif //FLUENTC_RULE_FUNCTION_H

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

#ifndef FLUENTC_RULE_BLOCK_H
#define FLUENTC_RULE_BLOCK_H

#include "../../../variable/variable.h"
#include "../alloca/alloca.h"
#include "../if/if.h"
#include "../jump/jump.h"
#include "../mov/mov.h"
#include "../ret/ret.h"
#include "../store/store.h"
#include "fluent/file_code/file_code.h"

namespace fluent::compiler::rule
{
    inline void process_block(
        llvm::BasicBlock *block,
        llvm::LLVMContext &context,
        const llvm::Module *module,
        llvm::IRBuilder<> &builder,
        stats::CompileTimeStats &ct_stats,
        const bool is_main,
        ankerl::unordered_dense::map<std::string_view, std::shared_ptr<variable::Variable>> &variables,
        const ankerl::unordered_dense::map<std::string_view, llvm::BasicBlock *> &blocks,
        const std::vector<std::shared_ptr<parser::AST>> &children
    )
    {
        builder.SetInsertPoint(block);

        // Iterate over the function's body
        for (const auto &child : children)
        {
            switch (child->rule)
            {
                case parser::Ret:
                {
                    // Return 0 for the main function
                    if (is_main)
                    {
                        builder.CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0));
                    }
                    else
                    {
                        // Process the return statement
                        process_ret(
                            builder,
                            child,
                            variables,
                            ct_stats
                        );
                    }

                    break;
                }

                case parser::Mov:
                {
                    process_mov(
                        module,
                        builder,
                        context,
                        child,
                        variables,
                        ct_stats
                    );

                    break;
                }

                case parser::Alloca:
                {
                    process_alloca(
                        context,
                        builder,
                        child,
                        variables,
                        ct_stats
                    );

                    break;
                }

                case parser::Jump:
                {
                    process_jump(builder, child, blocks);
                    break;
                }

                case parser::Store:
                {
                    process_store(
                        module,
                        builder,
                        context,
                        child,
                        variables,
                        ct_stats
                    );

                    break;
                }

                case parser::If:
                {
                    process_if(
                        context,
                        builder,
                        child,
                        blocks,
                        variables,
                        ct_stats
                    );
                    break;
                }

                default:
                {
                    process_expr(
                        module,
                        builder,
                        context,
                        child,
                        variables,
                        ct_stats,
                        nullptr,
                        nullptr
                    );
                }
            }
        }
    }
}

#endif //FLUENTC_RULE_BLOCK_H

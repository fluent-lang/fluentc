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
// Created by rodrigo on 5/26/25.
//

#ifndef FLUENTC_BLOCK_H
#define FLUENTC_BLOCK_H
#include <ankerl/unordered_dense.h>
#include <llvm/IR/BasicBlock.h>

namespace fluent::compiler
{
    class BlockList
    {
        ankerl::unordered_dense::map<std::string_view, llvm::BasicBlock *> blocks;
        llvm::Function *fn = nullptr;
    public:
        // Constructor
        explicit BlockList(llvm::Function *function) : fn(function)
        {}

        // Add a block to the list
        void add_block(const std::string &name, llvm::BasicBlock *block)
        {
            blocks[name] = block;
        }

        [[nodiscard]] bool contains(const std::string &name) const
        {
            return blocks.contains(name);
        }

        // Get a block by name
        [[nodiscard]] llvm::BasicBlock *get_block(const std::string_view &name, llvm::LLVMContext &context)
        {
            // Check if the block exists
            if (blocks.contains(name))
            {
                return blocks.at(name);
            }

            // If not, create a new block
            llvm::BasicBlock *new_block = llvm::BasicBlock::Create(
                context,
                name,
                fn
            );

            // Add the block
            blocks[name] = new_block;
            return new_block;
        }
    };
}

#endif //FLUENTC_BLOCK_H

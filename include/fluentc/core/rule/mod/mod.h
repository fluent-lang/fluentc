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
// Created by rodrigo on 5/24/25.
//

#ifndef FEATURE_MOD_H
#define FEATURE_MOD_H

#include "../../../util/triple.h"
#include "../../types/types .h"
#include "fluent/file_code/file_code.h"

namespace fluent::compiler::rule
{
    inline bool process_mod(
        llvm::LLVMContext &context,
        const std::shared_ptr<file_code::Mod> &mod,
        const std::string_view &name
    )
    {
        // Collect the module's types
        std::vector<llvm::Type *> types;
        for (const auto &type : mod->types)
        {
            // Convert the type and push it
            const auto result = convert_type(context, type, false);

            // Check if we have nullptr
            if (result == nullptr)
            {
                return false;
            }

            types.push_back(result);
        }

        // Create the module
        llvm::StructType::create(
            context,
            types,
            name.data()
        );

        return true;
    }

    inline void process_mods(
        llvm::LLVMContext &context,
        const file_code::FileCode *code
    )
    {
        // Since order of dependencies is not guaranteed,
        // we need to use a vector to queue all modules
        std::vector<util::Triple<std::string_view, std::shared_ptr<file_code::Mod>, bool>> queue;

        // Iterate over all modules and queue only what's needed
        for (const auto &[name, mod] : code->mods)
        {
            // Try to process the module
            if (!process_mod(context, mod, name))
            {
                // Enqueue the module
                queue.emplace_back(name, mod, false);
            }
        }

        // Process all modules in the queue
        while (!queue.empty())
        {
            // Get the module
            const auto triple = queue.back();
            queue.pop_back();

            // Process the module
            if (!process_mod(context, triple.second, triple.first))
            {
                // Make sure the mod was not seen before
                if (triple.third)
                {
                    // Infinite loop detected
                    throw std::runtime_error("Error: Infinite loop detected - Invalid IR structure");
                }

                // Enqueue the module again
                queue.emplace_back(triple.first, triple.second, true);
            }
        }
    }
}

#endif //FEATURE_MOD_H

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

#ifndef FLUENTC_STATS_H
#define FLUENTC_STATS_H
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <vector>
#include <fluent/itoa/library.h>

namespace fluent::compiler::stats
{
    class CompileTimeStats
    {
        long requested_vars = 0;
        std::vector<char *> allocated_vars;
        ankerl::unordered_dense::map<std::string_view, llvm::GlobalVariable *> refs;

    public:
        CompileTimeStats() = default;
        char *request_addr()
        {
            // Allocate a new variable
            auto *var = static_cast<char *>(malloc(12 + requested_vars));
            if (var == nullptr)
            {
                throw std::runtime_error("Error: Could not allocate memory");
            }

            // Write the address to the variable
            memcpy(var, "__compile_", 10);

            // Convert the requested_vars to a string
            char *requested_vars_str = itoa(requested_vars);
            memcpy(var + 10, requested_vars_str, requested_vars + 1); // +1 for null terminator
            free(requested_vars_str);

            // Store the variable
            allocated_vars.push_back(var);
            ++requested_vars;

            return var;
        }

        void insert_ref(
            const std::string_view &name,
            llvm::GlobalVariable *var
        )
        {
            // Check if the ref already exists
            if (refs.contains(name))
            {
                throw std::runtime_error("Error: Ref already exists");
            }

            // Insert the ref
            refs[name] = var;
        }

        void get_ref(
            const std::string_view &name,
            llvm::GlobalVariable *&var
        )
        {
            // Check if the ref exists
            if (!refs.contains(name))
            {
                throw std::runtime_error("Error: Ref not found");
            }

            // Get the ref
            var = refs[name];
        }

        ~CompileTimeStats()
        {
            // Free all allocated variables
            for (const auto & allocated_var : allocated_vars)
            {
                free(allocated_var);
            }
        }
    };
}

#endif //FLUENTC_STATS_H

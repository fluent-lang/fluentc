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

#ifndef FEATURE_LINK_H
#define FEATURE_LINK_H

#include <fluent/file_code/file_code.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/IRReader/IRReader.h>

inline void process_links(
    llvm::LLVMContext &context,
    llvm::Module *module,
    const fluent::file_code::FileCode *code
)
{
    // Iterate over all links
    for (const auto &link : code->links)
    {
        emit(fluent::compiler::state::Building, link.data());
        // Parse the IR file
        llvm::SMDiagnostic err;
        const auto link_module = parseIRFile(link.data(), err, context);
        if (!link_module)
        {
            // Print an error message
            err.print("fluent", llvm::errs());
            throw std::runtime_error("Error: Could not parse link");
        }

        // Insert the link module into the current module
        for (auto &function : link_module->functions())
        {
            // Check if the function is already defined
            if (module->getFunction(function.getName()))
            {
                // Print a warning message
                printf("Warning: Function %s already defined\n", function.getName().str().c_str());
            }
            else
            {
                // Get the function type from the original function
                llvm::FunctionType *funcType = function.getFunctionType();

                // Create a function declaration (without body) in the current module
                llvm::Function::Create(
                    funcType,
                    llvm::Function::ExternalLinkage,
                    function.getName(),
                    module
                );
            }
        }
    }
}

#endif //FEATURE_LINK_H

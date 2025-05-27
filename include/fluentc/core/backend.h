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

#ifndef FLUENTC_BACKEND_H
#define FLUENTC_BACKEND_H
#include <fluent/file_code/file_code.h>
#include <llvm/IR/IRBuilder.h>

#include "../stats/stats.h"
#include "rule/function/function.h"
#include "rule/link/link.h"
#include "rule/mod/mod.h"
#include "rule/ref/ref.h"

namespace fluent::compiler
{
    inline void gencode(
        llvm::LLVMContext &context,
        llvm::Module *module,
        llvm::IRBuilder<> &builder,
        const file_code::FileCode *code
    )
    {
        // Make sure we have a main function
        util::assert_eq(code->functions.contains("main"), true);

        // Create a stats object
        stats::CompileTimeStats stats;

        // Process all refs
        rule::process_refs(context, module, code, stats);

        // Add all links
        rule::process_links(context, module, code);

        // Process all mods
        rule::process_mods(context, code, stats);

        // Process all functions
        rule::process_functions(context, module, builder, code, stats);
    }
}

#endif //FLUENTC_BACKEND_H

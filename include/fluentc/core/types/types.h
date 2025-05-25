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

#ifndef CORE_TYPES_H
#define CORE_TYPES_H

#include "fluent/file_code/file_code.h"

namespace fluent::compiler::types
{
    inline llvm::Type *convert_type(
        llvm::LLVMContext &context,
        const file_code::Type &type,
        stats::CompileTimeStats &ct_stats,
        const bool panic = true
    )
    {
        llvm::Type *result = nullptr;

        // Get the type based on the type name
        if (type.base_type.has_value())
        {
            result = ct_stats.get_mod(type.base_type.value().data());
        } else
        {
            switch (type.primitive.value())
            {
                case file_code::Nothing:
                    result = llvm::Type::getVoidTy(context);
                break;
                case file_code::Num:
                    result = llvm::Type::getInt32Ty(context);
                break;
                case file_code::Dec:
                    result = llvm::Type::getDoubleTy(context);
                break;
                case file_code::String:
                    result = llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0);
                break;
            }
        }

        // Make sure we have a valid type
        if (result == nullptr)
        {
            // Return nullptr on fallback
            if (!panic)
            {
                return nullptr;
            }

            throw std::runtime_error("Error: Could not convert type");
        }

        // Process all pointers and arrays
        for (size_t i = 0; i < type.pointers + type.arrays; i++)
        {
            result = llvm::PointerType::get(result, 0);
        }

        return result;
    }
}

#endif //CORE_TYPES_H

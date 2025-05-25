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

#ifndef FLUENTC_RULE_REF_H
#define FLUENTC_RULE_REF_H

#include <fluent/file_code/file_code.h>
#include <fluent/atoi/library.h>

namespace fluent::compiler::rule
{
    inline void process_refs(
        llvm::LLVMContext &context,
        llvm::Module *module,
        const file_code::FileCode *code,
        ankerl::unordered_dense::map<std::string_view, llvm::GlobalVariable *> &refs
    )
    {
        // Iterate over all refs
        for (const auto &[name, ref] : code->refs)
        {
            // Define a global constant depending on its rule
            switch (const auto &value = ref->value; value->rule)
            {
                case parser::StringLiteral:
                {
                    // Create a global string
                    const auto &str = fluent::util::try_unwrap(value->value);
                    const auto global = new llvm::GlobalVariable(
                        *module,
                        llvm::ArrayType::get(llvm::Type::getInt8Ty(context), str.size() + 1), // +1 for null terminator
                        true,
                        llvm::GlobalValue::ExternalLinkage,
                        nullptr,
                        name.data()
                    );

                    // Set the initializer to the string
                    global->setInitializer(llvm::ConstantDataArray::getString(context, str.data()));
                    refs[name] = global;

                    break;
                }

                case parser::NumLiteral:
                {
                    // Create a global int
                    const auto &num = fluent::util::try_unwrap(value->value);
                    const auto global = new llvm::GlobalVariable(
                        *module,
                        llvm::Type::getInt32Ty(context),
                        true,
                        llvm::GlobalValue::ExternalLinkage,
                        llvm::ConstantInt::get(
                            llvm::Type::getInt32Ty(context),
                            atoi_convert(num.data())
                        ),
                        name.data()
                    );
                    refs[name] = global;
                    break;
                }

                case parser::DecLiteral:
                {
                    // Create a global int
                    const auto &num = fluent::util::try_unwrap(value->value);
                    const auto global = new llvm::GlobalVariable(
                        *module,
                        llvm::Type::getFloatTy(context),
                        true,
                        llvm::GlobalValue::ExternalLinkage,
                        llvm::ConstantInt::get(
                            llvm::Type::getFloatTy(context),
                            std::stod(num.data())
                        ),
                        name.data()
                    );

                    refs[name] = global;
                    break;
                }

                default:
                    break;
            }
        }
    }
}

#endif //FLUENTC_RULE_REF_H

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

#ifndef FLUENTC_IR_COMPILER_H
#define FLUENTC_IR_COMPILER_H

#include <cpp-subprocess/subprocess.hpp>
#include <format>
#include <fstream>
#include <llvm/Support/raw_ostream.h>

#include "../state/state .h"
#include "../util/command.h"
#include "ir_linker.h"
#ifndef _WIN32
#   include <unistd.h>
#endif

inline void compile_ir(
    const char *output_path,
    const size_t optimization_level,
    llvm::raw_string_ostream &stream,
    const fluent::file_code::FileCode &code
)
{
    // Create the output IR path
    std::string output_ir_path = std::format(
        "{}.ll",
        output_path
    );

    std::string output_obj_path = std::format(
        "{}.o",
        output_path
    );

    // Save the IR to a file
    std::ofstream output_file(output_ir_path);
    if (!output_file.is_open())
    {
        throw std::runtime_error("Error: Could not open output file");
    }

    output_file << stream.str();
    output_file.close();

    // Call the linker
    const auto linked_path = link_ir(output_path, output_ir_path, code);
    emit(fluent::compiler::state::Compiling, "program");

    // Call the LLVM compiler
    exec_command(
        {
            "llc",
            std::format("-O{}", optimization_level),
            "-relocation-model=pic",
            "-filetype=obj",
            linked_path,
            "-o",
            output_obj_path
        },
        "Error: LLVM Backend failed"
    );

    // Handle POSIX and Windows
#   if defined(__APPLE__) || defined(_WIN32)
    // Make sure we have clang installed
    if (
        const int result = system("clang --version > /dev/null 2>&1");
        result != 0
    )
    {
        throw std::runtime_error("Error: Clang is not installed. Please install it using `brew install llvm`.");
    }

    // Invoke clang directly
    exec_command(
        {
            "clang",
            "-o",
            output_path,
            output_obj_path
        },
        "Error: LLVM Backend failed"
    );)
#  elif defined(_POSIX_VERSION)
    // POSIX compliant systems that aren't macOS
    // Make sure GCC is installed
    if (
        const auto result = system("gcc --version > /dev/null 2>&1");
        result != 0
    )
    {
        // Very rare case, as GCC is installed by default in most systems
        throw std::runtime_error("Error: GCC is not installed. Please install it using your package manager.");
    }

    // Invoke GCC directly
    exec_command(
        {
            "gcc",
            "-o",
            output_path,
            output_obj_path
        },
        "Error: LLVM Backend failed"
    );
#   else
    throw std::runtime_error("Error: Unsupported platform. Please use macOS or any other POSIX-Compliant system (Or Windows)");
#   endif

    fluent::compiler::state::done();
}

#endif //FLUENTC_IR_COMPILER_H

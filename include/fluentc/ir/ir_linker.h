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

#ifndef FLUENTC_IR_LINKER_H
#define FLUENTC_IR_LINKER_H

namespace fluent::compiler
{
    inline std::string link_ir(
        const char *output,
        const std::string &ir_path,
        const file_code::FileCode &code
    )
    {
        emit(state::Linking, "modules");

        // Link all modules using llvm-link
        std::vector<std::string> args;
        args.emplace_back("llvm-link");
        args.emplace_back("-S");
        args.emplace_back(ir_path.c_str());

        // Add all links
        for (const auto &link : code.links)
        {
            args.emplace_back(link.data());
        }

        // Add the output file
        const auto &output_file = std::format(
            "{}_linked.ll",
            output
        );
        args.emplace_back("-o");
        args.push_back(output_file);

        // Call the llvm-link command
        util::exec_command(
            args,
            "Error: LLVM Backend failed"
        );

        return output_file;
    }
}

#endif //FLUENTC_IR_LINKER_H

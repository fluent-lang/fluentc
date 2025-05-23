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

inline std::string link_ir(
    const char *output,
    const std::string &ir_path,
    const fluent::file_code::FileCode &code
)
{
    emit(fluent::compiler::state::Linking, "modules");

    // Link all modules using llvm-link
    std::vector<std::string> args;
    args.push_back("llvm-link");
    args.push_back("-S");
    args.push_back(ir_path.c_str());

    // Add all links
    for (const auto &link : code.links)
    {
        args.push_back(link.data());
    }

    // Add the output file
    const auto &output_file = std::format(
        "{}_linked.ll",
        output
    );
    args.push_back("-o");
    args.push_back(output_file);

    // Call the llvm-link command
    subprocess::Popen p(
        args,
        subprocess::output{subprocess::PIPE},
        subprocess::input{subprocess::PIPE}
    );

    // Handle errors
    if (p.wait() != 0)
    {
        throw std::runtime_error("Error: Could not link modules");
    }

    fluent::compiler::state::done();
    return output_file;
}

#endif //FLUENTC_IR_LINKER_H

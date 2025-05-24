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

#ifndef FLUENTC_COMMAND_H
#define FLUENTC_COMMAND_H
#include <string>
#include <vector>

#include "cpp-subprocess/subprocess.hpp"

namespace fluent::compiler::util
{
    inline void exec_command(
        const std::vector<std::string> &args,
        const char *failure_msg = "Error: Command failed",
        const bool panic = true
    )
    {
        // Invoke the command
        auto p = subprocess::Popen(
            args,
            subprocess::output{subprocess::PIPE}
        );
        const auto [fst, snd] = p.communicate();

        // Check if we have an error code
        if (p.wait() != 0)
        {
            if (!panic)
            {
                return;
            }

            puts(failure_msg);
            puts(fst.buf.data());
            exit(1);
        }
    }
}

#endif //FLUENTC_COMMAND_H

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

// Macros
#define PROGRAM_NAME "fluentc"
#define PROGRAM_DESC "The Fluent Language Compiler"
#define PROGRAM_VERSION "1.0.0"

#include "include/fluentc/core/compiler.h"
#include "fluent/cli/algorithm/help_generator/help_generator.h"
#include "fluent/cli/argv_impl.h"
#include "fluent/cli/flag/flag.h"

using namespace std;

ankerl::unordered_dense::map<std::string, std::shared_ptr<fluent::cli::Flag>> get_flags()
{
    // Define flags
    ankerl::unordered_dense::map<std::string, std::shared_ptr<fluent::cli::Flag>> flags;
    flags["optimization"] = make_shared<fluent::cli::Flag>(fluent::cli::Flag{
        fluent::cli::STRING,
        "optimization",
        "Optimization level (0-3)",
        "O",
        false,
    });

    flags["out"] = make_shared<fluent::cli::Flag>(fluent::cli::Flag{
        fluent::cli::STRING,
        "",
        "Output program path",
        "o",
        true,
    });

    flags["path"] = make_shared<fluent::cli::Flag>(fluent::cli::Flag{
        fluent::cli::STRING,
        "",
        "Path of the program to be compiled",
        "p",
        true,
    });

    flags["help"] = make_shared<fluent::cli::Flag>(fluent::cli::Flag{
        fluent::cli::STATIC,
        "",
        "Displays this menu",
        "h",
        false,
    });

    return flags;
}

int main(const int argc, const char** argv)
{
    // Get the flags
    auto flags = get_flags();
    // Parse argv
    const auto args = parse_argv(argc, argv, flags);

    // Handle errors
    if (!args->success || args->statics.contains("help"))
    {
        generate_help(PROGRAM_NAME, PROGRAM_DESC, flags, 18);

        if (args->statics.contains("help"))
        {
            return 0;
        }

        return 2;
    }

    // Parse the optimization level if we have one
    size_t optimization_level = 0;
    if (args->ints.contains("optimization"))
    {
        optimization_level = args->ints["optimization"];
    }

    // Call the compiler
    fluent::compiler::compile(args->strings["path"], args->strings["out"], optimization_level);
    return 0;
}
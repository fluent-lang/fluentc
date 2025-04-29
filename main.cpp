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

#include <iostream>

#include <map>

#include "algorithm/cli/help_generator.h"
#include "args/argv_impl.h"
#include "args/flag/flag.h"

using namespace std;

std::map<std::string, Flag> get_flags()
{
    // Define flags
    std::map<std::string, Flag> flags;
    flags["optimization"] = Flag{
        "",
        "Optimization level (0-3)",
        "O",
        1,
    };

    flags["out"] = Flag{
        "",
        "Output program path",
        "o",
        0,
        true,
    };

    flags["path"] = Flag{
        "",
        "Path of the program to be compiled",
        "p",
        0,
        true,
    };

    flags["help"] = Flag{
        "",
        "Displays this menu",
        "h",
        2,
    };

    return flags;
}

int main(const int argc, const char** argv)
{
    // Print copyright messages
    cout << PROGRAM_NAME << " - " << PROGRAM_DESC << endl;
    cout << "Copyright (c) 2025 Rodrigo R. & All Fluent Contributors" << endl;
    cout << endl;

    // Get the flags
    const auto flags = get_flags();
    // Parse argv
    const ArgvImpl parsing_result = parse(argc, argv, flags);

    // Handle errors
    if (!parsing_result.is_success() || parsing_result.has("help"))
    {
        print_help(PROGRAM_NAME, flags);
    }

    return 0;
}
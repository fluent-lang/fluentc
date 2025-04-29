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

#include <iostream>

#include "args/ArgvImpl.h"
#include "args/flag/flag.h"
#include <map>

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
    };

    flags["path"] = Flag{
        "",
        "Path of the program to be compiled",
        "p",
        0,
    };

    return flags;
}

int main(const int argc, const char** argv)
{
    // Print copyright messages
    cout << "fluentc - The Fluent Language Compiler" << endl;
    cout << "Copyright (c) 2025 Rodrigo R. & All Fluent Contributors" << endl;
    cout << endl;

    // Parse argv
    ArgvImpl parsing_result = parse(argc, argv, get_flags());

    // Determine errors

    return 0;
}
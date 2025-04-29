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
// Created by rodrigo on 4/28/25.
//

#ifndef FLAG_H
#define FLAG_H

struct Flag
{
    // DO NOT SET MANUALLY
    mutable std::string original_name;
    // Information fields
    const char *description;
    const char *shortcut;
    // 0 = string
    // 1 = int
    // 2 = static
    unsigned int type;
};

#endif //FLAG_H

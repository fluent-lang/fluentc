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
// Created by rodrigo on 4/29/25.
//

#ifndef HELP_GENERATOR_H
#define HELP_GENERATOR_H

#ifndef FLAG_H
#include "../../args/flag/flag.h"
#endif

void print_help(const char *program_name, const std::map<std::string, Flag>& flags);

#endif //HELP_GENERATOR_H

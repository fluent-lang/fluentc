//
// Created by rodrigo on 4/29/25.
//

#include <iostream>
#include <map>
#include <string>
#include "../../args/flag/flag.h"
#include "../../structure/string/string_builder.h"

#include "../space/space_formatter.h"
#include "help_generator.h"

void print_help(const char *program_name, std::map<std::string, Flag> flags)
{
    // Create a new string builder
    auto builder = StringBuilder(250);

    // Write usage
    builder.write("USAGE: ");
    builder.write(program_name);
    builder.write(" <flags...> [arguments...]\n\nAVAILABLE FLAGS:\n");
    for (const auto& [name, flag] : flags)
    {
        // Create a substring builder to build  the flag's name dynamically
        StringBuilder name_builder;
        // Add the flag name
        name_builder.write("--");
        name_builder.write(name);
        name_builder.write(", -");
        name_builder.write(flag.shortcut);

        // Create a description string builder
        StringBuilder description_builder;
        description_builder.write(flag.description);

        // Write according to the flag type
        if (flag.type == 0)
        {
            description_builder.write(" (STRING)");
        } else if (flag.type == 1)
        {
            description_builder.write(" (NUMBER)");
        } else if (flag.type != 2)
        {
            description_builder.write(" (UNKNOWN)");
        }

        // Collect the name
        const auto name_str = name_builder.collect();

        // Build the spaces
        const auto spaced_str = add_spaces(25, name_str, description_builder.collect());

        // Add the final string to the builder
        builder.write(spaced_str);
        builder.write("\n");
    }

    std::cout << builder.collect();
}
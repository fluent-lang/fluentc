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
// Created by rodrigo on 2/25/25.
//

#include <iostream>
#include <map>
#include <string>
#include "../algorithm/atoi/atoi.h"
#include "../algorithm/atoi/atoi_result.h"
#include "../algorithm/str_copy/str_copy.h"
#include "../algorithm/strlen/str_len.h"
#include "argv_impl.h"
#include "flag/flag.h"

/**
 * Retrieves a numeric argument by its name.
 * @param name The name of the argument to retrieve.
 * @return An optional containing the numeric value if found, or 0 if not.
 */
long ArgvImpl::get_number(const char *name) {
    if (!this->numbers.contains(name))
    {
        return 0;
    }

    // Return the number
    return this->numbers[name];
}

/**
    * Retrieves a string argument by its name.
    * @param name The name of the argument to retrieve.
    * @return An optional containing the string value if found, or an empty string if not.
 */
std::string ArgvImpl::get_string(const char *name) {
    if (!this->strings.contains(name))
    {
        return "";
    }

    // Return the number
    return this->strings[name];
}

/**
    * Checks if the parsing was successful.
    * @return True if parsing was successful, false otherwise.
*/
bool ArgvImpl::is_success() const {
    return this->success;
}

/**
    * Checks the presence of a static flag by its name.
    * @param name The name of the flag to check.
    * @return A boolean indicating if the flag was found.
*/
bool ArgvImpl::has(const char *name) const {
    return this->statics.contains(name);
}

/**
 * Parses the command-line arguments and flags into an ArgvImpl object.
 *
 * @param argc The number of elements in argv
 * @param argv A pointer to an array of C-style strings representing the arguments.
 * @param flags A map to Flag objects containing additional parsing options.
 * @return An ArgvImpl object populated with the parsed arguments.
 */
ArgvImpl parse(const int argc, const char **argv, std::map<std::string, Flag> flags)
{
    ArgvImpl result;
    result.success = true;

    // Check if argc is empty
    if (argc == 1)
    {
        result.success = false;
        return result;
    }

    // Add all shortcuts to the flag map
    std::map<const char*, Flag> new_flags;
    for (const auto& [name, flag] : flags)
    {
        if (flag.shortcut != nullptr)
        {
            // Ensure we don't have a duplicate shortcut
            if (flags.contains(flag.shortcut))
            {
                std::cerr << "Runtime Error: CLI flag duplicated (" << flag.shortcut << ")" << std::endl;
                exit(1);
            }

            flag.original_name = name;
            new_flags[flag.shortcut] = flag;
        }
    }

    // Add the additional flags
    for (const auto& [name, flag] : new_flags)
    {
        flags[name] = flag;
    }

    // Parsing flags
    bool parsing_flag = false;
    std::string last_flag_name;
    Flag last_flag{};

    // Iterate over all arguments
    for (int i = 1; i < argc; i++)
    {
        const char* arg = argv[i];

        // Check if we are parsing a flag
        if (parsing_flag)
        {
            // Update parsing_flag
            parsing_flag = false;

            // Push to the appropriate map
            if (last_flag.type == 0)
            {
                result.strings[last_flag_name] = arg;
            } else
            {
                // Convert the argument to a number
                const auto [success, value] = atoi_convert(arg);
                if (!success)
                {
                    // Handle error
                    result.success = false;
                    return result;
                }

                result.numbers[last_flag_name] = value;
            }

            continue;
        }

        // Handle flags
        if (arg[0] == '-')
        {
            parsing_flag = true;

            Flag flag{};
            // Determine if this is a long or short flag
            if (arg[1] != '-')
            {
                // Ensure we have exactly one character
                if (arg[2] != '\0')
                {
                    // Handle null terminator
                    result.success = false;
                    return result;
                }

                char value[2];
                value[0] = arg[1];
                value[1] = '\0';

                // Get the flag
                if (!flags.contains(value))
                {
                    // Handle error
                    result.success = false;
                    return result;
                }

                flag = flags[&arg[1]];
                last_flag_name = flag.original_name;
            } else if (arg[1] == '-')
            {
                // Ensure we have more characters
                if (arg[2] == '\0')
                {
                    // Handle null terminator
                    result.success = false;
                    return result;
                }

                // Find the length of the flag
                const long length = str_len(arg) - 2;

                // Ensure we have more characters
                if (length < 1)
                {
                    // Handle null terminator
                    result.success = false;
                    return result;
                }

                // Allocate a new array of characters in order to get
                // the flag (+1 for null terminator)
                char flag_name[length + 1];
                str_copy(arg, flag_name, 2);

                // Get the flag
                if (!flags.contains(flag_name))
                {
                    // Handle error
                    result.success = false;
                    return result;
                }

                last_flag_name = flag_name;
                flag = flags[flag_name];
            } else if (arg[1] == '\0')
            {
                // Handle null terminator
                result.success = false;
                return result;
            }

            // Check for static flags
            if (flag.type == 2)
            {
                result.statics[last_flag.original_name] = true;
                parsing_flag = false;
                continue;
            }

            // Update the flag
            last_flag = flag;
            continue;
        }

        // Handle unexpected value
        result.success = false;
        return result;
    }

    // Ensure we don't end parsing a flag
    if (parsing_flag)
    {
        result.success = false;
    }

    // Ensure we have at least one flag
    if (result.numbers.empty() && result.statics.empty() && result.strings.empty())
    {
        result.success = false;
    }

    return result;
}

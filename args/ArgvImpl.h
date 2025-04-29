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

#ifndef ARGVIMPL_H
#define ARGVIMPL_H

#ifndef FLAG_H
struct Flag;
#endif

class ArgvImpl
{
public:
    // Stores string arguments mapped by their names
    std::map<std::string, std::string> strings;

    // Stores numeric arguments mapped by their names
    std::map<std::string, long> numbers;

    // Stores static flags mapped by their names
    std::map<std::string, bool> statics;

    // Stores whether the parsing result was successful
    bool success = false;

    // Default constructor
    ArgvImpl() = default;

    /**
     * Checks the presence of a static flag by its name.
     * @param name The name of the flag to check.
     * @return A boolean indicating if the flag was found.
     */
    bool has(const char* name) const;

    /**
     * Retrieves a string argument by its name.
     * @param name The name of the argument to retrieve.
     * @return The string value if found, or an empty string if not.
     */
    std::string get_string(const char* name);

    /**
     * Retrieves a numeric argument by its name.
     * @param name The name of the argument to retrieve.
     * @return The numeric value if found, or 0 if not.
     */
    long get_number(const char* name);

    /**
     * Checks if the parsing was successful.
     * @return True if parsing was successful, false otherwise.
     */
    [[nodiscard]] bool is_success() const;
};

/**
 * Parses the command-line arguments and flags into an ArgvImpl object.
 *
 * @param argc The number of elements in argv
 * @param argv A pointer to an array of C-style strings representing the arguments.
 * @param flags A map to Flag objects containing additional parsing options.
 * @return An ArgvImpl object populated with the parsed arguments.
 */
ArgvImpl parse(int argc, const char** argv, std::map<std::string, Flag> flags);

#endif //ARGVIMPL_H

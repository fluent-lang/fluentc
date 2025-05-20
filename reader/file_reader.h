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
// Created by rodrigo on 5/1/25.
//

#ifndef FILE_READER_H
#define FILE_READER_H
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>

inline std::string read_file(const char *& path)
{
    // Read the file at the specified path
    std::ifstream file(path);
    if (!file.is_open())
    {
        // Print an error message
        throw std::runtime_error("Error: Could not open file");
    }

    // Read the file contents
    std::stringstream buffer;
    buffer << file.rdbuf();  // Read the whole file
    return buffer.str();  // Convert to string
}

#endif //FILE_READER_H

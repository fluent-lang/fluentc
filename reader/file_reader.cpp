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

#include "file_reader.h"
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <chrono>

std::string read_file(const std::string& path)
{
    // Read the file at the specified path
    std::ifstream file(path);
    if (!file.is_open())
    {
        // Print an error message
        throw std::runtime_error("Error: Could not open file");
        exit(1);
    }

    // Read the file contents
    std::stringstream buffer;
    buffer << file.rdbuf();  // Read the whole file
    return buffer.str();  // Convert to string
}
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

#include <fstream>
#include <string>
#include "file_reader.h"

std::string read_file(const std::string& path)
{
    // Try to read the file
    std::ifstream file_stream(path);

    // Check for failure
    if (!file_stream.is_open())
    {
        return "";
    }

    // Read the file contents
    std::string file_contents;
    while (file_stream.good())
    {
        file_stream >> file_contents;
    }

    // Close the file
    file_stream.close();
    return file_contents;
}
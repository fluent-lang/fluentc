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
// Created by rodrigo on 5/23/25.
//

#ifndef FLUENTC_VERSION_PICKER_H
#define FLUENTC_VERSION_PICKER_H

#include <algorithm>
#include <filesystem>
#include <string>

inline std::string locate_msvc_version(const std::string& path)
{
    int greatest_version = 0;
    std::string selected_version;

    // Iterate over all files in the directory
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        const std::filesystem::path& f_path = entry.path();

        // Check that the filename is a number
        if (
            const auto filename = f_path.filename().string();
            isdigit(filename[0])
        )
        {
            // Reassign greatest_msvc_version if the version is greater
            if (
                const int version = std::stoi(filename);
                version > greatest_version
            )
            {
                greatest_version = version;
                selected_version = filename;
            }
        }
    }

    // Check if no version was found
    if (greatest_version == 0)
    {
        throw std::runtime_error("Error: Could not locate Visual Studio or Windows SDK installation user or system-wide.");
    }

    return selected_version;
}

#endif //FLUENTC_VERSION_PICKER_H

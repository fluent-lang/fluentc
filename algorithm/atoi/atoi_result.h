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

#ifndef ATOI_CLASS_H
#define ATOI_CLASS_H

/**
 * \struct AtoiResult
 * Represents the result of an attempt to convert a string to an integer.
 *
 * \var success
 * Indicates whether the conversion was successful.
 *
 * \var value
 * Holds the converted integer value if the conversion was successful.
 * If unsuccessful, the value is undefined.
 */
struct AtoiResult
{
    bool success;
    long value;
};

#endif //ATOI_CLASS_H

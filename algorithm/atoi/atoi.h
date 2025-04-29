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

#ifndef ATOI_H
#define ATOI_H

#ifndef ATOI_CLASS_H
#include "atoi_result.h"
#endif

/**
 * Converts a string to an integer.
 *
 * This function parses the input string and converts it to an integer value.
 * It handles negative numbers, validates the input, and ensures that only
 * valid numeric characters are processed.
 *
 * @param input A null-terminated string representing the number to convert.
 * @return An AtoiResult structure containing:
 *         - `success` (bool): Indicates whether the conversion was successful.
 *         - `value` (long): The converted integer value (or 0 if unsuccessful).
 */
inline AtoiResult atoi_convert(const char* input)
{
    // Check for empty strings
    if (input[0] == '\0')
    {
       return { false, 0 };
    }

    // Handle negative signs
    bool is_negative = false;
    long result = 0;

    // Iterate character by character
    while (*input != '\0')
    {
       // Get the character
       const char c = *input;

       // Handle negatives
       if (c == '-')
       {
          if (is_negative)
          {
             // Return immediately
             return { false, 0 };
          }

          is_negative = true;

          // Move onto the next character
          input++;
          continue;
       }

       // Validate characters
       if (c > '9' || c < '0')
       {
          // Return immediately
          return { false, 0 };
       }

       // Add to the result
       result = result * 10 + (c - '0');

       // Move onto the next character
       input++;
    }

    // Return
    if (is_negative)
    {
       return { true, -result };
    }

    return { true, result };
}

#endif //ATOI_H

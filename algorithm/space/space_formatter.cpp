//
// Created by rodrigo on 4/29/25.
//

#include <string>

#include "../../structure/string/string_builder.h"
#include "space_formatter.h"

std::string add_spaces(const size_t spaces, const std::string &left, const std::string &right)
{
    // Calculate the capacity
    long candidate_spaces = spaces - left.size();
    if (candidate_spaces < 0)
    {
        candidate_spaces = 1;
    }

    // Create a new string builder
    StringBuilder builder;

    // Write the left string
    builder.write(left);

    // Write the spaces
    for (size_t i = 0; i < candidate_spaces; i++)
    {
        builder.write(' ');
    }

    // Write the right string
    builder.write(right);

    // Return the string
    return builder.collect();
}
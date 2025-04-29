//
// Created by rodrigo on 4/28/25.
//

#ifndef STR_LEN_H
#define STR_LEN_H

/**
 * @brief Calculates the length of a null-terminated C-style string.
 *
 * This function iterates through the characters of the input string
 * until it encounters the null terminator (`\0`), counting the number
 * of characters in the process.
 *
 * @param str A pointer to the null-terminated C-style string.
 * @return The length of the string (number of characters before the null terminator).
 */
inline long str_len(const char *str)
{
    long result = 0;

    // Iterate character by character
    while (*str != '\0')
    {
        result++;
        // Move to the next character
        str++;
    }

    return result;
}

#endif //STR_LEN_H

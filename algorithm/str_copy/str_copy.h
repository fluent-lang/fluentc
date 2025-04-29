//
// Created by rodrigo on 4/28/25.
//

#ifndef STR_COPY_H
#define STR_COPY_H

/**
 * @brief Copies a substring from the source string (`pivot`) to the target string (`target`).
 *
 * This function starts copying characters from the `pivot` string beginning at the specified
 * `start` index and continues until the null terminator (`\0`) is encountered. The copied
 * substring is null-terminated in the `target` string.
 *
 * @param pivot The source string to copy from. Must be null-terminated.
 * @param target The destination string to copy to. Must have sufficient space to hold the copied substring.
 * @param start The starting index in the `pivot` string from which to begin copying.
 *
 * @note It is the caller's responsibility to ensure that the `start` index is within bounds
 * of the `pivot` string and that the `target` string has enough space to accommodate the copied data.
 */
inline void str_copy(const char* pivot, char* target, const size_t start)
{
    // Note: it is the responsibility of the caller to provide a start
    // index that is not out of bounds

    // Copy character by character
    size_t i = start;
    size_t real_i = 0;

    while (pivot[i] != '\0')
    {
        target[real_i] = pivot[i];
        i++;
        real_i++;
    }

    // Add the null terminator
    target[real_i] = '\0';
}

#endif //STR_COPY_H

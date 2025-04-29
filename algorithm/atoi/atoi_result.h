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

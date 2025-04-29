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
// Created by rodrigo on 4/29/25.
//

#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

class StringBuilder {
    size_t length = 0; ///< Current length of the string being built.
    size_t written = 0; ///< Number of characters written to the buffer.
    size_t capacity = 55; ///< Total capacity of the buffer.
    char *buffer{}; ///< Pointer to the dynamically allocated buffer.

    /**
     * Ensures there is enough space in the buffer for additional characters.
     * Allocates more memory if needed.
     */
    void request_space();

    /**
        * Initializes the StringBuilder by allocating the buffer
        * and setting up the initial state.
    */
    void init();

public:
    /**
     * Constructs a StringBuilder with a specified initial capacity.
     * @param capacity The initial capacity of the buffer.
     */
    explicit StringBuilder(size_t capacity);

    /**
     * Default constructor for StringBuilder.
     * Initializes with default capacity.
     */
    StringBuilder();

    /**
     * Destructor for StringBuilder.
     * Cleans up resources used by the object.
     */
    ~StringBuilder();

    /**
     * Writes a C-style character to the buffer.
     * @param c The character to write.
    */
    void write(char c);

    /**
     * Writes a null-terminated C-style string to the buffer.
     * @param str Pointer to the null-terminated string to write.
    */
    void write(const char *str);

    /**
     * Writes a C++ std::string to the buffer.
     * @param str The std::string to write.
    */
    void write(std::string str);

    /**
     * Collects the built string and returns it.
     * The caller is responsible for freeing the returned string.
     * @return A C++ std::string.
     */
    std::string collect();
};

#endif //STRING_BUILDER_H

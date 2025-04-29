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

#include <string>
#include "string_builder.h"
#include <cstdio>
#include <cstdlib>

void StringBuilder::init()
{
    // Allocate the initial buffer
    this->buffer = static_cast<char *>(malloc(sizeof(char) * this->capacity));

    // Check for allocation errors
    if (this->buffer == nullptr)
    {
        perror("malloc");
        exit(1);
    }
}

void StringBuilder::request_space()
{
    // Reallocate the buffer
    const auto new_buffer = static_cast<char *>(realloc(buffer, sizeof(char) * (length + capacity)));
    if (new_buffer == nullptr)
    {
        free(buffer);
        perror("realloc");
        exit(1);
    }

    // Update the buffer pointer
    this->buffer = new_buffer;
    this->written = 0;
}

void StringBuilder::write(const char c)
{
    // Check if we have enough space in the buffer
    if (written == capacity)
    {
        // Request more space
        request_space();
    }

    // Write the character to the buffer
    this->buffer[length] = c;
    this->length++;
    this->written++;
}

void StringBuilder::write(const char* str)
{
    // Write all characters to the buffer
    while (*str != '\0')
    {
        // Get the character
        const char c = *str;

        // Write the character directly
        this->write(c);

        // Move onto the next character
        str++;
    }
}

void StringBuilder::write(std::string str) {
    // Write all characters to the buffer
    for (const char c : str)
    {
        // Write the character directly
        this->write(c);
    }
}

char *StringBuilder::collect()
{
    // Detect if we have enough space to add the null terminator
    if (this->written == capacity)
    {
        request_space();
    }

    // Write a null terminator
    this->buffer[length] = '\0';

    // Return the buffer
    return this->buffer;
}

StringBuilder::StringBuilder(const size_t capacity) : capacity(capacity)
{
    this->init();
}

StringBuilder::~StringBuilder()
{
    // Free the buffer
    free(buffer);
}
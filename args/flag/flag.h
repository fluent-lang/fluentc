//
// Created by rodrigo on 4/28/25.
//

#ifndef FLAG_H
#define FLAG_H

struct Flag
{
    // DO NOT SET MANUALLY
    mutable std::string original_name;
    // Information fields
    const char *description;
    const char *shortcut;
    // 0 = string
    // 1 = int
    // 2 = static
    unsigned int type;
};

#endif //FLAG_H

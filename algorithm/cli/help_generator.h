//
// Created by rodrigo on 4/29/25.
//

#ifndef HELP_GENERATOR_H
#define HELP_GENERATOR_H

#ifndef FLAG_H
#include "../../args/flag/flag.h"
#endif

void print_help(const char *program_name, std::map<std::string, Flag> flags);

#endif //HELP_GENERATOR_H

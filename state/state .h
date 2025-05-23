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
// Created by rodrigo on 5/23/25.
//

#ifndef FLUENTC_STATE_H
#define FLUENTC_STATE_H
#include <cstdio>

#include "../ansi/ansi.h"

namespace fluent::compiler::state
{
    typedef enum
    {
        Lexing,
        Parsing,
        Building,
        Compiling,
        Linking,
    } State;

    typedef struct
    {
        State state;
        const char *additional;
        std::chrono::high_resolution_clock::time_point start;
    } StateWaiter;

    // Define the waiters
    inline StateWaiter current_waiter;
    inline bool waiting = false;

    inline void print_state(const State state)
    {
        switch (state)
        {
            case Lexing:
                printf("%sLexing", ansi::BoldBrightBlue);
            break;
            case Parsing:
                printf("%sParsing", ansi::BoldBrightPurple);
            break;
            case Building:
                printf("%sBuilding", ansi::BoldBrightGreen);
            break;
            case Compiling:
                printf("%sCompiling", ansi::BoldBrightYellow);
            break;
            case Linking:
                printf("%sLinking", ansi::BoldBrightGreen);
            break;
        }
    }

    inline void done()
    {
        // Make sure we are waiting
        if (!waiting)
        {
            throw std::runtime_error("Error: State is not waiting");
        }

        // Get the elapsed time
        const std::chrono::duration<double, std::micro> elapsed = std::chrono::high_resolution_clock::now() - current_waiter.start;

        // Print the state and additional information
        print_state(current_waiter.state);
        if (current_waiter.additional != nullptr)
        {
            printf(" %s", current_waiter.additional);
        }

        // Print the time taken
        printf("%s%s (%.2fμs)%s\n", ansi::Reset, ansi::BrightBlack, elapsed.count(), ansi::Reset);
        waiting = false;
    }

    inline void emit(const State state, const char *additional)
    {
        // Make sure we are not waiting
        if (waiting)
        {
            // Guard against double wait
            done();
        }

        // Print the state
        print_state(state);

        // Print any additional information
        if (additional != nullptr)
        {
            printf(" %s", additional);
        }

        // Print a carriage return to overwrite the line later
        printf("\r");

        // Create a new waiter
        const StateWaiter waiter{
            .state = state,
            .additional = additional,
            .start = std::chrono::high_resolution_clock::now(),
        };

        // Add the waiter to the map
        current_waiter = waiter;
        waiting = true;
    }
}

#endif //FLUENTC_STATE_H

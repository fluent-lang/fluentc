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
// Created by rodrigo on 5/24/25.
//

#ifndef FLUENTC_UTIL_TRIPLE_H
#define FLUENTC_UTIL_TRIPLE_H

namespace fluent::util
{
    template<typename T1, typename T2, typename T3>
    struct Triple
    {
        T1 first;
        T2 second;
        T3 third;

        Triple(const T1 &first, const T2 &second, const T3 &third)
            : first(first), second(second), third(third) {}
    };
}

#endif //FLUENTC_UTIL_TRIPLE_H

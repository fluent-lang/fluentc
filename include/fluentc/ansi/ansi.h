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

#ifndef FLUENTC_ANSI_H
#define FLUENTC_ANSI_H

namespace fluent::ansi {
    inline auto *Reset        = "\033[0m";
    inline auto *BrightRed    = "\033[91m";
    inline auto *BrightYellow = "\033[93m";
    inline auto *BrightPurple = "\033[95m";
    inline auto *BrightBlack  = "\033[90m";

    inline auto *BoldBrightBlue   = "\033[1;94m";
    inline auto *BoldBrightGreen  = "\033[1;92m";
    inline auto *BoldBrightRed    = "\033[1;91m";
    inline auto *BoldBrightYellow = "\033[1;93m";
    inline auto *BoldBrightPurple = "\033[1;95m";
}


#endif //FLUENTC_ANSI_H

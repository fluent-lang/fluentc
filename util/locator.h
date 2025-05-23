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

#ifndef FLUENTC_POSIX_LIB_LOCATOR_H
#define FLUENTC_POSIX_LIB_LOCATOR_H

// Define all possible libc paths
inline const char *possible_libc[11] = {
    "/lib64/ld-linux-x86-64.so.2", // x86_64 AMD/Intel
    "/lib/ld-linux-x86-64.so.2", // x86_64 AMD/Intel
    "/lib/ld-linux.so.2", // i386/i686 (32-bit Intel/AMD)
    "/lib/i386-linux-gnu/ld-linux.so.2", // i386/i686 (32-bit Intel/AMD)
    "/lib/ld-linux-armhf.so.3", // ARM (32 bits)
    "/lib/arm-linux-gnueabihf/ld-linux-armhf.so.3", // ARM (32-bits)
    "/lib/ld-linux-aarch64.so.1", // ARM (64 bits)
    "/lib/aarch64-linux-gnu/ld-linux-aarch64.so.1", // ARM (64 bits)
    "/lib/ld.so.1", // General
    "/lib64/ld64.so.1", // General (64 bits)
    "/lib/mips-linux-gnu/ld.so.1", // MIPS (32-bit and 64-bit)
};

inline const char *locate_libc()
{

}

inline void locate_posix_lib()
{

}

#endif //FLUENTC_POSIX_LIB_LOCATOR_H

cmake_minimum_required(VERSION 3.30)
project(fluentc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find LLVM
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVM Include Dir: ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM Libraries: ${LLVM_LIBRARY_DIRS}")

# Add LLVM definitions and include directories
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Define your executable
add_executable(fluentc main.cpp
        args/ArgvImpl.cpp
        args/ArgvImpl.h
        algorithm/atoi/atoi.h
        algorithm/atoi/atoi_result.h
        args/flag/flag.h
        args/flag/flag.cpp
        algorithm/strlen/str_len.h
        algorithm/str_copy/str_copy.h)

# Get the LLVM libraries using llvm-config
execute_process(COMMAND llvm-config --libs all OUTPUT_VARIABLE LLVM_LIBS_STRING OUTPUT_STRIP_TRAILING_WHITESPACE)
separate_arguments(LLVM_LIBS UNIX_COMMAND "${LLVM_LIBS_STRING}")

# Get the system library paths
execute_process(COMMAND llvm-config --libdir OUTPUT_VARIABLE LLVM_LIBDIR OUTPUT_STRIP_TRAILING_WHITESPACE)
link_directories(${LLVM_LIBDIR})

# Link against LLVM
target_link_libraries(fluentc PRIVATE ${LLVM_LIBS})

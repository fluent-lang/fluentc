include(FetchContent)

cmake_minimum_required(VERSION 3.30)
project(fluentc)

FetchContent_Declare(
        unordered_dense
        GIT_REPOSITORY https://github.com/martinus/unordered_dense.git
        GIT_TAG        main
)

FetchContent_Declare(
        fluent_parser
        GIT_REPOSITORY https://github.com/fluent-lang/ir_parser
        GIT_TAG        master
)

FetchContent_Declare(
        cli
        GIT_REPOSITORY https://github.com/fluent-lang/cli
        GIT_TAG        master
)


FetchContent_Declare(
        fluent_libc
        GIT_REPOSITORY https://github.com/rodrigoo-r/fluent_libc
        GIT_TAG        master
)

FetchContent_MakeAvailable(unordered_dense)
FetchContent_MakeAvailable(fluent_parser)
FetchContent_MakeAvailable(cli)
FetchContent_MakeAvailable(fluent_libc)

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
        reader/file_reader.cpp
        reader/file_reader.h
        core/compiler.h)

# Get the LLVM libraries using llvm-config
execute_process(COMMAND llvm-config --libs all OUTPUT_VARIABLE LLVM_LIBS_STRING OUTPUT_STRIP_TRAILING_WHITESPACE)
separate_arguments(LLVM_LIBS UNIX_COMMAND "${LLVM_LIBS_STRING}")

# Get the system library paths
execute_process(COMMAND llvm-config --libdir OUTPUT_VARIABLE LLVM_LIBDIR OUTPUT_STRIP_TRAILING_WHITESPACE)
link_directories(${LLVM_LIBDIR})

# Link against LLVM
target_link_libraries(fluentc PRIVATE ${LLVM_LIBS})
target_include_directories(fluentc PRIVATE ${CMAKE_BINARY_DIR}/_deps/unordered_dense-src/include)
target_include_directories(fluentc PRIVATE ${CMAKE_BINARY_DIR}/_deps/fluent_libc-src/include)
target_include_directories(fluentc PRIVATE ${CMAKE_BINARY_DIR}/_deps/fluent_parser-src/include)
target_include_directories(fluentc PRIVATE ${CMAKE_BINARY_DIR}/_deps/cli-src/include)
target_link_libraries(fluentc PRIVATE unordered_dense)
target_link_libraries(fluentc PRIVATE fluent_parser)
target_link_libraries(fluentc PRIVATE cli)
target_link_libraries(fluentc PRIVATE fluent_libc)

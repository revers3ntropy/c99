cmake_minimum_required(VERSION 3.25)
project(c99 C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "-Wall -Werror -Wextra -Wnull-dereference -Wwrite-strings -Wformat=2 -Wcast-align -Wpedantic -Wno-sign-conversion -Wno-implicit-fallthrough -Wno-maybe-uninitialized -Wno-missing-field-initializers -g") # -g adds extra debug info for valgrind to use

add_executable(c99
        src/main.c

        src/ast/ast.c 
        src/ast/empty_block.c 
        src/ast/function_def.c 

        src/parsing/parser.c
        src/parsing/tokens.c
)

set_property(TARGET c99 PROPERTY C_STANDARD 99)

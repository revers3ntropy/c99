cmake_minimum_required(VERSION 3.25)
project(c99 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Werror")

add_executable(c99
    src/main.c
    src/ds/list.c
    src/ast/ast.c
    src/ast/empty_block.c
    src/ast/function_def.c
    src/parse/parser.c
    src/parse/lexer.c
)

set_property(TARGET c99 PROPERTY C_STANDARD 99)

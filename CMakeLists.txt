cmake_minimum_required(VERSION 4.0)
project(llic C)

set(CMAKE_C_STANDARD 99)

add_executable(llic main.c
        lib/bytecode.c
        lib/bytecode.h
        lib/vm.c
        lib/vm.h
        lib/config.c
        lib/config.h
        lib/stack.c
        lib/stack.h
        lib/register.c
        lib/register.h
        lib/command.c
        lib/command.h
)

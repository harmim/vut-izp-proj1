cmake_minimum_required(VERSION 3.6)
project(proj1)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -Werror")

set(SOURCE_FILES proj1.c)
add_executable(proj1 ${SOURCE_FILES})


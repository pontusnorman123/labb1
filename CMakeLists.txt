cmake_minimum_required(VERSION 3.21)
project(labb1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(labb1
        lex.h
        main.cpp
        nodes.h
        parse.h)

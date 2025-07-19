cmake_minimum_required(VERSION 3.22)
project(Ex02)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(Ex02
        thread.cpp
        uthreads.cpp
)
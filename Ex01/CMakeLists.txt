cmake_minimum_required(VERSION 3.26)
project(Ex01)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
add_executable(Ex01
        measure.cpp
        measure.h
        memory_latency.cpp
        memory_latency.h)

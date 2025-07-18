cmake_minimum_required(VERSION 3.22)
project(Ex04)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(Ex04
        PhysicalMemory.cpp
        VirtualMemory.cpp
        Tests/SimpleTest.cpp
#        Tests/test1_write_read_all_virtual_memory.cpp
#        Tests/test2_write_one_page_twice_and_read.cpp
)

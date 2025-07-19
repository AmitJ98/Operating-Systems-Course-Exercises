cmake_minimum_required(VERSION 3.22)
project(Ex03)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Barrier)

add_executable(Ex03
        Barrier/Barrier.cpp
        MapReduceFramework.cpp
#        Test/test1-1_thread_1_process.cpp
#        Test/test4-1_thread_4_process.cpp
        Sample_Client/SampleClient.cpp
)

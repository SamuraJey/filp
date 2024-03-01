cmake_minimum_required(VERSION 3.24)
project(FILP-OK)

set(CMAKE_CXX_STANDARD 17)

add_executable(main
        t1/main.cpp
        t1/CComparator.h t1/CComparator.cpp
        t1/CAllocator.h t1/CAllocator.cpp
)


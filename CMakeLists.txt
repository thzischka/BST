cmake_minimum_required(VERSION 3.10)
project(program3)

set(CMAKE_CXX_STANDARD 11)

include_directories(Prompt)

add_executable(program3
        BST.cpp
        BST.h
        BSTSanityCheck.cxx
        CreateData.cxx
        json.hpp
        Makefile)

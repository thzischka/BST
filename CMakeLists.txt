cmake_minimum_required(VERSION 3.10)
project(program3)

set(CMAKE_CXX_STANDARD 11)

include_directories(Prompt)

add_executable(program3
        Prompt/BST.cpp
        Prompt/BST.h
        Prompt/BSTSanityCheck.cxx
        Prompt/CreateData.cxx
        Prompt/json.hpp
        Prompt/Makefile)

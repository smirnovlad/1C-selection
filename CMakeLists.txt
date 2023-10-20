cmake_minimum_required(VERSION 3.26)
project(1C_selection)

set(CMAKE_CXX_STANDARD 17)


add_executable(dir_comparator
        string_utils.h
        directory_comparator.h
        main.cpp)

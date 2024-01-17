cmake_minimum_required(VERSION 3.26)
project(CppBankManagementSystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(CppBankManagementSystem main.cpp
        bank.cpp
        bank.h)

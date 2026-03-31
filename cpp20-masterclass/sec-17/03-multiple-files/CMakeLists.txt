cmake_minimum_required(VERSION 3.20)

# Project name
project(MainCpp)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(main main.cpp
                compare.h compare.cpp
                operations.h operations.cpp
                some_other_file.cpp)

# For multi-file projects with headers and separate .cpp files
# add_executable(main main.cpp dog.cpp dog.h cat.cpp cat.h)
cmake_minimum_required(VERSION 3.20)
project(untitled28)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")

add_executable(untitled28 main.cpp)

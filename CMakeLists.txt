cmake_minimum_required(VERSION 2.8)
project(AiBToS_Project2)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

set(CMAKE_CXX_FLAGS "-O3 -Wall -std=c++0x -march=native")

set(SOURCE_FILES
        src/Program.cpp src/interface/Parser.h src/interface/NeighborJoining.h src/Naive.cpp src/Naive.h src/SimpleParser.cpp src/SimpleParser.h)

add_executable(AiBToS_Project2 ${SOURCE_FILES})

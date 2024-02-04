cmake_minimum_required(VERSION 3.25)
project(Big_Integer)

set(CMAKE_CXX_STANDARD 98)

add_library(Big_Integer SHARED library.cpp bigint.cpp bigint.h)

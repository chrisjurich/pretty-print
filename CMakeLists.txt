cmake_minimum_required(VERSION 3.16)
project(pretty_print)

set(CMAKE_CXX_STANDARD 20)

include_directories(/Users/cjurich/projects/pretty-print/)

set_property(
        SOURCE pretty_print.h
        PROPERTY LANGUAGE CXX
)

add_library(PP pretty_print.h)

target_link_libraries(PP)

add_executable(pretty_print main.cpp)

target_link_libraries(pretty_print PP)
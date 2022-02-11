cmake_minimum_required(VERSION 3.20)
project(Architect)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_EXE main.cpp myTerm.cpp myTerm.h)
set(SOURCE_LIB mySimpleComputer.cpp)
set(SOURCE_LIB_1 myTerm.cpp)

add_library(mySimpleComputer STATIC ${SOURCE_LIB})
add_library(myTerm STATIC ${SOURCE_LIB_1})

add_executable(Architect ${SOURCE_EXE})

target_link_libraries(Architect mySimpleComputer myTerm)

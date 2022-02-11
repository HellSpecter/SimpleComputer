cmake_minimum_required(VERSION 3.20)
project(Architect)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_EXE main.cpp)
set(SOURCE_LIB mySimpleComputer.cpp)

add_library(mySimpleComputer STATIC ${SOURCE_LIB})

add_executable(Architect ${SOURCE_EXE})

target_link_libraries(Architect mySimpleComputer)

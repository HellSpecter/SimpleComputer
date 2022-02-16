cmake_minimum_required(VERSION 3.20)
project(Architect)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_EXE src/main.cpp src/myTerm.cpp src/myTerm.h src/myBigChars.cpp src/myBigChars.h)
set(SOURCE_LIB src/mySimpleComputer.cpp)
set(SOURCE_LIB_1 src/myTerm.cpp)
set(SOURCE_LIB_2 src/myBigChars.cpp)

add_library(mySimpleComputer STATIC ${SOURCE_LIB})
add_library(myTerm STATIC ${SOURCE_LIB_1})
add_library(myBigChars STATIC ${SOURCE_LIB_2})

add_executable(Architect ${SOURCE_EXE})

target_link_libraries(Architect mySimpleComputer myTerm myBigChars)

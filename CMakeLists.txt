cmake_minimum_required(VERSION 3.20)
project(Architect)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_EXE src/main.cpp src/myTerm.cpp src/myTerm.h src/myBigChars.cpp src/myBigChars.h src/myReadKey.cpp src/myReadKey.h src/mySimpleHandler.cpp src/mySimpleHandler.h)
set(SOURCE_LIB src/mySimpleComputer.cpp)
set(SOURCE_LIB_1 src/myTerm.cpp)
set(SOURCE_LIB_2 src/myBigChars.cpp)
set(SOURCE_LIB_3 src/myReadKey.cpp)
set(SOURCE_LIB_4 src/mySimpleHandler.cpp)

add_library(mySimpleComputer STATIC ${SOURCE_LIB})
add_library(myTerm STATIC ${SOURCE_LIB_1})
add_library(myBigChars STATIC ${SOURCE_LIB_2})
add_library(myReadKey STATIC ${SOURCE_LIB_3})
add_library(mySimpleHandler STATIC ${SOURCE_LIB_4})

add_executable(Architect ${SOURCE_EXE})

target_link_libraries(Architect mySimpleComputer myTerm myBigChars myReadKey mySimpleHandler)

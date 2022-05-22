cmake_minimum_required(VERSION 3.10)
project(cppfinal CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB sources src/*.h src/*.cpp)
add_executable(cppfinal ${sources})
set_property(TARGET cppfinal PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/data")

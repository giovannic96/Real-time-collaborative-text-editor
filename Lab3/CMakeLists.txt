cmake_minimum_required(VERSION 3.14)
project(Lab3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab3 main.cpp NetworkServer.cpp NetworkServer.h SharedEditor.cpp SharedEditor.h Message.cpp Message.h Symbol.cpp Symbol.h)
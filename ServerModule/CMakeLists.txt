cmake_minimum_required(VERSION 3.14)
project(ServerModule)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
add_executable(ServerModule main.cpp myServer.cpp myServer.h session.cpp session.h jsonUtility.cpp jsonUtility.h)
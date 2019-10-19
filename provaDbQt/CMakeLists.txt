cmake_minimum_required(VERSION 3.14)
project(provaDbQt)

set(CMAKE_CXX_STANDARD 14)
find_package(Qt5Sql REQUIRED)
add_executable(provaDbQt main.cpp)
target_link_libraries(provaDbQt Qt5::Sql)
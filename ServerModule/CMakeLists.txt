cmake_minimum_required(VERSION 3.14)
project(ServerModule)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lcurl")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Qt5Sql REQUIRED)

add_compile_options(-l sqlite3)
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
#add_executable(ServerModule main.cpp myServer.cpp header_files/myServer.h session.cpp header_files/session.h jsonUtility.cpp header_files/jsonUtility.h dbService.cpp header_files/dbService.h room.cpp header_files/room.h participant.cpp header_files/participant.h message.cpp header_files/message.h fileUtility.cpp header_files/fileUtility.h symbol.cpp header_files/symbol.h File.cpp header_files/File.h email.cpp header_files/email.h header_files/header_files/symbolStyle.h symbolStyle.cpp)
add_executable(ServerModule main.cpp myServer.cpp header_files/myServer.h session.cpp header_files/session.h jsonUtility.cpp header_files/jsonUtility.h dbService.cpp header_files/dbService.h room.cpp header_files/room.h participant.cpp header_files/participant.h message.cpp header_files/message.h fileUtility.cpp header_files/fileUtility.h symbol.cpp header_files/symbol.h File.cpp header_files/File.h header_files/symbolStyle.h symbolStyle.cpp)

#target_link_libraries(ServerModule LINK_PUBLIC sqlite3 Qt5::Sql curl)
target_link_libraries(ServerModule LINK_PUBLIC sqlite3 Qt5::Sql)

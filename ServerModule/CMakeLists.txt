cmake_minimum_required(VERSION 3.14)
project(ServerModule)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-l sqlite3)
set(LIBRARIES sqlite3.dll)
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
add_executable(ServerModule main.cpp myServer.cpp header_files/myServer.h session.cpp header_files/session.h jsonUtility.cpp header_files/jsonUtility.h dbService.cpp header_files/dbService.h room.cpp header_files/room.h participant.cpp header_files/participant.h message.cpp header_files/message.h)
target_link_libraries(ServerModule LINK_PUBLIC sqlite3)

cmake_minimum_required (VERSION 2.8.11)
project (CrunchLuaSol)
set(CMAKE_CXX_FLAGS "-std=c++14")

find_package(Lua 5.3 REQUIRED)
include_directories (${CMAKE_CURRENT_SOURCE_DIR} /usr/local/include  ${LUA_INCLUDE_DIR})
link_directories(/usr/local/lib)

set (CRUNCHLUASOLDEPS Stick pthread ${LUA_LIBRARIES})

set (CRUNCHLUASOLINC
CrunchLuaSol/CrunchLuaSol.hpp
)

install (FILES ${CRUNCHLUASOLINC} DESTINATION /usr/local/include/CrunchLuaSol)
add_subdirectory (Tests)

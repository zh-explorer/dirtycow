cmake_minimum_required(VERSION 3.10)
project(dirtycow C)

set(CMAKE_C_STANDARD 11)

add_executable(dirtycow dirtycow.c exploit.c exploit.h unit.c unit.h)

target_link_libraries(dirtycow pthread)
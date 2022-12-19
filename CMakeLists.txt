cmake_minimum_required(VERSION 3.10)
project(dirtycow C)

set(CMAKE_C_STANDARD 11)

add_executable(dirtycow dirtycow.c exploit.c exploit.h unit.c unit.h vdso_backdoor.c vdso_backdoor.h dirtycow.h)

target_link_libraries(dirtycow pthread)

add_subdirectory(${PROJECT_SOURCE_DIR}/backdoor)

add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/shellcode.c
        COMMAND python3 ${CMAKE_SOURCE_DIR}/script/file_strip.py ${CMAKE_BINARY_DIR}/backdoor/ScMaker ${CMAKE_BINARY_DIR}/shellcode.c
        DEPENDS ScMaker
        VERBATIM
)

target_sources(dirtycow PRIVATE ${CMAKE_BINARY_DIR}/shellcode.c)
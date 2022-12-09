cmake_minimum_required(VERSION 3.10)
project(ScMaker C)

set(CMAKE_C_STANDARD 99)

add_executable(ScMaker backdoor.c)

set(COMMON_C_FLAG "-D_FORTIFY_SOURCE=0 -fshort-wchar -fno-builtin-printf -fno-asynchronous-unwind-tables -ffreestanding -ffunction-sections -fdata-sections -fPIC -fPIE -pie -Os")
set(COMMON_LINK_FLAG "-nostartfiles -nodefaultlibs -Wl,--gc-sections -fPIC -fPIE -pie -Os")

include(x86_64_linux.cmake)
set(LINK_SCRIPT standalone_elf64.lds)
include(${PROJECT_SOURCE_DIR}/linux_syscalls/linux.cmake)

target_link_libraries(ScMaker libgcc.a)
set(CMAKE_C_FLAGS "${COMMON_C_FLAG}")
set(CMAKE_EXE_LINKER_FLAGS "${COMMON_LINK_FLAG} -T${CMAKE_SOURCE_DIR}/standalone_elf64.lds")
include(${PROJECT_SOURCE_DIR}/libc/libc.cmake)

add_custom_target(
        ShellcodeBin
#        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shellcode.bin
        COMMAND python3 ${CMAKE_SOURCE_DIR}/script/file_strip.py ${CMAKE_BINARY_DIR}/ScMaker ${CMAKE_BINARY_DIR}/shellcode.bin
        DEPENDS ScMaker
        VERBATIM
)
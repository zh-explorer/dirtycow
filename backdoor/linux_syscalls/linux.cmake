
target_sources(ScMaker PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/syscall.c
        ${CMAKE_CURRENT_LIST_DIR}/unistd.c
        ${CMAKE_CURRENT_LIST_DIR}/stat.c
        ${CMAKE_CURRENT_LIST_DIR}/signal.c
        ${CMAKE_CURRENT_LIST_DIR}/fcntl.c
        ${CMAKE_CURRENT_LIST_DIR}/libc_warrper.c
        ${CMAKE_CURRENT_LIST_DIR}/socket.c
        )

target_include_directories(ScMaker PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )
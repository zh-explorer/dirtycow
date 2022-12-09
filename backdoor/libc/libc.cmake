target_sources(ScMaker PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/string.c
        ${CMAKE_CURRENT_LIST_DIR}/errno.c
        ${CMAKE_CURRENT_LIST_DIR}/signal.c
        )

target_include_directories(ScMaker PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )
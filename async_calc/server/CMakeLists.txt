add_executable(calc_server
    server.cpp
)

wa_codegen(
    TARGET       server_dispatch
    SOURCE       ${CMAKE_CURRENT_SOURCE_DIR}/dispatch/dispatch.cpp
    MODE         SERVER
    INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(server_dispatch
    PRIVATE
        wanime::server-sdk
)

target_link_libraries(calc_server PRIVATE
    server_dispatch
    wanime::server-sdk
)

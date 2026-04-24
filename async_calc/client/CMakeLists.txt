add_executable(calc_client
    client.cpp
)

wa_codegen(
    TARGET       client_dispatch
    SOURCE       ${CMAKE_CURRENT_SOURCE_DIR}/processor/calc.cpp
    MODE         CLIENT 
    INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(client_dispatch
    wanime::client-sdk
)

target_link_libraries(calc_client
    client_dispatch
    wanime::client-sdk
)

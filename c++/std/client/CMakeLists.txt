add_executable(client
    client.cpp
)

wa_codegen(
    TARGET       client_process_lib
    SOURCES      ${CMAKE_CURRENT_SOURCE_DIR}/process/exmp.warpc.cpp
    MODE         CLIENT 
    INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
    EXT_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../../schema/exmp.hpp
    EXT_LIBS
        wanime::client-sdk
        polyglot::polyglot
)

target_link_libraries(client
    client_process_lib
)

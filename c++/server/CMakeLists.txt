wa_codegen(
    TARGET       server_dispatch
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/dispatch/exmp.warpc.cpp
    MODE         SERVER
    HEADLESS     TRUE
    INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    EXT_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../../schema/exmp.hpp
    EXT_LIBS
        polyglot::polyglot
)

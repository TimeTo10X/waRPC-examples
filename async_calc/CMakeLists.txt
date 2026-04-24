cmake_minimum_required(VERSION 4.0.1)
project(calc)

add_compile_definitions(WLOG)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

list(APPEND CMAKE_MODULE_PATH "/usr/local/lib/cmake/wanime-sdk")
include(wa_codegen) 

find_package(wanime-server-sdk REQUIRED)
find_package(wanime-client-sdk REQUIRED)

add_subdirectory(client)
add_subdirectory(server)

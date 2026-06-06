cmake_minimum_required(VERSION 4.1.0)

project(
    cpp_exmp 
    LANGUAGES C CXX
    VERSION 1.0.0
)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 26)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)

include(wa_codegen) 

find_package(wanime-client-sdk REQUIRED)
find_package(wanime-server-sdk REQUIRED)

add_subdirectory(external/polyglot)

add_subdirectory(client)
add_subdirectory(server)

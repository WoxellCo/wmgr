cmake_minimum_required(VERSION 3.28)

project(wmgrlib)

set(CMAKE_C_STANDARD           99)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_EXTENSIONS        OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME} STATIC
    src/wmgr.c src/wmgr_webserver.c
)

include_directories(include)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif()
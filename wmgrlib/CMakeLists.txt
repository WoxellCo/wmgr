cmake_minimum_required(VERSION 3.28)
project(wmgrlib LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME} STATIC
    src/wmgr.c
    src/wmgr_webserver.c
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS OFF
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC wsock32 ws2_32)
endif()
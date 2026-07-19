cmake_minimum_required(VERSION 3.28)

project(wmgr)

set(CMAKE_C_STANDARD           99)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_EXTENSIONS        OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(wmgrlib)

include_directories(include wmgrlib/include)
add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} wmgrlib)

# on windows you can build with MinGW with the following command
# ` cmake -S . -B build -G "MinGW Makefiles"`
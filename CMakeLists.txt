cmake_minimum_required(VERSION 3.30)
project(untitled33 C)

set(CMAKE_C_STANDARD 99)

include_directories("./src")

add_library(whttp STATIC src/whttp.c)

add_executable(untitled33 main.c)

target_link_libraries(untitled33 PRIVATE whttp cjson)

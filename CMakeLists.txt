cmake_minimum_required(VERSION 3.16)

project(gameroom VERSION 0.1 LANGUAGES C RC)

set(EXECUTABLE_OUTPUT_PATH ./${CMAKE_BUILD_TYPE})

add_executable(gameroom
    res/resource.rc
    src/main.c
)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_options(gameroom PRIVATE -SUBSYSTEM:WINDOWS -s)
else()
    target_link_options(gameroom PRIVATE -SUBSYSTEM:WINDOWS)
endif()

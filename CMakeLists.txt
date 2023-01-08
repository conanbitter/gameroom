cmake_minimum_required(VERSION 3.16)

project(gameroom VERSION 0.1 LANGUAGES C RC)

set(EXECUTABLE_OUTPUT_PATH ./${CMAKE_BUILD_TYPE})

add_subdirectory(grf)

add_subdirectory(minefield)
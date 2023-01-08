add_executable(minefield
    res/resource.rc
    main.c
)

target_link_libraries(minefield PRIVATE grf)

target_link_options(minefield PRIVATE -SUBSYSTEM:WINDOWS)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_property(TARGET minefield PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")
endif()
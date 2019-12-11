cmake_minimum_required(VERSION 3.1)

project(kestrelc
        VERSION 0.1
        DESCRIPTION "Kestrel Programming Language Compiler"
        LANGUAGES C)

add_subdirectory(src)

if (BUILD_TESTS STREQUAL no)
# Nothing extra to do here
elseif(BUILD_TESTS STREQUAL yes)
        include(CTest)
        add_subdirectory(unity)
        add_subdirectory(test)
else()
        message(FATAL_ERROR "Unknown BUILD_TEST. Use either yes or no")
endif()

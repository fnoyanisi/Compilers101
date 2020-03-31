cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(kestrelc
        VERSION 0.1
        DESCRIPTION "Kestrel Programming Language Compiler"
        LANGUAGES CXX)

add_subdirectory(src)

if (BUILD_TESTS STREQUAL no)
# Nothing extra to do here
elseif(BUILD_TESTS STREQUAL yes)
        include(CTest)
        add_subdirectory(test)
else()
        message(FATAL_ERROR "Unknown BUILD_TESTS. Use either yes or no")
endif()

project(kestrelc_prog)

set(LEXICAL_SOURCES lexical.c lexical.h)

add_library(liblexical STATIC ${LEXICAL_SOURCES})
target_include_directories(liblexical PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# The main program
add_executable(kestrelc main.c)
target_link_libraries(kestrelc PRIVATE liblexical)
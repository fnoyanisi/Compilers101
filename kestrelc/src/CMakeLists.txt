project(kestrelc_prog)

set(LEXICAL_SOURCES lexical.c lexical.h)

add_library(lexical STATIC ${LEXICAL_SOURCES})
target_include_directories(lexical PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# The main program
add_executable(kestrelc kestrelc.c kestrelc.h)
target_link_libraries(kestrelc PRIVATE lexical)

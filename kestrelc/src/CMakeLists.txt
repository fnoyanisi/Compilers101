project(kestrelc_prog)

set(LEXICAL_SOURCES
        lexical.c errors.c symboltable.c stringpool.c lexsupport.c keywords.c
        lexical.h errors.h symboltable.h stringpool.h lexsupport.h keywords.h)

add_library(lexical STATIC ${LEXICAL_SOURCES})
target_include_directories(lexical PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# The main program
add_executable(kestrelc kestrelc.c kestrelc.h)
target_link_libraries(kestrelc PRIVATE lexical)

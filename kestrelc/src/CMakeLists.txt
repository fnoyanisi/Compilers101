project(kestrelc_prog)

set(LEXICAL_SOURCES
        kestrelc.cpp            kestrelc.h
        parseargs.cpp           parseargs.h
        lexical.cpp             lexical.h
        errors.cpp              errors.h
        symboltable.cpp         symboltable.h
        stringpool.cpp          stringpool.h
        keywords.cpp            keywords.h
)

add_library(lexical STATIC ${LEXICAL_SOURCES})
target_include_directories(lexical PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# The main program
add_executable(kestrelc kestrelc.cpp kestrelc.h)
target_link_libraries(kestrelc PRIVATE lexical)

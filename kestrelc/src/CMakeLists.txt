project(kestrelc_prog)

set(LEXICAL_SOURCES
        kestrelc.cpp            kestrelc.hpp
        parseargs.cpp           parseargs.hpp
        lexical.cpp             lexical.hpp
        errors.cpp              errors.hpp
        symboltable.cpp         symboltable.hpp
        stringpool.cpp          stringpool.hpp
        keywords.cpp            keywords.hpp
)

add_library(lexical STATIC ${LEXICAL_SOURCES})
target_include_directories(lexical PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# The main program
add_executable(kestrelc kestrelc.cpp kestrelc.hpp)
target_link_libraries(kestrelc PRIVATE lexical)

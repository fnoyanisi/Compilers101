project(kestrelc_tests)

add_executable(lextest lextest.cpp catch.hpp)
target_link_libraries(lextest PRIVATE lexical)

add_test(lexer lextest)

project(kestrelc_tests)

add_executable(lextest lextest.c)
target_link_libraries(lextest PRIVATE liblexical unity)

add_test(lexer lextest)

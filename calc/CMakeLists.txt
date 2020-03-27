cmake_minimum_required(VERSION 3.16)
  
project(calc VERSION 1.0
        DESCRIPTION "Simple arithmetic calculator"
        LANGUAGES CXX)

add_executable(calc     src/calc.cpp
                        src/calc.h
                        src/calc_lexer.cpp
                        src/calc_lexer.h
                        src/calc_parser.cpp
                        src/calc_parser.h
                        src/calc_exception.h)

target_compile_features(calc PRIVATE cxx_std_17)

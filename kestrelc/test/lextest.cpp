/*-
 * lextest.c
 * Copyright (c) 2019 Fehmi Noyan Isi
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define CATCH_CONFIG_MAIN

#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <lexical.h> 
#include <symboltable.h>

#include "catch.hpp"

// writes the Kestrel source code into the file
void
write_srcfile(const std::vector<std::string>& series, std::string file, 
  bool newline=true){
  std::ofstream ofs(file);
  for (auto s: series){
    int len = 1;
    std::ostringstream oss;
    if (newline)
      oss << s << std::endl;
    else
      oss << s;

    ofs.write(oss.str().c_str(), s.size()+ ((newline)? 1 : 0 ));
  }
  ofs.close();
}

// writes the output into the output file
// the input is provided by the lexer
void
write_outfile(lexer& l, std::string file) {
  std::ofstream ofs(file);
  do {
    l.lex_put(ofs);
    ofs << std::endl;
    l.lex_advance();
  } while (l.lex_get().type() != ENDFILE);
  ofs.close();
}

// given an expected output, this function compares it with the 
// data read from the file.
// ideally, the data in the file should be the output of the lexer
void 
check_diff(std::vector<std::string> exp, std::string file){
  std::ifstream ifs(file);
  std::vector<std::string> from_file;

  std::string str;
  while(std::getline(ifs, str))
    from_file.push_back(str);  
  ifs.close();
  
  REQUIRE(exp == from_file);
}

// Test cases for the lexer
// many unit tests use write_srcfile() to generate a simple Kestrel source 
// file which is named as test.kl
// the lexer object created for each test case/section uses test.kl as the
// input source file 
// the output of the lexer is written into the output.kl file, which, 
// obviously, has the tokenized output from the lexer
TEST_CASE("LEXER") {
  std::string srcfile_name("test.kl");
  std::string outfile_name("output.kl");

  // the line number should start from 1
  SECTION("Check line numbers") {
    std::vector<std::string> series{"1","2","3","4"};
    write_srcfile(series, srcfile_name);
    
    lexer test(srcfile_name);

    for (int i: {1, 2, 3, 4}) {
      REQUIRE(i == test.lex_get().line());
      test.lex_advance();
    }
  }

  // the lexer should ignore white spaces and only store the numeric 
  // values in lex_next.value
  SECTION("Ignore white spaces") {
    std::vector<std::string> series{"   1","2","3  ","  4","5"};
    write_srcfile(series, srcfile_name);

    lexer test(srcfile_name);

    for (int i: {1, 2, 3, 4, 5}) {
      REQUIRE(i == test.lex_get().value());
      test.lex_advance();
    }
  }

  SECTION("Test punctuation") {
    std::vector<std::string> series{";", "(", ")", ",", "/", "<", "-", 
    "%", "~"};
    write_srcfile(series, srcfile_name);

    lexer test(srcfile_name);
    write_outfile(test, outfile_name);

    check_diff(series, outfile_name);
  }

  SECTION("Test multi-char punctuation") {
    std::vector<std::string> series{";", "/=", "(", ">", ")", ">=", "<=", 
    "-", "/"};
    write_srcfile(series, srcfile_name);

    lexer test(srcfile_name);
    write_outfile(test, outfile_name);

    check_diff(series, outfile_name);
  }

  SECTION("Test comments") {
    std::vector<std::string> series{"-- t", 
                                    "-- a",
                                    "(",
                                    "=",
                                    "-- b",
                                    "-"};
    std::vector<std::string> expected{"(",
                                      "=",
                                      "-"};
    write_srcfile(series, srcfile_name);

    lexer test(srcfile_name);
    write_outfile(test, outfile_name);

    check_diff(expected, outfile_name);
  }

  SECTION("Test string") {
    std::vector<std::string> series{"testing"};
    write_srcfile(series, srcfile_name, false);
    
    lexer test(srcfile_name);
    lexeme lx = test.lex_get();
    char *p = symbol_get(lx.value());
    REQUIRE(p == series.at(0));
  }

  std::filesystem::remove(srcfile_name);
  std::filesystem::remove(outfile_name);
}
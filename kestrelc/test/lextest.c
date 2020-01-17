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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unity.h>
#include <lexical.h>
#include <symboltable.h>

static FILE *s_fd;
static FILE *o_fd;
static const char *s_file = "test.kl";
static const char *o_file = "output.kl";

/* 
* writes the Kestrel code into s_file, which is the source file 
* the lexer reads.
*/
void write_s_file(const char **series, int len){
  int i;
  for (i = 0; i < len; i++){
    if (fprintf(s_fd,"%s\n",series[i]) < 0) {
      perror(s_file);
      exit(EXIT_FAILURE);
    }
  }
  rewind(s_fd);
}

/* 
 * read the source file , s_file, and writes the output in to 
 * o_file 
 */
void write_o_file(){
  lex_open(s_file);
  do {
    if (lex_this.type != NONE){
      lex_put(&lex_this, o_fd);
      fputs("\n",o_fd);
    }
    lex_advance();
  } while (lex_this.type != ENDFILE);
}

/*
 * Comapres each lexeme from the expected output, given by the 
 * parameter s, with the one read from o_file, which is the output 
 * of the lexer.
 * Parameter len is the length of the character string array, s.
 */
void check_diff(const char **s, int len, FILE *fd){
  int i, slen, buflen = 32;
  char buf[buflen]; /* buffer to store the text read from the file */
  
  rewind(fd); /* go back to begining of the file */
  
  for (i=0; i < len; i++) {
    slen = strlen(s[i]);
    if (fgets(buf, buflen, fd) == NULL){
      perror(o_file);
      exit(EXIT_FAILURE);
    }
    TEST_ASSERT_EQUAL_STRING_LEN(s[i], buf,slen);
    lex_advance();
  }
}

/* Executed before each unit test */
void setUp(void){
  if (remove(s_file) == -1 && errno != ENOENT){
    perror(s_file);
    exit(EXIT_FAILURE);
  }

  if (remove(o_file) == -1 && errno != ENOENT){
    perror(o_file);
    exit(EXIT_FAILURE);
  }

  if ((s_fd = fopen(s_file, "w+")) == NULL){
    perror(s_file);
    exit(EXIT_FAILURE);
  }

  if ((o_fd = fopen(o_file, "w+")) == NULL){
    perror(o_file);
    exit(EXIT_FAILURE);
  }

  lex_this.type = NONE;
  lex_this.value = 0;

  lex_next.type = NONE;
  lex_next.value = 0;

  string_init();
}

/* Executed after each unit test */
void tearDown(void){
  fclose(s_fd);
  fclose(o_fd);

  if (remove(s_file) != 0) {
    perror(s_file);
    exit(EXIT_FAILURE);
  }

  if (remove(o_file) != 0) {
    perror(o_file);
    exit(EXIT_FAILURE);
  }
}

/* 
 * lex_open should sucessfuly read the first lexeme and then call
 * lex_advance(), hence after calling lex_open(), lex_get should 
 * return "putstr" as the first identified lexeme
 */
void test_lex_open(void) {
  const char *buf[] = {"putstr( \"Hello world\"+LF, output )"};
  lexeme exp, act;
  char *p;

  exp.type = IDENT;   /* type of the lexeme */
  exp.value = 0;      /* do not compare this field */
  exp.line = 1;       /* current line number */
  exp.pos = 1;        /* one char pass the last one */

  write_s_file(buf,1);

  lex_open(s_file);
  act = lex_get();

  if ((p = symbol_get(lex_next.value)) == NULL)
    TEST_FAIL_MESSAGE("test_lex_open : symbol_get() failed");

  TEST_ASSERT_EQUAL_INT(act.type, exp.type);
  TEST_ASSERT_EQUAL_STRING("putstr", p);
  TEST_ASSERT_EQUAL_INT(act.line, exp.line);
  TEST_ASSERT_EQUAL_INT(act.pos, exp.pos);

  free(p);
}

/*
 * check to see wheter the line numbering work properly
 */
void test_line_number(void) {
  int i, len = 4;
  const char *series[]= {"1","2","3","4"};
  lexeme l;

  write_s_file(series, len);
  lex_open(s_file);

  for (i=1; i<5; i++){
    l = lex_get();
    TEST_ASSERT_EQUAL_INT(i, l.line);
    lex_advance();
  }
}

void test_string(void) {
  int i, len = 1;
  const char *str[] = {"'testing'"};
  lexeme l;
  char *p;

  write_s_file(str, len);
  lex_open(s_file);

  l = lex_get();

  /* without quotes */
  p = symbol_get(lex_next.value);
  TEST_ASSERT_EQUAL_STRING("testing",p);
  free(p);
}

/* 
 * the lexer should ignore white spaces and only store the numeric 
 * values in lex_next.value
 */
void test_numeric(void){
  int i, len = 9;
  const char *series[]= {"   1","2","3","4","5","6","7","8","9"};
  lexeme l;
  
  write_s_file(series, len);

  lex_open(s_file);
  for (i=1; i < 10; i++) {
    l = lex_get();
    TEST_ASSERT_EQUAL_INT(i, l.value);
    lex_advance();
  }
}

void test_punct(){
  int len = 9;
  const char *series[] = {";", "(", ")", ",", "/", "<", "-", "%", "~"};

  write_s_file(series, len);

  write_o_file();

  check_diff(series, len, o_fd);
}

/* 
 * the lexer should be able to capture punctuation marks that are 
 * comprised of two characters
 */
void test_multi_punct(){
  int len = 9;
  const char *series[] = {";", "/=", "(", ">", ")", ">=", "<=", "-", "/"};
  
  write_s_file(series, len);

  write_o_file();

  check_diff(series, len, o_fd);

}

/* 
 * the leer should ignore the comment lines, which start with -- 
 * and write only the other character strings in to o_file
 */
void test_comment(){
  int len = 6;
  const char *series[] = {"-- t", 
                          "-- a",
                          "(",
                          "=",
                          "-- b",
                          "-"};
  const char *expected[] = {"(",
                          "=",
                          "-"};                          

  write_s_file(series, len);

  write_o_file();

  len = 3;
  check_diff(expected, len, o_fd);
}

int main(int argc, const char * argv[]) {
  UNITY_BEGIN();
    RUN_TEST(test_lex_open);
    RUN_TEST(test_line_number);
    RUN_TEST(test_string);
    RUN_TEST(test_numeric);
    RUN_TEST(test_punct);
    RUN_TEST(test_multi_punct);
    RUN_TEST(test_comment);
  return UNITY_END();
}
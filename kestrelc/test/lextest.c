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

static FILE *fd;
static const char *test_file = "test.kl";

/* helper function to write contents of the test file */
void test_write(const char *buf){
  size_t len = strlen(buf);

  if ((fd = fopen(test_file, "w")) == NULL){
    perror(test_file);
    exit(EXIT_FAILURE);
  }

  if (fwrite(buf, sizeof(char), len, fd) != len) {
    fclose(fd);
    perror(test_file);
    exit(EXIT_FAILURE);
  }

  fclose(fd);
}

void setUp(void){
  /* 
  * check if the file exists. 
  * there could be a better way of doing this in a portable way 
  */
  if ((fd = fopen(test_file, "r")) != NULL) {
    fclose(fd);
    remove(test_file);
  }

  if ((fd = fopen(test_file, "w")) == NULL){
    perror(test_file);
    exit(EXIT_FAILURE);
  }

  fclose(fd);
}

void tearDown(void){
  if (remove(test_file) != 0) {
    perror(test_file);
    exit(EXIT_FAILURE);
  }
}

/* 
 * lex_open should sucessfuly read the first char and then call
 * lex_advance(), hence after calling lex_open(), ch should have
 * the value of the second char in the buf
 */
void test_lex_open(void) {
  const char *buf = "putstr( \"Hello world\"+LF, output )";
  test_write(buf);

  lex_open(test_file);
  TEST_ASSERT_EQUAL_CHAR(*(buf+1), get_lex_ch());

  fclose(fd);
}

/* 
 * the lexer should ignore white spaces and only store the numeric 
 * values in lex_next.value
 */
void test_numeric(){
  int i;
  const char *buf = "1 2 3 4 5 6 7 8 9";
  test_write(buf);

  lex_open(test_file);
  for (i=1; i < 10; i++) {
    TEST_ASSERT_EQUAL_INT(i, lex_next.value);
    lex_advance();
  }
  
  fclose(fd);
}

/* 
 * the lexer should ignore white spaces and only store the punctuation 
 * characters in lex_next.value
 */
void test_punctuation(){
  int i;
  const char *buf = "; ( ) , / < - % ~";
  test_write(buf);

  const char *another_file="another.txt";
  FILE *another;
  if ((another = fopen(another_file,"w+"))==NULL){
    TEST_FAIL_MESSAGE(strerror(errno));
  }

  /* write output of the lexer to a file */
  lex_open(test_file);
  do {
    lex_put(&lex_this, another);
    lex_advance();
  } while (lex_this.type != ENDFILE);

  rewind(another); /* go back to begining of the file */
  
  for (i=0; i < strlen(buf); i+=2) {
    TEST_ASSERT_EQUAL_CHAR(*(buf+i), fgetc(another));
    lex_advance();
  }
  
  fclose(another);
  fclose(fd);

  remove(another_file);
}

int main(int argc, const char * argv[]) {
  UNITY_BEGIN();
    RUN_TEST(test_lex_open);
    RUN_TEST(test_numeric);
    RUN_TEST(test_punctuation);
  return UNITY_END();
}
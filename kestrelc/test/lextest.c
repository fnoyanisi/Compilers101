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

static FILE *s_fd;
static FILE *o_fd;
static const char *s_file = "test.kl";
static const char *o_file = "output.txt";

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
}

void tearDown(void){
  fclose(s_fd);
  fclose(o_fd);

  // if (remove(s_file) != 0) {
  //   perror(s_file);
  //   exit(EXIT_FAILURE);
  // }

  // if (remove(o_file) != 0) {
  //   perror(o_file);
  //   exit(EXIT_FAILURE);
  // }
}

/* 
 * lex_open should sucessfuly read the first char and then call
 * lex_advance(), hence after calling lex_open(), ch should have
 * the value of the second char in the buf
 */
void test_lex_open(void) {
  const char *buf[] = {"putstr( \"Hello world\"+LF, output )"};
  
  write_s_file(buf,1);

  lex_open(s_file);
  TEST_ASSERT_EQUAL_CHAR(buf[0][1], get_lex_ch());
}

/* 
 * the lexer should ignore white spaces and only store the numeric 
 * values in lex_next.value
 */
void test_numeric(){
  int i, len = 9;
  const char *series[]= {"1","2","3","4","5","6","7","8","9"};
  
  write_s_file(series, len);

  lex_open(s_file);
  for (i=1; i < 10; i++) {
    TEST_ASSERT_EQUAL_INT(i, lex_next.value);
    lex_advance();
  }
}

/* 
 * the lexer should ignore white spaces and only store the punctuation 
 * characters in lex_next.value
 */
void test_punct(){
  int i, len = 9, buflen = 32;
  char buf[buflen];
  const char *series[] = {";", "(", ")", ",", "/", "<", "-", "%", "~"};

  write_s_file(series, len);

  /* read the source and write the output to "output.txt" */
  lex_open(s_file);
  do {
    if (lex_this.type != NONE){
      lex_put(&lex_this, o_fd);
      fputs("\n",o_fd);
    }
    lex_advance();
  } while (lex_this.type != ENDFILE);

  rewind(o_fd); /* go back to begining of the file */
  
  for (i=0; i < len; i++) {
    if (fgets(buf, buflen, o_fd) == NULL){
      perror(o_file);
      exit(EXIT_FAILURE);
    }
    TEST_ASSERT_EQUAL_STRING_LEN(series[i], buf,1);
    lex_advance();
  }
}

/* 
 * the lexer should ignore white spaces and only store the punctuation 
 * characters in lex_next.value.
 */
void test_multi_punct(){
  int i, slen, len = 7, buflen = 32;
  char buf[buflen]; /* buffer to store the text read from the file */
  const char *series[] = {";", "\\=", "(", ")", ">=", "<=", "-"};
  
  write_s_file(series, len);

  /* write output of the lexer to a file */
  lex_open(s_file);
  do {
    if (lex_this.type != NONE) {
      lex_put(&lex_this, o_fd);
      fputs("\n",o_fd);
    }
    lex_advance();
  } while (lex_this.type != ENDFILE);

  rewind(o_fd); /* go back to begining of the file */
  
  for (i=0; i < len; i++) {
    slen = strlen(series[i]);
    if (fgets(buf, buflen, o_fd) == NULL){
      perror(o_file);
      exit(EXIT_FAILURE);
    }
    printf("series[i] =\t%s  buf =\t%s slen =\t%d\n", series[i], buf, slen);
    //TEST_ASSERT_EQUAL_STRING_LEN(series[i], buf, slen);
    lex_advance();
  }
}

int main(int argc, const char * argv[]) {
  UNITY_BEGIN();
    // RUN_TEST(test_lex_open);
    // RUN_TEST(test_numeric);
    // RUN_TEST(test_punct);
    RUN_TEST(test_multi_punct);
  return UNITY_END();
}
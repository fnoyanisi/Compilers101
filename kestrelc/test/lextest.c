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
#include <unity.h>
#include <lexical.h>

static FILE *fd;
static const char *test_file = "test.kl";
static const char *buf = "putstr( \"Hello world\"+LF, output )";

void setUp(void){
  size_t len = strlen(buf);

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
    exit(1);
  }

  if (fwrite(buf, sizeof(char), len, fd) != len) {
    fclose(fd);
    perror(test_file);
    exit(1);
  }

  fclose(fd);
}

void tearDown(void){
  if (remove(test_file) != 0) {
    perror(test_file);
    exit(1);
  }
}

void test_lex_open(void) {
  lex_open(test_file);
  TEST_ASSERT_EQUAL_CHAR(*buf, get_lex_ch());
}

void test_lex_advance(){
  lex_open("test.kl");
  FILE *f = fopen("unit.kl","w");
  do {
    lex_put(&lex_this, f);
    putchar('\n');
    lex_advance();
  } while (lex_this.type == ENDFILE);
  fclose(f);
}

int main(int argc, const char * argv[]) {
  UNITY_BEGIN();
    RUN_TEST(test_lex_open);
    RUN_TEST(test_lex_advance);
  return UNITY_END();
}
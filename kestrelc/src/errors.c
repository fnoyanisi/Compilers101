/*-
 * errors.c
 * 
 * This implementation is following the theory in the Compiler Construction
 * course given by Douglas W.Jones from The University of Iowa Department of 
 * Computer Science
 * http://homepage.divms.uiowa.edu/~jones/compiler/
 * 
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
#include "errors.h"
#include "lexical.h"

static const char *message[] = {
    /* ER_BADFILE */    "Cannot open input file",
    /* ER_TOOBIG */     "Value too large",
    /* ER_POOLOVF */    "String pool buffer overflow",
    /* ER_TOOLONG */    "String is too long",
    /* ER_SYMTAB */     "Symbol error",
    /* ER_BADSTR */     "Bad string"
};

void error_fatal(error_message er, int line){
    fprintf(stderr, "Fatal error in line %d: %s\n", line, message[er]);
    exit(EXIT_FAILURE);
}

void error_warn(error_message er, int line){
    fprintf(stderr, "Error on line %d: %s\n", line, message[er]);
}

void error_unexpected(lexeme got, lexeme exp, int line) {
    fprintf(stderr, "Error on line %d: Expecting lex_type %s but got %s\n", 
        line,lex_name[exp.type], lex_name[got.type]);
}
/*-
 * lexical.c
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
#include <string.h>
#include "kestrelc.h"
#include "lexical.h"

static char ch;         /* current char not yet part of a lexeme */
static FILE *infile;    /* the input file */

/* helper function to get the state of the lexer */
char get_lex_ch(void){
    return ch;
}

void lex_open(const char *f) {
    if (f == NULL) {
         /* for the ability to pipe the source from stdin */
        infile = stdin;
    } else if ((infile = fopen(f,"r")) == NULL) {
        exit_error(f);
    } 

    if ((ch = fgetc(infile)) == EOF && ferror(infile)) {
        exit_error(f);
    }
}

void lex_advance() {
    lex_this = lex_next;

    /* skip whitespace */
    while(ISCLASS(ch, WHITESPACE)) {
        if ((ch = fgetc(infile)) == EOF && ferror(infile)) {
            if (ferror(infile)) {
                exit_error(NULL);
            }
        }
    }

    /* =BUG= how do we handle comments? */

    /* decimal digit */
    if ((ch >= '0') && (ch <= '9')) {
        lex_next.type = NUMBER;
        lex_next.value = 0;

        /* accumulate value of the digit */
        do {
            lex_next.value = (lex_next.value * 10) + (ch - '0');
            /* =BUG= what if there is an overflow? */
            ch = fgetc(infile);
        } while ((ch >= '0') && (ch <= '9'));
        /* =BUG= what if a # leads into an odd number base? */
    } else {
         printf("none\n");
    }
}

void lex_put(lexeme *l, FILE *f) {

}
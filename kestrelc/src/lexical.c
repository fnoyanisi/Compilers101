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
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include "kestrelc.h"
#include "lexical.h"
#include "errors.h"

static char ch;         /* current char not yet part of a lexeme */
static FILE *infile;    /* the input file */
static int in_comment;
static int in_string;
static int line_number;

/* helper function to get the state of the lexer */
char get_lex_ch(void){
    return ch;
}

void lex_open(const char *f) {
    if (f == NULL) {
         /* for the ability to pipe the source from stdin */
        infile = stdin;
    } else if ((infile = fopen(f,"r")) == NULL) {
        perror(f);
        exit(EXIT_FAILURE);
    } 

    if ((ch = fgetc(infile)) == EOF && ferror(infile)) {
        perror(f);
        exit(EXIT_FAILURE);
    }

    in_comment = 0;
    in_string = 0;
    line_number = 0;
}

void lex_advance() {
    lex_this = lex_next;

    /* skip whitespace */
    while(ISCLASS(ch, WHITESPACE)) {
        if ((ch = fgetc(infile)) == EOF) {
            if (ferror(infile)) {
                perror(NULL);
                exit(EXIT_FAILURE);
            }
        }
    }

    /* =BUG= how do we handle comments? */

    /* handle comments */
    if (lex_this.type == PUNC && lex_this.value == PT_MINUS && ch == '-')
        in_comment = 1;
    while(ch != '\n' && in_comment) {
        if ((ch = fgetc(infile)) == EOF) {
            if (ferror(infile)) {
                perror(NULL);
                exit(EXIT_FAILURE);
            }
        }
    }
    in_comment = 0;

    /* decimal digit */
    if ((ch >= '0') && (ch <= '9')) {
        lex_next.type = NUMBER;
        lex_next.value = 0;
        
        do {
            /* check for overflow */
            if (lex_next.value > ((UINT32_MAX - (ch - '0')) / 10)){
                error_warn(ER_TOOBIG, line_number);
            } else {
            /* accumulate value of the digit */
                lex_next.value = (lex_next.value * 10) + (ch - '0');
            }
            ch = fgetc(infile);
        } while ((ch >= '0') && (ch <= '9'));
        /* =BUG= what if a # leads into an odd number base? */
    /* punctuation */
    } else if (ISCLASS(ch, PUNCTUATION)) { 
        lex_next.type = PUNC;

        if (lex_this.type == PUNC && lex_this.value == PT_DIV && ch == '=')
            lex_this.value = PT_NOTEQL; /* /= */
        else if (lex_this.type == PUNC && lex_this.value == PT_GT && ch == '=')
            lex_this.value = PT_GE;     /* >= */
        else if (lex_this.type == PUNC && lex_this.value == PT_LT && ch == '=')
            lex_this.value = PT_LE;     /* <= */
        else       
            lex_next.value = punc_class[ch];

        if ((ch = fgetc(infile)) == EOF) {
            if (ferror(infile)) {
                fclose(infile);
                perror(NULL);
                exit(EXIT_FAILURE);
            } else {
                /* end of file */
                return;
            }
        }
    /* strings */
    } else if (ch == '\'' || ch == '\"'){
         printf("none\n");
    }
}

void lex_put(lexeme *l, FILE *f) {

}
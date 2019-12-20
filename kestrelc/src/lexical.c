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
#include <inttypes.h>
#include "kestrelc.h"
#include "lexical.h"
#include "errors.h"

static int ch;          /* current char not yet part of a lexeme */
static FILE *infile;    /* the input file */
static int in_comment;
static int in_string;
static int line_number;

static const char *punc_name[]= {
    /* PT_SEMI   */ ";",  /* PT_EQUALS */ "=",  /* PT_COLON  */  ":",
    /* PT_LPAREN */ "(",  /* PT_LBRAKT */ "[",  /* PT_LBRACE */  "{",
    /* PT_RPAREN */ ")",  /* PT_RBRAKT */ "]",  /* PT_RBRACE */  "}",
    /* PT_COMMA  */ ",",  /* PT_ATSIGN */ "@",  /* PT_ELIPS  */  "..",
    /* PT_NOTEQL */ "/=", /* PT_GT     */ ">",  /* PT_GE     */  ">=",
    /* PT_LT     */ "<",  /* PT_LE     */ "<=", /* PT_PLUS   */  "+",
    /* PT_MINUS  */ "-",  /* PT_TIMES  */ "*",  /* PT_DIV    */  "/",
    /* PT_MOD    */ "%",  /* PT_AND    */ "&",  /* PT_OR     */  "|",
    /* PT_NOT    */ "~",  /* PT_DOT    */ ".",  /* PT_NONE   */  "?WHAT?"
};

/* helper function */
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

    ch = fgetc(infile);
    in_comment = 0;
    in_string = 0;
    line_number = 1;

    lex_this.type = NONE;
    lex_this.value = 0;

    lex_advance();
}

void lex_advance() {
    char next_ch;
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

    /* handle comments */
    /* =BUG= */
    // if(ch == '-') {
    //     if ((ch = getc(infile)) == '-'){
    //         do {
    //             ch = getc(infile);
    //         }  while(ch != '\n' && ch != EOF);
    //         ch = getc(infile);
    //         return;
    //     } else {
    //         ungetc(ch, infile);
    //     }
    // }

    if (ch == EOF) {
        /* end of file */ 
        lex_next.type = ENDFILE;
        lex_next.value = 0;
    } else if ((ch >= '0') && (ch <= '9')) {
        /* decimal digit */
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
    } else if (ISCLASS(ch, PUNCTUATION)) { 
        /* punctuation */
        lex_next.type = PUNCT;
        lex_next.value = punc_class[ch];

        /* multi-char punctuation */
        if (ch == '/' || ch == '>' || ch == '<') {
            if ((next_ch = getc(infile)) == '=') {
                switch (ch) {
                case '/':
                    lex_next.value = PT_NOTEQL;
                    break;
                case '<':
                    lex_next.value = PT_LE;
                    break;
                case '>':
                    lex_next.value = PT_GE;
                    break;
                default:
                    ungetc(next_ch, infile);
                }
            } 
        }

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
    } else if (ch == '\'' || ch == '\"'){
        /* strings */
        printf("none\n");
    } else {
        /* other */

        /* no lexeme assignments, just skip */

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
    }
}

void lex_put(lexeme *lex, FILE *f) {
    /* reconstruct and output lex to file f */
    switch (lex->type) {
        case IDENT:
        case KEYWORD:
        /* =BUG= missing code for these lexeme types */
            break;
        case NUMBER:
            fprintf(f, "%" PRId32, lex->value);
            break;
        case PUNCT:
            fputs(punc_name[lex->value],f);
            break;
        case STRING:
        case ENDFILE:
        case NONE:
        /* =BUG= missing code for these lexeme types */
            break;
    }
}
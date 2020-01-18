/*-
 * lexical.c
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
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>
#include "kestrelc.h"
#include "lexical.h"
#include "lexsupport.h"

static int ch;          /* current char not yet part of a lexeme */
static FILE *infile;    /* the input file */
static unsigned int line_number;
static unsigned int pos = 0;

/* to keep track of the position in the line */
#define lex_getc(ch)            (pos++, getc(ch))
#define lex_ungetc(ch, file)    (pos--, ungetc(ch, file))

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

/* helper function that returns lex_next */
lexeme lex_get(void){
    return lex_next;
}

void lex_open(const char *f) {
    if (f == NULL) {
         /* for the ability to pipe the source from stdin */
        infile = stdin;
    } else if ((infile = fopen(f,"r")) == NULL) {
        perror(f);
        exit(EXIT_FAILURE);
    } 

    line_number = 1;
    ch = lex_getc(infile);

    lex_this.type = NONE;
    lex_this.value = 0;
    lex_this.line = line_number;
    lex_this.pos = 0;

    lex_advance();
}

void lex_advance() {
    char next_ch;
    lex_this = lex_next;

    /* skip whitespace */
    while(ISCLASS(ch, WHITESPACE)) {
        if (ch == '\n') /* CR */
            line_number++;

        if ((ch = lex_getc(infile)) == EOF) {
            if (ferror(infile)) {
                perror(NULL);
                exit(EXIT_FAILURE);
            }
        }
    }

    /* handle comments */
    while(ch == '-') {
        if ((next_ch = lex_getc(infile)) == '-'){
            do {
                ch = lex_getc(infile);
                pos++;
            }  while(ch != '\n');
            line_number++;
            ch = getc(infile);
        } else {
            lex_ungetc(next_ch, infile);
            break;
        }
    }

    if (ch == EOF) {
        /* end of file */ 
        lex_next.type = ENDFILE;
        lex_next.value = 0;
        lex_next.pos = pos;
        lex_next.line = line_number;
    } else if ((ch >= '0') && (ch <= '9')) {
        /* decimal digit */
        lex_next.type = NUMBER;
        lex_next.value = 0;
        lex_next.pos = pos;
        lex_next.line = line_number;
        do {
            /* check for overflow */
            if (lex_next.value > ((UINT32_MAX - (ch - '0')) / 10)){
                error_warn(ER_TOOBIG, line_number);
            } else {
            /* accumulate value of the digit */
                lex_next.value = (lex_next.value * 10) + (ch - '0');
            }
            ch = lex_getc(infile);
        } while ((ch >= '0') && (ch <= '9'));
        /* =BUG= what if a # leads into an odd number base? */
    } else if (ISCLASS(ch, PUNCTUATION)) { 

        /* punctuation */
        lex_next.type = PUNCT;
        lex_next.value = punc_class[ch];
        lex_next.pos = pos;
        lex_next.line = line_number;

        /* multi-char punctuation */
        if (ch == '/' || ch == '>' || ch == '<') {
            if ((next_ch = lex_getc(infile)) == '=') {
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
                    lex_ungetc(next_ch, infile);
                }
            } 
        }

        if ((ch = lex_getc(infile)) == EOF) {
            if (ferror(infile)) {
                fclose(infile);
                perror(NULL);
                exit(EXIT_FAILURE);
            } else {
                /* end of file */
                return;
            }
        }
    } else if (ISCLASS(ch, LETTER)) { 
        /* identifier */
        symbol_start(line_number);
        lex_next.type = IDENT;
        lex_next.pos = pos;
        lex_next.line = line_number;

        do {
            symbol_append(ch);
            ch = lex_getc(infile);
        } while (ch != EOF && ISCLASS(ch, LETTER | NUMBER));
        lex_next.value = symbol_lookup();
        
    } else if (ch == '\'' || ch == '"'){
        /* string */
        char quote = ch; /* remember which quote mark to use */

        symbol_start(line_number);
        ch = lex_getc(infile);

        while (ch != EOF && ch != '\n' && ch != quote){
            symbol_append(ch);
            ch = lex_getc(infile);
        }

        if (ch == quote){
            lex_next.type = STRING;
            lex_next.value = symbol_lookup();
            lex_next.pos = pos;
            lex_next.line = line_number;
            ch = lex_getc(infile);
        } else { 
            error_warn(ER_BADSTR, line_number);
        }

    } else {
        /* other */

        /* no lexeme assignments, just skip */

        if ((ch = lex_getc(infile)) == EOF) {
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
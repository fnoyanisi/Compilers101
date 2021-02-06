/*-
 * lexical.cpp
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

#include <iostream>
#include <fstream>
#include <cerrno>
#include <string>

#include "errors.hpp"
#include "kestrelc.hpp"
#include "lexical.hpp"
#include "lexsupport.hpp"

/* to keep track of the position in the line */
#define lex_getc(lxr, file)          (lxr->posinc(), file.get())
#define lex_ungetc(lxr, file)        (lxr->posdec(), file.unget())

/* this has to be in the same order as lex_types */
const char *lex_name[]= {
    /* NONE     */  "NONE",
    /* IDENT    */  "IDENT", 
    /* KEYWORD  */  "KEYWORD", 
    /* NUMBER   */  "NUMBER", 
    /* STRING   */  "STRING", 
    /* PUNCT    */  "PUNCT", 
    /* ENDFILE  */  "ENDFILE"
}; 

const char *punc_name[]= {
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
lexeme 
lexer::lex_get(void) const {
    return lex_next;
}

lexer::lexer(std::string f) {
    pos_ = 0;
    line_number_ = 1;

    infile.open(f);
    if (infile.is_open() == false) {
        std::cerr << "Error: " << strerror(errno);
        exit(EXIT_FAILURE);
    } 

    ch = lex_getc(this, infile);

    lex_this.type(NONE);
    lex_this.value(0);
    lex_this.line(line_number_);
    lex_this.pos(pos_);

    lex_advance();
}

void 
lexer::lex_advance() {
    key_handle key;
    char next_ch;
    lex_this = lex_next;

    /* skip whitespace */
    while(ch != std::char_traits<char>::eof() && ISCLASS(ch, WHITESPACE)) {
        if (ch == '\n') {
            line_number_++;
            pos_ = 1;
        }

        ch = lex_getc(this, infile);
    }

    /* handle comments */
    while(ch == '-') {
        if ((next_ch = lex_getc(this, infile)) == '-'){
            do {
                ch = lex_getc(this, infile);
                pos_++;
            }  while(ch != '\n');
            line_number_++;
            pos_ = 1;
            ch = infile.get();
        } else {
            lex_ungetc(this, infile);
            break;
        }
    }

    if (ch == std::char_traits<char>::eof()) {
        /* end of file */ 
        lex_next.type(ENDFILE);
        lex_next.value(0);
        lex_next.pos(pos_);
        lex_next.line(line_number_);
    } else if ((ch >= '0') && (ch <= '9')) {
        /* decimal digit */
        lex_next.type(NUMBER);
        lex_next.value(0);
        lex_next.pos(pos_);
        lex_next.line(line_number_);
        do {
            /* check for overflow */
            if (lex_next.value() > ((UINT32_MAX - (ch - '0')) / 10)){
                error_warn(error_message::ER_TOOBIG, line_number_);
            } else {
            /* accumulate value of the digit */
                lex_next.value((lex_next.value() * 10) + (ch - '0'));
            }
            ch = lex_getc(this, infile);
        } while ((ch >= '0') && (ch <= '9'));
        /* =BUG= what if a # leads into an odd number base? */
    } else if (ISCLASS(ch, PUNCTUATION)) { 

        /* punctuation */
        lex_next.type(PUNCT);
        lex_next.value(punc_class[ch]);
        lex_next.pos(pos_);
        lex_next.line(line_number_);

        /* multi-char punctuation */
        if (ch == '/' || ch == '>' || ch == '<') {
            if ((next_ch = lex_getc(this, infile)) == '=') {
                switch (ch) {
                case '/':
                    lex_next.value(PT_NOTEQL);
                    break;
                case '<':
                    lex_next.value(PT_LE);
                    break;
                case '>':
                    lex_next.value(PT_GE);
                    break;
                default:
                    lex_ungetc(this, infile);
                }
            } 
        }

        ch = lex_getc(this, infile);
        if (infile.eof()) {
            return;
        }
    } else if (ISCLASS(ch, LETTER)) { 
        /* identifier */
        symbol_start(line_number_);
        lex_next.type(IDENT);
        lex_next.pos(pos_);
        lex_next.line(line_number_);

        do {
            symbol_append(ch);
            ch = lex_getc(this, infile);
        } while (ch != EOF && ISCLASS(ch, LETTER | NUMBER));
        lex_next.value(symbol_lookup());

        key = key_lookup(lex_next.value());

    } else if (ch == '\'' || ch == '"'){
        /* string */
        char quote = ch; /* remember which quote mark to use */

        symbol_start(line_number_);
        ch = lex_getc(this, infile);

        while (ch != EOF && ch != '\n' && ch != quote){
            symbol_append(ch);
            ch = lex_getc(this, infile);
        }

        if (ch == quote){
            lex_next.type(STRING);
            lex_next.value(symbol_lookup());
            lex_next.pos(pos_);
            lex_next.line(line_number_);
            ch = lex_getc(this, infile);
        } else { 
            error_warn(error_message::ER_BADSTR, line_number_);
        }

    } else {
        /* other */

        /* no lexeme assignments, just skip */

        ch = lex_getc(this, infile);
        if (infile.eof()){
            if (infile.fail()) {
                infile.close();
                std::cerr << "Error: " << strerror(errno);
                exit(EXIT_FAILURE);
            } else {
                /* end of file */
                return;
            }
        }
    }
}

void 
lexer::lex_put(std::ofstream& f) const {
    /* reconstruct and output lex to file f */
    switch (lex_next.type()) {
        case IDENT:
        case KEYWORD:
        /* =BUG= missing code for these lexeme types */
            break;
        case NUMBER:
            f << lex_next.value();
            break;
        case PUNCT:
            f << punc_name[lex_next.value()];
            break;
        case STRING:
        case ENDFILE:
        case NONE:
        /* =BUG= missing code for these lexeme types */
            break;
    }
}

unsigned
lexer::line_number() const {
    return line_number_;
}

unsigned
lexer::pos() const {
    return pos_;
}

void
lexer::posinc() {
    pos_++;
}

void
lexer::posdec() {
    pos_--;
}
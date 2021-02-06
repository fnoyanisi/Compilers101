/*-
 * lexical.hpp
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

#ifndef _LEXICAL_H_
#define _LEXICAL_H_

#include <iostream>
#include <fstream>
#include "stringpool.hpp"
#include "symboltable.hpp"
#include "keywords.hpp"

extern unsigned line_number;

/******************************************************************************
 * character identification
 *****************************************************************************/
enum char_type {
    OTHER=0, WHITESPACE=1, LETTER=2, DIGIT=4, PUNCTUATION=8
};

#define OTH OTHER
#define WIT WHITESPACE
#define LET LETTER
#define DIG DIGIT
#define PUN PUNCTUATION
static const char_type char_class[256] = {
  /*NUL SOH STX ETX EOT ENQ ACK BEL BS  HT  LF  VT  FF  CR  SO  SI */ 
    OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,WIT,WIT,WIT,WIT,WIT,OTH,OTH,
  /*DLE DC1 DC2 DC3 DC4 NAK SYN ETB CAN EM  SUB ESC FS  GS  RS  US */ 
    OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
  /*     !   "   #   $   %   &   '   (   )   *   +   ,   -   .   / */ 
    WIT,OTH,OTH,OTH,OTH,PUN,PUN,OTH,PUN,PUN,PUN,PUN,PUN,PUN,PUN,PUN,
  /* 0   1   2   3   4   5   6   7   8   9   :   ;   <   =   >   ? */ 
    DIG,DIG,DIG,DIG,DIG,DIG,DIG,DIG,DIG,DIG,PUN,PUN,PUN,PUN,PUN,OTH,
  /* @   A   B   C   D   E   F   G   H   I   J   K   L   M   N   O */ 
    PUN,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,
  /* P   Q   R   S   T   U   V   W   X   Y   Z   [   \   ]   ^   _ */ 
    LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,PUN,OTH,PUN,OTH,OTH,
  /* `   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o */ 
    OTH,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,
  /* p   q   r   s   t   u   v   w   x   y   z   {   |   }   ~  DEL*/ 
    LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,PUN,PUN,PUN,PUN,OTH,
  /* beyond ASCII */
    OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH, 
    OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH, 
    OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH, 
    OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH, 
    OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH, 
    OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH, 
    OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH, 
    OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH
};
#undef OTH
#undef WIT
#undef LET
#undef DIG
#undef PUN

#define ISCLASS(ch,class) (char_class[ch]&(class))

/******************************************************************************
 * punctuation character type
 *****************************************************************************/
enum punc_type {
    PT_SEMI     /* ; */,    PT_EQUALS   /* = */,    PT_COLON    /* : */,
    PT_LPAREN   /* ( */,    PT_LBRAKT   /* [ */,    PT_LBRACE   /* { */,
    PT_RPAREN   /* ) */,    PT_RBRAKT   /* ] */,    PT_RBRACE   /* } */,
    PT_COMMA    /* , */,    PT_ATSIGN   /* @ */,    PT_ELIPS    /* .. */,
    PT_NOTEQL   /* /= */,   PT_GT       /* > */,    PT_GE       /* >= */,
    PT_LT       /* < */,    PT_LE       /* <= */,   PT_PLUS     /* + */,
    PT_MINUS    /* - */,    PT_TIMES    /* * */,    PT_DIV      /* / */,
    PT_MOD      /* % */,    PT_AND      /* & */,    PT_OR       /* | */,
    PT_NOT      /* ~ */,    PT_DOT      /* . */,    PT_NONE
};
extern const char *punc_name[];

#define SMI PT_SEMI
#define EQU PT_EQUALS
#define COL PT_COLON
#define LPR PT_LPAREN
#define LBR PT_LBRAKT
#define LBC PT_LBRACE
#define RPR PT_RPAREN
#define RBR PT_RBRAKT
#define RBC PT_RBRACE
#define COM PT_COMMA
#define ATS PT_ATSIGN
#define ELS PT_ELIPS
#define GT  PT_GT
#define LT  PT_LT
#define PLS PT_PLUS
#define MNS PT_MINUS
#define TMS PT_TIMES
#define DIV PT_DIV
#define MOD PT_MOD
#define AND PT_AND
#define OR  PT_OR
#define NOT PT_NOT
#define DOT PT_DOT
#define NON PT_NONE
static const punc_type punc_class[256] = {
  /*NUL SOH STX ETX EOT ENQ ACK BEL BS  HT  LF  VT  FF  CR  SO  SI */ 
    NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,
  /*DLE DC1 DC2 DC3 DC4 NAK SYN ETB CAN EM  SUB ESC FS  GS  RS  US */ 
    NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,
  /*     !   "   #   $   %   &   '   (   )   *   +   ,   -   .   / */ 
    NON,NON,NON,NON,NON,MOD,AND,NON,LPR,RPR,TMS,PLS,COM,MNS,DOT,DIV,
  /* 0   1   2   3   4   5   6   7   8   9   :   ;   <   =   >   ? */ 
    NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,COL,SMI,LT ,EQU,GT ,NON,
  /* @   A   B   C   D   E   F   G   H   I   J   K   L   M   N   O */ 
    ATS,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,
  /* P   Q   R   S   T   U   V   W   X   Y   Z   [   \   ]   ^   _ */ 
    NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,LBR,NON,RBR,NON,NON,
  /* `   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o */ 
    NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,
  /* p   q   r   s   t   u   v   w   x   y   z   {   |   }   ~  DEL*/ 
    NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,LBC,OR ,RBC,NOT,NON,
  /* beyond ASCII */
    NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON, 
    NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON, 
    NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON, 
    NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON, 
    NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON, 
    NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON, 
    NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON, 
    NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON,NON
};
#undef SMI
#undef EQU
#undef COL
#undef LPR
#undef LBR
#undef LBC
#undef RPR
#undef RBR
#undef RBC
#undef COM
#undef ATS
#undef ELS
#undef GT
#undef LT
#undef PLS
#undef MNS
#undef TMS
#undef DIV
#undef MOD
#undef AND
#undef OR
#undef NOT
#undef DOT
#undef NON

/******************************************************************************
 * lexeme related definitions 
 *****************************************************************************/
enum lex_type {NONE, IDENT, KEYWORD, NUMBER, STRING, PUNCT, ENDFILE};
extern const char *lex_name[];

class lexeme {
    private:
      lex_type type_;   
      uint32_t value_;
      unsigned line_;    /* line number of the lexeme */
      unsigned pos_;     /* zero-indexed start location within the line */
    public:
      // some code smell here
      // keep getters and setter for some future additions
      lex_type type() const { return type_; }
      void type(lex_type t) { type_ = std::move(t); }
      uint32_t value() const { return value_; }
      void value(uint32_t v) { value_ = std::move(v); }
      unsigned line() const { return line_; }
      void line(unsigned l) { line_ = std::move(l); }
      unsigned pos() const { return pos_; }
      void pos(unsigned p) {pos_ = std::move(p); }
};

/******************************************************************************
 * function declarations
 *****************************************************************************/

class lexer {
    private:
      lexeme lex_this;          // the current lexeme
      lexeme lex_next;          // the next lexeme
      std::ifstream infile;
      int ch;                   // current char not yet part of a lexeme
      unsigned pos_, line_number_;
    public:
      lexer(std::string);
      lexeme lex_get() const;
      void lex_advance();
      void lex_put(std::ofstream&) const;
      unsigned line_number() const;
      unsigned pos() const;
      void posinc();
      void posdec();
};

#endif
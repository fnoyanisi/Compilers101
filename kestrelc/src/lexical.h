/*-
 * lexical.h 
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

#include <stdint.h>
#include <stdio.h>

typedef enum {
    OTHER=0, WHITESPACE=1, LETTER=2, DIGIT=4, PUNCTUATION=8
} char_type;

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
    WIT,OTH,OTH,OTH,OTH,OTH,PUN,OTH,PUN,PUN,PUN,PUN,PUN,PUN,PUN,PUN,
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

typedef enum {IDENT, KEYWORD, NUMBER, STRING, PUNC, ENDFILE} lex_types;

typedef struct lexeme_t {
    lex_types type;
    uint32_t value;
} lexeme;

lexeme lex_this;    /* the current lexeme */
lexeme lex_next;    /* the next lexeme */

char get_lex_ch(void);
void lex_open(const char *f);
void lex_advance();
void lex_put(lexeme *l, FILE *f);
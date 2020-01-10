/*-
 * symboltable.h
 * 
 * This implementation is following the theory in the Compiler Construction
 * course given by Douglas W.Jones from The University of Iowa Department of 
 * Computer Science
 * http://homepage.divms.uiowa.edu/~jones/compiler/
 * 
 * Copyright (c) 2020 Fehmi Noyan Isi
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
#include <stdbool.h>
#include "stringpool.h"

/*
 * When the file is used from stringpool.c (but nowhere else)
 * the user nust first define EXTERN as nothing or blank
 */
#ifndef EXTERN
    #define EXTERN extern
#endif

#define SYMBOL_SIZE 2048
#define SYMBOL_HASH 31

/* an index within [0 ~ SYMBOL_SIZE-1] range to address the symbols */
typedef uint32_t symbol_handle;

/* maps symbol handles to string handles */
EXTERN string_handle _symbol_table[SYMBOL_SIZE];

/* the hash code of the symbol currently being accumulated */
EXTERN symbol_handle _symbol_hash;

/* the tentative string_handle for the symbol being accumulated */
EXTERN string_handle _symbol_string;

/* line number on which tge string is found */
EXTERN int _symbol_line;

/* Initialize the symbol table */
void symbol_init();

/*
 * setup to accumulate on string into the symbol table
 * the line parameter is given for error reporting
 * 
 * void symbol_start(int line);
 */
#define symbol_start(line) {                                    \
            _symbol_hash = 0;                                   \
            _symbol_string = string_start(line);                \
            _symbol_line = line;                                \
}

/*
 * append one character to the symbol currnetly being accumulated
 *
 * void symbol_append(char ch);
 */
#define symbol_append(ch) {                                     \
            _symbol_hash = ((_symbol_hash * SYMBOL_HASH)        \
                            + (ch)) % SYMBOL_SIZE;              \
            string_append(ch);                                  \
}

/*
 * output the symbol to a file
 * 
 * void symbol_put(symbol_handle s, FILE *f);
 */
#define symbol_put(s, f) { string_put(symbol_table[s], f); }

/* check whether a symbol has already been added into strin pool or not */
symbol_handle symbol_lookup();

#undef EXTERN
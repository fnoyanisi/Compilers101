/*-
 * symboltable.cpp
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

#include <stdlib.h>
#include "errors.hpp"
#include "stringpool.hpp"
#include "symboltable.hpp"

/* maps symbol handles to string handles */
string_handle _symbol_table[SYMBOL_SIZE];

/* the hash code of the symbol currently being accumulated */
symbol_handle _symbol_hash;

/* the tentative string_handle for the symbol being accumulated */
string_handle _symbol_string;

/* line number on which tge string is found */
int _symbol_line;

void 
symbol_init(){
    symbol_handle i;
    for (i = 0; i < SYMBOL_SIZE; i++)
        _symbol_table[i] = SYMBOL_INVALID;
}

symbol_handle 
symbol_lookup(){
    symbol_handle place = _symbol_hash;

    for (;;) {
        if (_symbol_table[place] == SYMBOL_INVALID) {
            /* add symbol to the table */
            _symbol_table[place] = _symbol_string;
            string_done();
            string_accept();
            return place;
        }
        if (string_eq(_symbol_table[place], _symbol_string)) {
            /* symbol is already in the table */
            string_done();
            string_reject();
            return place;
        }
        place++;
        if (place == SYMBOL_SIZE)
            place = 0;
        
        if (place == _symbol_hash)
            error_fatal(error_message::ER_SYMTAB, _symbol_line);
    }
}

/* caller has to free the buffer returned by symbol_get */
char *
symbol_get(symbol_handle hash){
    string_handle h = _symbol_table[hash];
    size_t len = (_string_pool[h+1] << 8) + _string_pool[h];
    char *p;
    int i;

    if ((p = (char*) malloc (len + 1)) != NULL) {
        for (i = 0; i<len; i++){
            p[i] = _string_pool[h+2+i];
        }
        p[len] = '\0';
    }
    return p;
}

symbol_handle 
symbol_add(const char *s){
    symbol_start(0);
    while (*s != '\0') {
        symbol_append(*s);
        s++;
    }
    return symbol_lookup();
}
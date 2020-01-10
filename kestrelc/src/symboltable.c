/*-
 * symboltable.c
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

#define EXTERN
#include "errors.h"
#include "stringpool.h"
#include "symboltable.h"

void symbol_init(){
    symbol_handle i;
    for (i = 0; i < SYMBOL_SIZE; i++)
        _symbol_table[i] = STRING_NUL;
}

symbol_handle symbol_lookup(){
    symbol_handle place = _symbol_hash;

    for (;;) {
        if (_symbol_table[place] == STRING_NUL) {
            /* add symbol to the table */
            _symbol_table[place] = _symbol_string;
            string_accept();
            return place;
        }
        if (string_eq(_symbol_table[place], _symbol_string)) {
            /* symbol is already in the table */
            string_reject();
            return place;
        }
        place++;
        if (place == SYMBOL_SIZE)
            place = 0;
        
        if (place == _symbol_hash)
            error_fatal(ER_SYMTAB, _symbol_line);
    }
}
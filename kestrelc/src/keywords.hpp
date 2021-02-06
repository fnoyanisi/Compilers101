/*-
 * keywords.hpp
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

#ifndef _KEYWORDS_H_
#define _KEYWORDS_H_

#include "stringpool.hpp"
#include "symboltable.hpp"

/* 
 * the best KEY_HASH_SIZE value is found by trialling several values and 
 * comparing the number of observed collisions. See Lecture 14, Predefined
 * Symbols and Keywords
 */
#define KEY_HASH_SIZE   89
#define KEY_MAX 21 

/* list of all the keywords in the language */
typedef enum {
        KEY_INVALID,
        KEY_END,        KEY_CONST,      KEY_FINAL,      KEY_TYPE,
        KEY_EXCEPTION,  KEY_VAR,        KEY_PROCEDURE,  KEY_FUNCTION,
        KEY_PRIVATE,    KEY_RESTRICTED, KEY_EXTERNAL,   KEY_ARRAY,
        KEY_SET,        KEY_OF,         KEY_RECORD,     KEY_IF,
        KEY_THEN,       KEY_ELSE,       KEY_SELECT,     KEY_CASE,
        KEY_WHILE,      KEY_DO,         KEY_UNTIL,      KEY_FOR,
        KEY_IN,         KEY_CATCH,      KEY_RAISE,      KEY_NULL
} key_handle;

/* data structure to hold key - symbol pairs */
typedef struct {
        key_handle key;
        symbol_handle sym;
} key_item;

/* initializer for the keyword interface */
void key_init();

/* outputs the indicated keyword ot a human readable file */
void key_put(key_handle, FILE*);

/* 
 * returns the corresponading key_handle for the symbol, KEY_INVALID 
 * if the requested symbol is not found, i.e. symbol is not a keyword
 */
key_handle key_lookup(symbol_handle);

#endif
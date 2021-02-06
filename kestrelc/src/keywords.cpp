/*-
 * keywords.cpp
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

#include <iostream>
#include <fstream>
#include "errors.hpp"
#include "keywords.hpp"
#include "symboltable.hpp"

/* 
 * list of all the keywords in the language, the order of the items has 
 * to be the same as the one found in key_handle
 */
static const char *key_names[] = {
        "????",
        "end",          "const",        "final",        "type",
        "exception",    "var",          "procedure",    "function",
        "private",      "restricted",   "external",     "array",
        "set",          "of",           "record",       "if",
        "then",         "else",         "select",       "case",
        "while",        "do",           "until",        "for",
        "in",           "catch",        "raise",        "null"
};

string_handle key_table[KEY_MAX + 1];

key_item key_hash[KEY_HASH_SIZE];

/* output the key to the human readable file */
void 
key_put(key_handle k, std::ofstream f) {
        f << key_names[k];
}

/* initializer for the lookup mechanism */
void 
key_init() {
        int i, hash;
        symbol_handle s;

        /* first, putthe default values in the table */
        for (i = 0; i < KEY_HASH_SIZE; i++) {
                key_hash[i].key = KEY_INVALID;
                key_hash[i].sym = SYMBOL_INVALID;
        }

        /* second, try to put hash keywords into table */
        for (i = KEY_INVALID+1; i <= KEY_NULL; i++) {
                s = symbol_add(key_names[i]);
                hash = s % KEY_HASH_SIZE;

                if (key_hash[hash].key == KEY_INVALID) {
                        key_hash[hash].key = (key_handle)i;
                        key_hash[hash].sym = s;
                } else {
                        error_fatal(error_message::ER_SYMCOL, 0);
                }
        }
}

/* 
 * returns the keyword handle corresposnding to the given symbol handle.
 * if the symbol handle is not a keyword, returns KEY_INVALID */
key_handle 
key_lookup(symbol_handle s) {
        int hash = s % KEY_HASH_SIZE;

        if (key_hash[hash].sym == s)
                return key_hash[hash].key;
        else
                return KEY_INVALID;
}
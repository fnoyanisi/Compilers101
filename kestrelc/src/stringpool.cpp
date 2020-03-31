/*-
 * stringpool.c
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
#include "stringpool.hpp"

/* an index within [0 ~ POOL_SIZE-1] range to address the strings */
typedef uint32_t string_handle;

/* main buffer to store all the text */
unsigned char _string_pool[POOL_SIZE];

/* index of the next free location */
string_handle _string_limit;

/* position to store new characters added to the _string_pool */
string_handle _string_pos;

/* the line number on which the string is starting */
unsigned int _string_line;

void 
string_put(string_handle h, std::ofstream f) {
    int limit = h + 2 + _string_pool[h] + (_string_pool[h+1] << 8);
    h = h + 2;
    while (h < limit) {
        f.put(_string_pool[h]);
        h++;
    }
}

bool 
string_eq(string_handle h1, string_handle h2) {
    int limit = h1 + 2 + _string_pool[h1] + (_string_pool[h1+1] << 8);

    /* if the length of the strings differ, return false */
    if (limit != (h2 + 2 + _string_pool[h2] + (_string_pool[h2+1] << 8)))
        return false;

    while (h1 < limit) {
        if (_string_pool[h1] != _string_pool[h2])
            return false;
        h1++;
        h2++;
    }
    return true;
}
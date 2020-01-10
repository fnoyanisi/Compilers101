/*-
 * stringpool.h
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
#include <stdbool.h>

/*
 * When the file is used from stringpool.c (but nowhere else)
 * the user nust first define EXTERN as nothing or blank
 */
#ifndef EXTERN
    #define EXTERN extern
#endif

#define POOL_SIZE   2048
#define STRING_NUL  0

/* an index within [0 POOL_SIZE-1] range to address the strings */
typedef uint32_t string_handle;

/* main buffer to store all the text */
EXTERN unsigned char _string_pool[POOL_SIZE];

/* index of the next free location */
EXTERN string_handle _string_limit;

/* position to store new characters added to the _string_pool */
EXTERN string_handle _string_pos;

/* the line number on which the string is starting */
EXTERN string_handle _string_line;


/*
 *    <-------------------- POOL_SIZE ---------------------> 
 *  |                                                       |
 *  | OTHER STRINGS STORED IN THE BUFFER | <---- FREE ----> |
 *  |                                    ^  ^               |
 *                                       p1  p2
 * 
 *  - p1 is _string_limit, showing the starting location of the 
 * free location
 * 
 * - p2 is _string_pos, which is 2 bytes (to store the lenght of 
 * the string) + [number of characters added with string_append()
 * so far] bytes further from _string_limit  
 */

/* 
 * initializer for the string pool
 * 
 * void string_init();
 */
#define string_init() { _string_limit = 1; }

/* 
 * set up to accumulate a new string and return its handle 
 * the line parameter is for error reporting
 * 
 * 2 bytes reserved to store the lenght of the string
 * 
 * string_handle string_start(int line);
 */
#define string_start(line) (                                \
            _string_line = line,                            \
            _string_pos = _string_limit + 2,                \
            _string_limit                                   \
)

/* 
 * append a char to the current string 
 * 
 * void string_append(char ch);
 */
#define string_append(ch) {                                 \
            if (_string_pos > (POOL_SIZE - 1)) {            \
                error_fatal(ER_POOLOVF, _string_line);      \
            }                                               \
            _string_pool[_string_pos] = ch;                 \
            _string_pos++;                                  \
}

/* 
 * mark the end of the string 
 * 
 * void string_done();
 */
#define string_done(ch) {                                   \
            int length = _string_pos - (_string_limit + 2); \
            if (length > 65535) {                           \
                error_warn(ERR_TOOLONG, _string_line);      \
                length = 65535;                             \
            }                                               \
            _string_pool[_string_limit] = length & 0xFF;    \
            _string_pool[_string_limit+1] = length >> 8;    \
}

/* 
 * accept the new string as a permament part of the pool 
 * 
 * void string_accept();
 */
#define string_accept() { _tring_limit = _string_pos; }

/* 
 * reject the new string, it will not be added to the pool 
 * 
 * void string_reject();
 */
#define string_reject() { (void); }

/* outputs the text of the string to FILE */
void string_put(string_handle h, FILE *f);

/* compare two strings */
bool string_eq(string_handle h1, string_handle h2);

#undef EXTERN
/*-
 * errors.h
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

#ifndef _ERRORS_H_
#define _ERRORS_H_

#include "lexical.hpp"

enum class error_message {
    ER_BADFILE,
    ER_TOOBIG,
    ER_POOLOVF,
    ER_TOOLONG,
    ER_SYMTAB,
    ER_BADSTR,
    ER_SYMCOL
};

void error_fatal(error_message, int);
void error_warn(error_message, int);
void error_unexpected(lex_type, lex_type, int);
void error_punctype(punc_type, punc_type, int);

#endif
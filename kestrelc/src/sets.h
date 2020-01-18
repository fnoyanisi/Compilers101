/*-
 * set.h 
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

#include <stdint.h>

/* sets.h a fast lightweight implementation of set operations */
typedef uint32_t set32_t;

/*
 * construct a single-member set32_t value from one integer or enumeration
 * 
 * set32_t to_set32(int i) 
 */
#define to_set32(i) (((set32_t)1) << (i))

/* 
 * test if integer in set32_t, returns nonzero if so, zero if not
 * 
 * bool in_set32( int i, set32_t s ) 
 */
#define in_set32(i,s) (to_set32(i) & s)

/* 
 * construct set32_t value from 2 integers 
 * 
 * set32_t to_set32_2( int i, int j ) 
 */
#define to_set32_2(i,j) (to_set32(i) | to_set32(j)) 

/* 
 * construct set32_t value from 3 integers
 * 
 * set32_t to_set32_3( int i, int j, int k ) 
 */
#define to_set32_3(i,j,k) (to_set32(i) | to_set32(j) | to_set32(k)) 

/* set32_t to_set32_4( int i, int j, int k, int l ) */
#define to_set32_4(i,j,k,l) (to_set32_2(i,j) | to_set32_2(k,l))
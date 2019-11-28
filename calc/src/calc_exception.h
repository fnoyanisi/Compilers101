// calc_exception.h
// Copyright (c) 2019, Fehmi Noyan ISI fnoyanisi@yahoo.com
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY Fehmi Noyan ISI ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL Fehmi Noyan ISI BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef CALC_EXCEPTION_H_
#define CALC_EXCEPTION_H_

#include <iostream>
#include <exception>
#include "calc.h"

#define BUFSIZE 1024

struct CalcException : public std::exception {
    private:
        char message[BUFSIZE];

    public:
        CalcException(int i, std::string m){
            if (i >= 0)
                snprintf(message, BUFSIZE, "%*s^ %s", i, "", m.c_str());
            else
                snprintf(message, BUFSIZE, "%s", m.c_str());
        }

        CalcException(std::string m){
            CalcException(-1, m);
        }

        CalcException(Token e, Token f){
            snprintf(message, BUFSIZE, "Syntax Error : Expecting %s but got %s", e.str().c_str(), f.str().c_str());
        }

        const char * what () const throw (){
            return message;
        }
};

#endif
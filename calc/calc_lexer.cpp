// calc_lexer.cpp
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

#include <iostream>
#include <string>
#include <vector>

#include "calc_exception.h"
#include "calc.h"

// This lexer uses 'Principle of Longest Substring'. i.e. given a 
// choice between two interpretations, it always chooses the longest one.
void lexer(std::string line, std::vector<Token>& tokens){
    int index = 0;
    std::string lexeme("");
    TokenType type = TokenType::UNKNOWN;

    for(char c: line){
        std::string tmp_lexeme = lexeme + c;
        TokenType tmp_type = TokenFactory::getType(tmp_lexeme);

        if (tmp_type == TokenType::UNKNOWN || tmp_type == TokenType::SPACE) {
            if (type == TokenType::UNKNOWN)
                throw CalcException(index-1, "Unknown character");

            tokens.push_back(Token(lexeme, type));

            lexeme = c;
            type = TokenFactory::getType(lexeme);
        } else {
            lexeme = tmp_lexeme;
            type = tmp_type;
        }

        index++;
    }

    tokens.push_back(Token(lexeme, type));
}
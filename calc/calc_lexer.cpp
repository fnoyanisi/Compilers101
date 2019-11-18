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

// This runs in O(n) time.
// However, by updating CharFactor::getChars() with a post-condition 
// to return an ordered list, std::binary_search, which runs in O(logN)
// time, can be used instead of linear search, and the running time can
// be improved
bool vector_find(std::vector<char> v, char c){
    for (auto a: v){
        if (a == c)
            return true;
    }
    return false;
}

void lexer(std::string line, std::vector<Token>& tokens){
    int index = 0;

    for(char c: line){
        if (!std::isspace(c)) {
            if (vector_find(CharFactory::getChars(TokenType::BINOP), c))
                tokens.push_back(Token(c, TokenType::BINOP));
            else if (vector_find(CharFactory::getChars(TokenType::LP), c))
                tokens.push_back(Token(c, TokenType::LP));
            else if (vector_find(CharFactory::getChars(TokenType::RP), c))
                tokens.push_back(Token(c, TokenType::RP));
            else if (vector_find(CharFactory::getChars(TokenType::NUMBER), c)){
                // To account numbers with more than one digit
                if (!tokens.empty() && tokens.back().type == TokenType::NUMBER) {
                    tokens.back().lexeme.append(1,c);
                } else {
                    tokens.push_back(Token(c, TokenType::NUMBER));
                }
            }
            else
                throw CalcException(index, "Unknown character");
        }

        index++;
    }
}
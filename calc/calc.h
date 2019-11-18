// calc.h
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

#ifndef CALC_H_
#define CALC_H_

#include <iostream>
#include <string>
#include <vector>

enum TokenType {BINOP, LP, RP, NUMBER};

class Token {
    public:
        std::vector<char> values;
        TokenType type;
        std::string lexeme;

        Token(char c, TokenType t) {
            this->lexeme = c;
            this->type = t;
        }

        bool append_char(char c) { 
            return false;
        };

        std::string str(){
            switch(this->type) {
                case TokenType::BINOP: return "BinOp " + this-> lexeme;
                case TokenType::LP: return "LeftP " + this-> lexeme;
                case TokenType::RP: return "RightP " + this-> lexeme;
                case TokenType::NUMBER: return "Number " + this-> lexeme;
            }
        }
};

class CharFactory {
    public:
        static std::vector<char> getChars(TokenType t){
            switch (t) {
                case TokenType::BINOP:
                    return {'+','-','*','/'};
                case TokenType::NUMBER:
                    return{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
                case TokenType::LP:
                    return{'('};
                case TokenType::RP:
                    return {')'};
                default:
                    return {};
            }
        }
};

#endif
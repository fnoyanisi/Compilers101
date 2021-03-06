// calc_parser.h
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

#ifndef CALC_PARSER_H_
#define CALC_PARSER_H_

#include <string>
#include <algorithm>
#include <vector>
#include "calc.h"

class CalcParser {
    private:
        std::vector<Token>& tokens;
        size_t pos;
        Token token;

        bool isSpace(Token t) { return t.type == TokenType::SPACE; }

    public:
        CalcParser(std::vector<Token>& t) : tokens(t), token(tokens.at(0)) {
            // Remove the spaces from the list of tokens
            this->tokens.erase(std::remove_if(this->tokens.begin(), 
                                            this->tokens.end(), 
                                            [](Token t) { return t.type == TokenType::SPACE; }), 
                                            this->tokens.end());
            this->pos = 0;
        }

        std::string match(TokenType);
        double parseExpression();
        double parseTerm();
        double parseFactor();
};

#endif
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
// THIS SOFTWARE IS PROVIDED BY Fehmi Noyan ISI ""AS IS"" AND ANY
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

enum class TokenType {BINOPL, BINOPH, LP, RP, NUMBER, SPACE, UNKNOWN};

// This class represents each token created by the lexer
class Token {
    public:
        std::vector<char> values;
        TokenType type;
        std::string lexeme;

        Token(std::string s, TokenType t) {
            this->lexeme = s;
            this->type = t;
        }

        bool append_char(char c) { 
            return false;
        };

        std::string str(){
            switch(this->type) {
                case TokenType::BINOPL: return "BinOpL " + this-> lexeme;
                case TokenType::BINOPH: return "BinOpH " + this-> lexeme;
                case TokenType::LP: return "LeftP " + this-> lexeme;
                case TokenType::RP: return "RightP " + this-> lexeme;
                case TokenType::NUMBER: return "Number " + this-> lexeme;
                case TokenType::SPACE: return "Space";
                case TokenType::UNKNOWN: return "Unknown " + this-> lexeme;
            }
        }
};

class TokenFactory {
    private:
        // This runs in O(n) time.
        // However, by updating CharFactor::getChars() with a post-condition 
        // to return an ordered list, std::binary_search, which runs in O(logN)
        // time, can be used instead of linear search, and the running time can
        // be improved
        static bool vector_find(std::vector<std::string> v, std::string s){
            for (auto t: v){
                if (t == s)
                    return true;
            }
            return false;
        }

    public:
        static TokenType getType(std::string s){
            if (vector_find(getTokens(TokenType::BINOPL), s))
                return TokenType::BINOPL;
            else if (vector_find(getTokens(TokenType::BINOPH), s))
                return TokenType::BINOPH;
            else if (vector_find(getTokens(TokenType::LP), s))
                return TokenType::LP;
            else if (vector_find(getTokens(TokenType::RP), s))
                return TokenType::RP;
            else if (s.find_first_not_of("0123456789") == std::string::npos)
                return TokenType::NUMBER;
            else if (s.find_first_not_of(' ') == std::string::npos)
                return TokenType::SPACE;
            else
                return TokenType::UNKNOWN;
        }

        static std::vector<std::string> getTokens(TokenType t){
            switch (t) {
                case TokenType::BINOPL:
                    return {"+","-"};
                case TokenType::BINOPH:
                    return {"*","/"};
                case TokenType::NUMBER:
                    return{ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
                case TokenType::LP:
                    return{"("};
                case TokenType::RP:
                    return {")"};
                case TokenType::SPACE:
                case TokenType::UNKNOWN:
                    return {};
            }
        }
};

#endif
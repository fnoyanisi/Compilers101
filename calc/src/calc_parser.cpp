// calc_parser.cpp
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

#include "calc.h"
#include "calc_parser.h"
#include "calc_exception.h"

// Advances the token pointer, matches a given token and updates 
// the value of binary operator or the number depedning on the 
// type of the token
std::string CalcParser::match(TokenType t){
    if (this->token.type == t) {
        std::string lexeme = this->token.lexeme;
        this->token = this->tokens.at(++this->pos);
        return lexeme;
    } else {
        throw CalcException(Token("", t), this->token);
    }
    // not reached
}

// Expr     ::= Term ( BinOpL Term )*
double CalcParser::parseExpression(){
    double right, left; 
    
    right = 0;
    left = parseTerm();

    while(TokenFactory::getType(this->token.lexeme) == TokenType::BINOPL){
        std::string op = match(TokenType::BINOPL);
        right = parseTerm();
        if (op == "+")
            left += right;
        else 
            left -= right; 
    }

    return left;
}

// Term     ::= Factor ( BinOpH Factor )*
double CalcParser::parseTerm(){
    double right, left; 
    
    right = 0;
    left = parseFactor();

    while(TokenFactory::getType(this->token.lexeme) == TokenType::BINOPH){
        std::string op = match(TokenType::BINOPH);
        right = parseFactor();
        if (op == "*")
            left *= right;
        else 
            left /= right; 
    }

    return left;
}

// Factor   ::= '(' Expr ')'
//          | Number
double CalcParser::parseFactor(){
    double result;
    if (this->token.type == TokenType::NUMBER) {
        std::string number = match(TokenType::NUMBER);
        result = std::stod(number);
    } else {
        match(TokenType::LP);
        result = parseExpression();
        match(TokenType::RP);
    }
    return result;
}
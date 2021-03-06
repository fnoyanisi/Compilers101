// calc.cpp
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
#include <cctype>

#include "calc.h"
#include "calc_lexer.h"
#include "calc_parser.h"
#include "calc_exception.h"

void intro(){
    std::cout << "Type \"v\" to toggle the verbose mode for the lexer or \"quit\" to exit." << std::endl;
    std::cout << "Enter an expression" << std::endl;
}

int main(){
    std::vector<Token> tokens;
    std::string input;
    bool verbose = false;

    intro();

    while(true) {
        tokens.clear();

        std::cout << ">> ";
        std::getline(std::cin,input);

        if (input == "quit")
            return 0;
        else if (input == "v") {
            verbose = !verbose;
            std::cout << "verbose mode " << ((verbose)? "on" : "off") << std::endl;
            continue;
        }

        try {
            CalcLexer(input, tokens);

            if (verbose) {
                std::cout << "Lexer output : " << std::endl;
                for (auto t : tokens)
                    std::cout << t.str() << std::endl;
            }

            CalcParser calcParser(tokens);

            std::cout << "result : " << calcParser.parseExpression() << std::endl;

        } catch (CalcException& e) {
            std::cout << input << std::endl;
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}
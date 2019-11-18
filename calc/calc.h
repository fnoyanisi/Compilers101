#include <iostream>
#include <string>
#include <vector>

#ifndef CALC_H_
#define CALC_H_

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
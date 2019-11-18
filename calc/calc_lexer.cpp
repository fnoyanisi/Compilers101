#include <iostream>
#include <string>
#include <vector>

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
    std::vector<int> syntax_errors;

    try {
        for(char c: line){
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
                throw index;

            index++;
        }
    } catch (...) {
        tokens.clear();
        std::cout << line << std::endl;
        std::cout << std::string(index, ' ') << "^ syntax error" << std::endl;
    }
}
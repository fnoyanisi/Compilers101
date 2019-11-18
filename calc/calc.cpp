#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "calc.h"
#include "calc_lexer.h"

int main(){
    std::vector<Token> tokens;
    std::string input;

    std::cout << "Type \"quit\" to exit." << std::endl;

    while(true) {
        std::cout << ">> ";
        std::getline(std::cin,input);

        if (input == "quit")
            return 0;

        lexer(input, tokens);

        for (auto t : tokens)
            std::cout << t.str() << std::endl;
    }

    return 0;
}
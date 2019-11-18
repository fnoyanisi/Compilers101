#include <iostream>
#include <string>
#include <vector>
#include "calc.h"

#ifndef CALC_LEXER_H_
#define CALC_LEXER_H_

bool vector_find(std::vector<char>, char);

void lexer(std::string, std::vector<Token>&);

#endif
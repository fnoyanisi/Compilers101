# calc : simple, interactive arithmetic calculator

## Summary
A simple arithmetic calculator program to practice the basics of compilers. This program implements a very simple compiler front-end using a separate lexer and a parser.

The code is meant to be explanatory rather than using the best approaches at times.

Two main sources were used for this practice: [Scott Gordon's lecture notes on Computing Theory and Programming Languages](https://athena.ecs.csus.edu/~gordonvs/135/resources/) (till the point where the lexer is implemented), and [Douglas W. Jones' lecture notes on Compile Construction](http://homepage.divms.uiowa.edu/~jones/compiler/notes/) (for the parser).

## Grammar 
The calculator lacks some arithmetic operations, such as the exponentiation is not implemented. However, adding support for this ooperation is trivial and requires one more production in the grammar. Also, negative number are not supported, but, simila to the exponentiation operation, this would be a trivial addition to the existing grammar and the code.

#### BNF Syntax
```
<expr> ::= <expr> + <term> | <expr> - <term> | <term>
<term> ::= <term> * <factor> | <term> / <factor> | <factor>
<factor> ::= ( <expr> ) | <number>
<number> ::= <digit> <number> | <digit>
<digit> ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
```

#### EBNF Syntax
```
<expr> ::= <term> {<term> (+ | -)} 
<term> ::= <factor> {<factor> (* | /)} 
<factor> ::= '(' <expr> ')' | <digit> {<digit>}
<digit> ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
```

However, the ENBF grammar used to draw syntax (railroad) diagrams and the implement the parser is given below. The grammar below, when used on [bottlecaps.de](https://www.bottlecaps.de/rr/ui), gives the railroad diagrams used for the parser. 

```
Expr     ::= Term (BinOpL Term)*
Term     ::= Factor (BinOpH Factor)*
Factor   ::= '(' Expr ')' | Number
Number   ::= Digit+
Digit    ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
BinOpL   ::= '+' | '-'
BinOpH   ::= '*' | '/'
```

## TODO
See the Issues

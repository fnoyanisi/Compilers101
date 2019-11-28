# calc : simple and interactive arithmetic calculator

## Summary
A simple arithmetic calculator program to practice the basics of compilers. This program implements a very simple compiler front-end using a separate lexer and a parser.

The code is meant to be explanatory rather than using the best practactices at times.

Two main sources were used for this practice: [Scott Gordon's lecture notes on Computing Theory and Programming Languages](https://athena.ecs.csus.edu/~gordonvs/135/resources/) (till the point where the lexer is implemented), and [Douglas W. Jones' lecture notes on Compile Construction](http://homepage.divms.uiowa.edu/~jones/compiler/notes/) (for the parser). You may also find [Federico Tomasetti's Guide to Parsing](https://tomassetti.me/guide-parsing-algorithms-terminology/) an interesting read.

## Grammar 
The calculator lacks support for some arithmetic operations, such as the exponentiation and being able to parse negative numbers. However, implementing these features is trivial and only requires a couple of more production rules in the grammar. 

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
The ENBF grammar used to draw syntax (railroad) diagrams and to the implement the parser is given below. The grammar below, when used in [bottlecaps.de](https://www.bottlecaps.de/rr/ui), gives the railroad diagrams used for the parser. 

```
Expr     ::= Term (BinOpL Term)*
Term     ::= Factor (BinOpH Factor)*
Factor   ::= '(' Expr ')' | Number
Number   ::= Digit+
Digit    ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
BinOpL   ::= '+' | '-'
BinOpH   ::= '*' | '/'
```

## Building
You need to have `cmake` installed to build the program. Once you are in the main director (`calc/`)

```
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

## TODO
See the Issues

## LICENSE
2-Clause BSD license

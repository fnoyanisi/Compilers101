# calc : simple and interactive arithmetic calculator

## Summary
A simple arithmetic calculator program to practice the basics of compilers. This program implements a very simple compiler front-end using a separate lexer and a parser.

The code is meant to be explanatory rather than using the best practactices at times.

Two main sources were used for this practice: [Scott Gordon's lecture notes on Computing Theory and Programming Languages](https://athena.ecs.csus.edu/~gordonvs/135/resources/), and [Douglas W. Jones' lecture notes on Compiler Construction, especially the ones covering _Recursive Descent Parsers_](http://homepage.divms.uiowa.edu/~jones/compiler/notes/). You may also find [Federico Tomasetti's Guide to Parsing](https://tomassetti.me/guide-parsing-algorithms-terminology/) an interesting read.

## Implementation Notes
Usage of principle of the longest substring helps the lexer to tackle the ambiguity in the grammar. This is a known and used technique in compilers & interpreters.

An alternative implementation could use a state table rather than a railroad diagram to implement the lexer and the parser.

In a more ideal implementation, instead of having completely seperate lexing and parsing stages, one could have a `CalcLexer` class and a `CalcLexer::advance()` method that would be invoked by `CalcParser` to get the next token identified by the lexer.

Also, the current implementation does not make use of the `end-of-file` token, which is used to verify the integrity of the data read from the cource file.

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
